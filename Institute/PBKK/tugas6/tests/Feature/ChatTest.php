<?php

namespace Tests\Feature;

use App\Livewire\ChatPanel;
use App\Livewire\ConversationList;
use App\Models\Conversation;
use App\Models\User;
use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Support\Facades\Cache;
use Illuminate\Support\Facades\Http;
use Livewire\Livewire;
use Tests\TestCase;

class ChatTest extends TestCase
{
    use RefreshDatabase;

    protected function setUp(): void
    {
        parent::setUp();
        Http::preventStrayRequests();
        config(['llm.url' => 'https://llm.test/api/chat', 'llm.model' => 'test-model', 'llm.demo' => false]);
    }

    public function test_guests_cannot_access_chat_or_api(): void
    {
        $this->get('/chat')->assertRedirect('/login');
        $this->postJson('/api/chat', ['prompt' => 'Hello'])->assertUnauthorized();
    }

    public function test_demo_is_explicit_and_works_without_an_llm(): void
    {
        config(['llm.demo' => true]);
        Livewire::actingAs(User::factory()->create())->test(ChatPanel::class)
            ->assertSee('Mode demo aktif')->set('prompt', 'Coba percakapan')->call('send')
            ->assertHasNoErrors()->assertSee('Respons contoh');
        Http::assertNothingSent();
        $this->assertDatabaseCount('chat_messages', 2);
    }

    public function test_workspace_renders_both_livewire_components(): void
    {
        $this->actingAs(User::factory()->create())->get('/chat')->assertOk()
            ->assertSeeLivewire(ConversationList::class)->assertSeeLivewire(ChatPanel::class)
            ->assertSee('wire:loading.attr="disabled"', false);
    }

    public function test_send_persists_an_ordered_pair_and_refresh_restores_it(): void
    {
        Http::fake(['*' => Http::sequence()
            ->push(['message' => ['content' => 'Jawaban pertama.']])
            ->push(['message' => ['content' => 'Jawaban kedua.']])]);
        $user = User::factory()->create();
        $component = Livewire::actingAs($user)->test(ChatPanel::class)
            ->set('prompt', 'Jelaskan Livewire')->call('send')->assertHasNoErrors()
            ->assertSet('prompt', '')->assertDispatched('conversations-changed');
        $conversation = Conversation::firstOrFail();
        $this->assertSame($user->id, $conversation->user_id);
        $this->assertSame(['user', 'assistant'], $conversation->messages()->orderBy('id')->pluck('role')->all());
        $this->assertSame([$user->id], $conversation->messages()->pluck('user_id')->unique()->all());

        $component->set('prompt', 'Berikan contohnya')->call('send')->assertHasNoErrors();
        Http::assertSent(fn ($request) => count($request['messages']) === 3
            && $request['messages'][0]['content'] === 'Jelaskan Livewire'
            && $request['messages'][1]['role'] === 'assistant');
        Livewire::test(ChatPanel::class)->assertSee('Jawaban pertama.')->assertSee('Jawaban kedua.');
    }

    public function test_empty_whitespace_short_and_oversized_prompts_do_not_call_llm(): void
    {
        foreach (['', '   ', 'ab', str_repeat('a', 1001)] as $prompt) {
            Livewire::actingAs(User::factory()->create())->test(ChatPanel::class)
                ->set('prompt', $prompt)->call('send')->assertHasErrors('prompt');
        }
        $this->assertDatabaseCount('chat_messages', 0);
        $this->assertDatabaseCount('conversations', 0);
        Http::assertNothingSent();
    }

    public function test_conversations_cannot_be_read_or_selected_by_another_user(): void
    {
        $owner = User::factory()->create();
        $other = User::factory()->create();
        $conversation = Conversation::create(['user_id' => $owner->id, 'title' => 'Private secret']);
        $conversation->messages()->create(['user_id' => $owner->id, 'role' => 'user', 'content' => 'Private content']);

        Livewire::actingAs($other)->test(ConversationList::class)->assertDontSee('Private secret');
        Livewire::test(ChatPanel::class)->assertDontSee('Private content');
        $this->actingAs($other)->postJson('/api/chat', ['conversation_id' => $conversation->id, 'prompt' => 'Steal this'])
            ->assertNotFound();
        $this->getJson('/api/conversations/'.$conversation->id.'/messages')->assertNotFound();
        Http::assertNothingSent();
        $this->expectException(\Illuminate\Database\Eloquent\ModelNotFoundException::class);
        Livewire::test(ChatPanel::class)->dispatch('conversation-selected', id: $conversation->id);
    }

