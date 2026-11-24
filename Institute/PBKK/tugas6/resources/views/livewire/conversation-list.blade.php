<aside class="sidebar" aria-label="Riwayat percakapan">
    <button type="button" class="button button-primary new-chat" wire:click="$dispatchTo('chat-panel', 'new-conversation')" wire:loading.attr="disabled">
        <i class="bi bi-plus-lg" aria-hidden="true"></i> Percakapan baru
    </button>
    <details class="history" open>
        <summary>Riwayat percakapan <span>{{ $conversations->count() }}</span></summary>
        <nav class="conversation-list" aria-label="Pilih percakapan">
            @forelse ($conversations as $item)
                <button type="button" wire:key="conversation-{{ $item->id }}"
                    wire:click="$dispatchTo('chat-panel', 'conversation-selected', { id: {{ $item->id }} })"
                    wire:loading.attr="disabled" class="conversation-item">
                    <i class="bi bi-chat-left-text" aria-hidden="true"></i>
                    <span><strong>{{ $item->title }}</strong><small>{{ $item->updated_at->format('d M, H:i') }}</small></span>
                </button>
            @empty
                <p class="sidebar-empty">Percakapan Anda akan tersimpan di sini setelah mengirim pesan pertama.</p>
            @endforelse
        </nav>
    </details>
    <div class="sidebar-footer"><strong>Ruang belajar Anda.</strong><p>Riwayat hanya dapat diakses oleh akun Anda.</p><small>Maulana · 5025241001<br>PBKK · Tugas 6</small></div>
</aside>
