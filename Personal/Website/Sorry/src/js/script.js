const items = [
  "Yakin gamau maafin aku ?",
  "Maaf ya sayang...",
  "I'm sorry...",
  "Aku minta maaf ya sayang",
  "Miaw miaw miaw miaw",
  "Makasih ya udah maafin aku",
  "Yeayy hehe"
];

const gif = [
  "../../assets/gif/a.gif",
  "../../assets/gif/b.gif",
  "../../assets/gif/c.gif",
  "../../assets/gif/d.gif",
  "../../assets/gif/e.gif",
  "../../assets/gif/f.gif",
  "../../assets/gif/g.gif",
  "../../assets/gif/h.gif"
];

let current = 1;
let neg = 0;
const teks = document.getElementById("teks");
const gambarImg = document.querySelector("#gambar img");
const yesbtn = document.getElementById("yes");
const nobtn = document.getElementById("no");
const lagu = document.getElementById("lagu");
teks.textContent = items[current];
gambarImg.src = gif[current+1];
yesbtn.textContent = "Maafin";
nobtn.textContent = "mls";

function playAudio() {
  if (current === 6) {
    lagu.src = "../../assets/audio.mp3";
  }
}

function updatebuttons() {
  if (current === 6) {
    yesbtn.textContent = "😊";
    nobtn.textContent = "❤️";
    playAudio();
  } else {
    yesbtn.textContent = "Maafin";
    nobtn.textContent = "mls";
  }
}

yesbtn.onclick = function () {
  if (current < items.length - 1) {
    current++;
    teks.textContent = items[current];
    gambarImg.src = gif[current+1];
  }
  updatebuttons();
};

nobtn.onclick = function () {
  if (current !== items.length - 1) {
    if (current === 0) {
      teks.textContent = "Yaudah gapapa, aku sayang kamu kok";
      nobtn.textContent = "🥺";
      gambarImg.src = gif[0];
    } else {
      current--;
      teks.textContent = items[current];
      gambarImg.src = gif[current+1];
      updatebuttons();
    }
  }
};
