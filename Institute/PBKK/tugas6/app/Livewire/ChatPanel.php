<?php

namespace App\Livewire;

use App\Models\Conversation;
use App\Services\ChatService;
use Illuminate\Support\Str;
use Illuminate\View\View;
use Livewire\Attributes\Locked;
use Livewire\Attributes\On;
use Livewire\Component;

class ChatPanel extends Component
{
    #[Locked]
    public ?int $conversationId = null;

    public string $prompt = '';

    public function boot(): void
    {
        abort_unless(auth()->check(), 401);
    }

    public function mount(): void
    {
        $this->conversationId = Conversation::where('user_id', auth()->id())
            ->latest('updated_at')->latest('id')->value('id');
    }

    public function updatedPrompt(): void
    {
        $this->resetValidation('prompt');
        $this->validateOnly('prompt', ['prompt' => 'max:1000'], [
            'prompt.max' => 'Prompt maksimal 1000 karakter.',
        ]);
    }

    #[On('conversation-selected')]
    public function selectConversation(int $id): void
    {
        $conversation = Conversation::where('user_id', auth()->id())->findOrFail($id);
        $this->conversationId = $conversation->id;
        $this->prompt = '';
        $this->resetValidation();
    }

    #[On('new-conversation')]
    public function newConversation(): void
    {
        $this->conversationId = null;
        $this->prompt = '';
        $this->resetValidation();
    }

    public function send(): void
    {
        $this->prompt = trim($this->prompt);
        $this->validate(['prompt' => 'required|string|min:3|max:1000'], [
            'prompt.required' => 'Tulis pesan terlebih dahulu.',
            'prompt.min' => 'Prompt minimal 3 karakter.',
            'prompt.max' => 'Prompt maksimal 1000 karakter.',
        ]);

        if ($this->conversationId === null) {
            $conversation = Conversation::create([
                'user_id' => auth()->id(),
                'title' => Str::limit($this->prompt, 70),
            ]);
            $this->conversationId = $conversation->id;
        }

        $prompt = $this->prompt;
        $this->prompt = '';
        try {
            app(ChatService::class)->reply(auth()->user(), $this->conversationId, $prompt);
        } finally {
            $this->dispatch('conversations-changed')->to(ConversationList::class);
            $this->dispatch('messages-updated');
        }
    }

    public function retry(): void
    {
        abort_if($this->conversationId === null, 404);
        $this->resetValidation();
        try {
            app(ChatService::class)->reply(auth()->user(), $this->conversationId);
        } finally {
            $this->dispatch('conversations-changed')->to(ConversationList::class);
            $this->dispatch('messages-updated');
        }
    }

    public function render(): View
    {
        $conversation = $this->conversationId === null ? null
            : Conversation::where('user_id', auth()->id())->findOrFail($this->conversationId);

        return view('livewire.chat-panel', [
            'conversation' => $conversation,
            'messages' => $conversation?->messages()->latest('id')->limit(100)->get()->reverse()->values() ?? collect(),
        ]);
    }
}
