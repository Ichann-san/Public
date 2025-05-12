const canvas = document.getElementById('gameview');
canvas.width = canvas.offsetWidth;
canvas.height = canvas.offsetHeight;


document.addEventListener('DOMContentLoaded', function() {
    const items = ['Tetris', 'Snake', 'Minesweeper', 'Pong', '2048'];
    let current = 0;

    const games = document.getElementById('games');
    document.getElementById('lbutt').onclick = function() {
        current = (current - 1 + items.length) % items.length;
        games.textContent = items[current];
    };
    document.getElementById('rbutt').onclick = function() {
        current = (current + 1) % items.length;
        games.textContent = items[current];
    };
});