function toggleTheme() {
    const theme = document.documentElement.dataset.theme === 'dark' ? 'light' : 'dark';
    document.documentElement.dataset.theme = theme;
    try { localStorage.setItem('pbkk-theme', theme); } catch (_) {}
}

document.addEventListener('alpine:init', () => {
    Alpine.data('typingMessage', (id, text, animate) => ({
        shown: '', typing: false, timer: null,
        init() {
            if (!animate || matchMedia('(prefers-reduced-motion: reduce)').matches) return;
            try {
                if (sessionStorage.getItem('message-' + id)) return;
                sessionStorage.setItem('message-' + id, 'seen');
            } catch (_) {}
            this.typing = true;
            let position = 0;
            const step = Math.max(3, Math.ceil(text.length / 100));
            this.timer = setInterval(() => {
                position += step;
                this.shown = text.slice(0, position);
                if (position >= text.length) {
                    clearInterval(this.timer);
                    this.typing = false;
                    this.$dispatch('messages-updated');
                }
            }, 15);
        },
        destroy() { clearInterval(this.timer); },
    }));
});
