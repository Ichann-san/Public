<?php

namespace App\Services;

use App\Models\ChatMessage;
use App\Models\Conversation;
use App\Models\User;
use Illuminate\Http\Client\ConnectionException;
use Illuminate\Http\Client\RequestException;
use Illuminate\Support\Facades\Cache;
use Illuminate\Support\Facades\Http;
use Illuminate\Validation\ValidationException;

class ChatService
{
    public function reply(User $user, int $conversationId, ?string $prompt = null): ChatMessage
    {
        $conversation = Conversation::where('user_id', $user->id)->findOrFail($conversationId);
        $lock = Cache::lock('chat:'.$conversation->id, config('llm.timeout') + 30);

        if (! $lock->get()) {
            throw ValidationException::withMessages(['prompt' => 'Jawaban masih diproses. Tunggu sebentar.']);
        }

        try {
            $last = $conversation->messages()->latest('id')->first();

            if ($prompt !== null) {
                if ($last?->role === 'user') {
                    throw ValidationException::withMessages(['prompt' => 'Pesan terakhir belum dijawab. Gunakan tombol Coba lagi.']);
                }

                $conversation->messages()->create([
                    'user_id' => $user->id,
                    'role' => 'user',
                    'content' => $prompt,
                ]);
                $conversation->touch();
            } elseif ($last?->role !== 'user') {
                throw ValidationException::withMessages(['prompt' => 'Tidak ada jawaban yang perlu dicoba ulang.']);
            }

            // shortcut: send the latest 40 messages as context; add summarization for longer conversations.
            $history = $conversation->messages()->latest('id')->limit(40)->get()
                ->reverse()->values()->map->only(['role', 'content'])->all();

            if (config('llm.demo')) {
                $message = $conversation->messages()->create([
                    'user_id' => $user->id,
                    'role' => 'assistant',
                    'content' => "**Respons contoh — mode demo, bukan jawaban model AI.**\n\nPesan Anda sudah tersimpan. Anda dapat melanjutkan percakapan, membuat obrolan baru, atau membuka riwayat setelah memuat ulang halaman.\n\nUntuk mendapatkan jawaban AI sungguhan, hubungkan layanan LLM melalui konfigurasi aplikasi.\n\n```php\n// Contoh: pesan disimpan dengan pemilik yang aktif.\nChatMessage::create([\n    'user_id' => auth()->id(),\n    'role' => 'user',\n    'content' => \$prompt,\n]);\n```",
                ]);
                $conversation->touch();

                return $message;
            }

            $request = Http::acceptJson()->connectTimeout(10)->timeout(config('llm.timeout'));
            if (filled(config('llm.key'))) {
                $request = $request->withToken(config('llm.key'));
            }

            try {
                $response = $request->post(config('llm.url'), [
                    'model' => config('llm.model'),
                    'messages' => $history,
                    'stream' => false,
                ])->throw();
            } catch (ConnectionException|RequestException $exception) {
                // Keep credentials and upstream response bodies out of the UI and logs.
                throw ValidationException::withMessages([
                    'prompt' => 'Layanan AI belum dapat dihubungi. Pesan tersimpan; periksa koneksi lalu coba lagi.',
                ]);
            }

            $content = $response->json('message.content') ?? $response->json('choices.0.message.content');
            if (! is_string($content) || trim($content) === '' || mb_strlen($content) > 60000) {
                throw ValidationException::withMessages([
                    'prompt' => 'Jawaban AI tidak valid. Pesan tersimpan; silakan coba lagi.',
                ]);
            }

            $message = $conversation->messages()->create([
                'user_id' => $user->id,
                'role' => 'assistant',
                'content' => $content,
            ]);
            $conversation->touch();

            return $message;
        } finally {
            $lock->release();
        }
    }
}
