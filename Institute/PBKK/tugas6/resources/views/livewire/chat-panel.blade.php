<main id="main" class="chat-panel" x-data x-on:messages-updated.window="$nextTick(() => $refs.messages.scrollTop = $refs.messages.scrollHeight)">
    <div class="chat-header">
        <div><h1>{{ $conversation?->title ?? 'Workspace AI' }}</h1><p>Tulis ide, pelajari konsep, atau kerjakan kode bersama.</p></div>
        <span class="private-badge"><i class="bi bi-lock" aria-hidden="true"></i> Privat</span>
    </div>

    @if (config('llm.demo'))
        <div class="demo-banner" role="status"><i class="bi bi-info-circle" aria-hidden="true"></i> Mode demo aktif. Balasan berupa contoh; belum terhubung ke model AI.</div>
    @endif
    <div class="messages" x-ref="messages" aria-label="Pesan percakapan" tabindex="0">
        @if ($messages->isEmpty())
            <div class="empty-state">
                <div class="assistant-mark" aria-hidden="true"><i class="bi bi-stars"></i></div>
                <h2>Mulai dari satu pertanyaan.</h2>
                <p>Asisten untuk menemani belajar dan menyusun ide. Apa yang ingin Anda kerjakan hari ini?</p>
                <div class="suggestions">
                    @foreach (['Jelaskan konsep event pada Laravel Livewire.', 'Bantu susun rencana belajar PHP selama satu minggu.', 'Berikan contoh validasi form Laravel yang aman.'] as $suggestion)
                        <button class="suggestion" type="button" wire:click="$set('prompt', @js($suggestion))">{{ $suggestion }} <i class="bi bi-arrow-up-right" aria-hidden="true"></i></button>
                    @endforeach
                </div>
            </div>
        @else
            <p class="history-note">Menampilkan hingga 100 pesan terbaru. Semua pesan tetap tersimpan.</p>
            @foreach ($messages as $message)
                <article wire:key="message-{{ $message->id }}" class="message {{ $message->role }}">
                    <div class="message-meta"><strong>{{ $message->role === 'user' ? 'Anda' : 'Asisten AI' }}</strong><time datetime="{{ $message->created_at->toIso8601String() }}">{{ $message->created_at->format('H:i') }}</time></div>
                    @if ($message->role === 'assistant')
                        <div class="bubble" x-data="typingMessage({{ $message->id }}, @js($message->content), @js($loop->last))">
                            <div class="typed-content" x-show="typing" x-text="shown" aria-hidden="true"></div>
                            <div class="markdown" x-show="!typing">{!! \Illuminate\Support\Str::markdown($message->content, ['html_input' => 'strip', 'allow_unsafe_links' => false]) !!}</div>
                        </div>
                    @else
                        <div class="bubble user-content">{{ $message->content }}</div>
                    @endif
                </article>
            @endforeach
        @endif
        <div wire:loading wire:target="send,retry" class="thinking" role="status"><span class="spinner" aria-hidden="true"></span> Asisten sedang menyiapkan jawaban…</div>
    </div>

    <div class="composer-wrap">
        @error('prompt')<div class="form-error" id="prompt-error" role="alert">{{ $message }}</div>@enderror
        @if ($messages->last()?->role === 'user')
            <div class="retry-note"><span>Pesan tersimpan dan menunggu jawaban.</span><button type="button" class="button button-secondary" wire:click="retry" wire:loading.attr="disabled" wire:target="send,retry">Coba lagi</button></div>
        @endif
        <form wire:submit="send" class="composer" aria-label="Kirim pesan">
            <label for="prompt" class="sr-only">Pesan untuk asisten AI</label>
            <textarea id="prompt" wire:model.live.debounce.300ms="prompt" rows="3" placeholder="Tulis pertanyaan atau instruksi Anda…"
                wire:loading.attr="disabled" wire:target="send,retry" aria-describedby="prompt-help @error('prompt') prompt-error @enderror" @error('prompt') aria-invalid="true" @enderror></textarea>
            <div class="composer-actions">
                <small id="prompt-help">{{ mb_strlen($prompt) }} / 1000 karakter</small>
                <button class="button button-primary" type="submit" wire:loading.attr="disabled" wire:target="send,retry" @disabled($messages->last()?->role === 'user')>
                    <span wire:loading.remove wire:target="send,retry">Kirim <i class="bi bi-arrow-up" aria-hidden="true"></i></span>
                    <span wire:loading wire:target="send,retry">Memproses…</span>
                </button>
            </div>
        </form>
        <p class="composer-footnote">AI dapat membuat kesalahan. Periksa kembali informasi penting.</p>
    </div>
</main>