    public function test_events_select_a_conversation_and_start_a_fresh_one(): void
    {
        $user = User::factory()->create();
        $conversation = Conversation::create(['user_id' => $user->id, 'title' => 'Previous chat']);
        Livewire::actingAs($user)->test(ChatPanel::class)
            ->dispatch('new-conversation')->assertSet('conversationId', null)
            ->dispatch('conversation-selected', id: $conversation->id)->assertSet('conversationId', $conversation->id);
    }

    public function test_failed_llm_preserves_user_message_and_retry_does_not_duplicate_it(): void
    {
        Http::fake(['*' => Http::sequence()
            ->push(['error' => 'secret upstream details'], 503)
            ->push(['message' => ['content' => 'PHP adalah bahasa pemrograman.']])]);
        $component = Livewire::actingAs(User::factory()->create())->test(ChatPanel::class)
            ->set('prompt', 'Tolong jelaskan PHP')->call('send')->assertHasErrors('prompt')
            ->assertSee('Coba lagi')->assertDontSee('secret upstream details');
        $this->assertDatabaseCount('chat_messages', 1);
        $component->set('prompt', 'Another prompt')->call('send')->assertHasErrors('prompt');
        $this->assertDatabaseCount('chat_messages', 1);

        $component->call('retry')->assertHasNoErrors()->assertSee('PHP adalah bahasa pemrograman.');
        $this->assertDatabaseCount('chat_messages', 2);
    }

    public function test_empty_or_malformed_upstream_response_is_not_saved_as_an_answer(): void
    {
        Http::fake(['*' => Http::response(['message' => ['content' => []]])]);
        Livewire::actingAs(User::factory()->create())->test(ChatPanel::class)
            ->set('prompt', 'Hello there')->call('send')->assertHasErrors('prompt');
        $this->assertDatabaseCount('chat_messages', 1);
    }

    public function test_connection_failure_can_be_retried_and_releases_the_lock(): void
    {
        Http::fake(['*' => Http::failedConnection()]);
        Livewire::actingAs(User::factory()->create())->test(ChatPanel::class)
            ->set('prompt', 'Hello there')->call('send')->assertHasErrors('prompt');
        $lock = Cache::lock('chat:'.Conversation::firstOrFail()->id, 10);
        $this->assertTrue($lock->get());
        $lock->release();
    }

    public function test_concurrent_send_is_rejected_before_inserting_another_message(): void
    {
        $user = User::factory()->create();
        $conversation = Conversation::create(['user_id' => $user->id, 'title' => 'Busy']);
        $lock = Cache::lock('chat:'.$conversation->id, 10);
        $lock->get();
        try {
            Livewire::actingAs($user)->test(ChatPanel::class)
                ->set('prompt', 'Send while busy')->call('send')->assertHasErrors('prompt');
            $this->assertDatabaseCount('chat_messages', 0);
            Http::assertNothingSent();
        } finally {
            $lock->release();
        }
    }

    public function test_markdown_output_does_not_execute_html_or_javascript_links(): void
    {
        $attack = '<script>alert("xss")</script>[bad](javascript:alert(1))';
        Http::fake(['*' => Http::response(['message' => ['content' => $attack]])]);
        Livewire::actingAs(User::factory()->create())->test(ChatPanel::class)
            ->set('prompt', 'Show a safe response')->call('send')
            ->assertDontSee('<script>alert', false)->assertDontSee('href="javascript:', false);
    }

    public function test_bearer_token_can_send_read_and_revoke_access(): void
    {
        $user = User::factory()->create();
        $token = $this->postJson('/api/token', ['email' => $user->email, 'password' => 'password'])
            ->assertOk()->json('token');
        Http::fake(['*' => Http::response(['choices' => [['message' => ['content' => 'Compatible response.']]]])]);
        $conversationId = $this->withToken($token)->postJson('/api/chat', ['prompt' => 'Hello from API'])
            ->assertCreated()->assertJsonPath('message.role', 'assistant')->json('conversation_id');
        $this->withToken($token)->getJson('/api/conversations/'.$conversationId.'/messages')
            ->assertOk()->assertJsonCount(2, 'data');
        $this->withToken($token)->deleteJson('/api/token')->assertNoContent();
        $this->assertDatabaseCount('personal_access_tokens', 0);
    }
}
