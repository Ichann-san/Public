// teks_gerak.js
const teksEl = document.getElementById('teks');
const radius = 100;

function parseFontSettings(str) {
  return Object.fromEntries(
    str.split(',').map(s => s.trim().split(' ')).map(([k, v]) => [k.replace(/['"]/g, ''), parseFloat(v)])
  );
}

function toFontSettings(obj) {
  return Object.entries(obj).map(([k, v]) => `'${k}' ${v}`).join(', ');
}

const fromSettings = parseFontSettings("'wght' 400, 'opsz' 9");
const toSettings = parseFontSettings("'wght' 1000, 'opsz' 40");

function lerp(a, b, t) {
  return a + (b - a) * t;
}

function getDistance(x1, y1, x2, y2) {
  return Math.sqrt((x1 - x2)**2 + (y1 - y2)**2);
}

function updateFontVariations(mouseX, mouseY) {
  const rect = teksEl.getBoundingClientRect();
  const centerX = rect.left + rect.width / 2;
  const centerY = rect.top + rect.height / 2;
  const dist = getDistance(mouseX, mouseY, centerX, centerY);
  const factor = Math.max(0, 1 - dist / radius);

  const current = {};
  for (const key in fromSettings) {
    current[key] = lerp(fromSettings[key], toSettings[key], factor);
  }

  teksEl.style.fontVariationSettings = toFontSettings(current);
}

document.addEventListener('mousemove', e => {
  updateFontVariations(e.clientX, e.clientY);
});
