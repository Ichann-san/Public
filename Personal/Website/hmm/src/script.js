document.addEventListener('DOMContentLoaded', function() {
    const items = [
        "Yakin gamau maafin aku ?",
        "Maaf ya sayang...",
        "I'm sorry...",
        "Aku minta maaf ya sayang",
        "Maukah sayang aku maafin aku",
        "Yeeayy hehe",
        "Makasih ya udah maafin aku"
    ];
    const gif = [
        "../assets/gif/a.gif",
        "../assets/gif/b.gif",
        "../assets/gif/c.gif",
    ];
    let current = 1;

    const teks = document.getElementById('teks');
    const gambarImg = document.querySelector('#gambar img'); // Select the <img> inside #gambar
    teks.textContent = items[current];
    gambarImg.src = gif[current];

    document.getElementById('yes').onclick = function() {
        if (current < items.length - 1) {
            current = current + 1;
            teks.textContent = items[current];
            gambarImg.src = gif[current % gif.length]; // Use modulo in case items > gifs
        }
    }

    document.getElementById('no').onclick = function() {
        if (current != items.length - 1) {
            if (current === 0) {
                teks.textContent = "Yaudah gapapa, aku sayang kamu kok";
                gambarImg.src = gif[0];
            } else if (current > 0) {
                current = current - 1;
                teks.textContent = items[current];
                gambarImg.src = gif[current % gif.length];
            }
        }
    }
});