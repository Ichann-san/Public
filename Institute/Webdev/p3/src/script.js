const form = document.querySelector('form');

form.addEventListener('submit', function(event) {
    event.preventDefault();
    Notification.requestPermission().then(permission => {
        if (permission === 'granted') {
            new Notification('Form Terkirim!', {
                body: 'Datamu telah berhasil disubmit.',
            });
        }

        setTimeout(() => {
            form.submit();
        }, 200);
    });
});