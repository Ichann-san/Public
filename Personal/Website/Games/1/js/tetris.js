const canvas = document.getElementById('tetris');
const context = canvas ? canvas.getContext('2d') : null;
const scoreElem = document.getElementById('score');

const COLS = 10;
const ROWS = 20;
const BLOCK_SIZE = 24;
const COLORS = [
  null,
  '#FF0D72', // T
  '#0DC2FF', // I
  '#0DFF72', // S
  '#F538FF', // Z
  '#FF8E0D', // L
  '#FFE138', // J
  '#3877FF', // O
];

const SHAPES = [
  [],
  [[0,0],[1,0],[2,0],[1,1]], // T
  [[0,0],[1,0],[2,0],[3,0]], // I
  [[0,0],[1,0],[1,1],[2,1]], // S
  [[1,0],[2,0],[0,1],[1,1]], // Z
  [[0,0],[0,1],[1,1],[2,1]], // L
  [[2,0],[0,1],[1,1],[2,1]], // J
  [[0,0],[1,0],[0,1],[1,1]], // O
];

let arena, player, dropCounter, dropInterval, lastTime, running, score;

function createMatrix(w, h) {
  const matrix = [];
  while (h--) matrix.push(new Array(w).fill(0));
  return matrix;
}

function collide(arena, player) {
  const [m, o] = [player.matrix, player.pos];
  for (let y = 0; y < m.length; ++y) {
    for (let x = 0; x < m[y].length; ++x) {
      if (m[y][x] &&
        (arena[y + o.y] && arena[y + o.y][x + o.x]) !== 0) {
        return true;
      }
    }
  }
  return false;
}

function merge(arena, player) {
  player.matrix.forEach((row, y) => {
    row.forEach((value, x) => {
      if (value) arena[y + player.pos.y][x + player.pos.x] = value;
    });
  });
}

function rotate(matrix, dir) {
  for (let y = 0; y < matrix.length; ++y) {
    for (let x = 0; x < y; ++x) {
      [matrix[x][y], matrix[y][x]] = [matrix[y][x], matrix[x][y]];
    }
  }
  if (dir > 0) matrix.forEach(row => row.reverse());
  else matrix.reverse();
}

function playerDrop() {
  player.pos.y++;
  if (collide(arena, player)) {
    player.pos.y--;
    merge(arena, player);
    playerReset();
    arenaSweep();
    updateScore();
  }
  dropCounter = 0;
}

function playerMove(dir) {
  player.pos.x += dir;
  if (collide(arena, player)) player.pos.x -= dir;
}

function playerReset() {
  const pieces = 'TJSLJOI';
  const type = pieces[Math.floor(Math.random() * pieces.length)];
  player.matrix = createPiece(type);
  player.pos.y = 0;
  player.pos.x = Math.floor(COLS / 2) - Math.floor(player.matrix[0].length / 2);
  if (collide(arena, player)) {
    arena.forEach(row => row.fill(0));
    score = 0;
    updateScore();
    running = false;
    alert('Game Over!');
  }
}

function playerRotate(dir) {
  const pos = player.pos.x;
  let offset = 1;
  rotate(player.matrix, dir);
  while (collide(arena, player)) {
    player.pos.x += offset;
    offset = -(offset + (offset > 0 ? 1 : -1));
    if (offset > player.matrix[0].length) {
      rotate(player.matrix, -dir);
      player.pos.x = pos;
      return;
    }
  }
}

function createPiece(type) {
  switch (type) {
    case 'T': return [
      [0,1,0],
      [1,1,1],
      [0,0,0],
    ];
    case 'O': return [
      [2,2],
      [2,2],
    ];
    case 'L': return [
      [0,0,3],
      [3,3,3],
      [0,0,0],
    ];
    case 'J': return [
      [4,0,0],
      [4,4,4],
      [0,0,0],
    ];
    case 'I': return [
      [0,5,0,0],
      [0,5,0,0],
      [0,5,0,0],
      [0,5,0,0],
    ];
    case 'S': return [
      [0,6,6],
      [6,6,0],
      [0,0,0],
    ];
    case 'Z': return [
      [7,7,0],
      [0,7,7],
      [0,0,0],
    ];
  }
}

function arenaSweep() {
  let rowCount = 1;
  outer: for (let y = arena.length - 1; y >= 0; --y) {
    for (let x = 0; x < arena[y].length; ++x) {
      if (arena[y][x] === 0) continue outer;
    }
    const row = arena.splice(y, 1)[0].fill(0);
    arena.unshift(row);
    ++y;
    score += rowCount * 10;
    rowCount *= 2;
  }
}

function drawMatrix(matrix, offset) {
  matrix.forEach((row, y) => {
    row.forEach((value, x) => {
      if (value && context) {
        context.fillStyle = COLORS[value];
        context.fillRect(
          (x + offset.x) * BLOCK_SIZE,
          (y + offset.y) * BLOCK_SIZE,
          BLOCK_SIZE, BLOCK_SIZE
        );
        context.strokeStyle = '#222';
        context.strokeRect(
          (x + offset.x) * BLOCK_SIZE,
          (y + offset.y) * BLOCK_SIZE,
          BLOCK_SIZE, BLOCK_SIZE
        );
      }
    });
  });
}

function draw() {
  if (!context) return;
  context.fillStyle = '#111';
  context.fillRect(0, 0, canvas.width, canvas.height);
  drawMatrix(arena, {x:0, y:0});
  drawMatrix(player.matrix, player.pos);
}

function update(time = 0) {
  if (!running) return;
  const deltaTime = time - lastTime;
  lastTime = time;
  dropCounter += deltaTime;
  if (dropCounter > dropInterval) {
    playerDrop();
  }
  draw();
  requestAnimationFrame(update);
}

function updateScore() {
  if (scoreElem) scoreElem.innerText = 'Score: ' + score;
}

function startGame() {
  if (!context) return;
  arena = createMatrix(COLS, ROWS);
  player = { pos: {x:0, y:0}, matrix: null };
  dropCounter = 0;
  dropInterval = 800;
  lastTime = 0;
  score = 0;
  running = true;
  playerReset();
  updateScore();
  update();
}

document.addEventListener('keydown', event => {
  if (!running) return;
  if (event.key === 'ArrowLeft') playerMove(-1);
  else if (event.key === 'ArrowRight') playerMove(1);
  else if (event.key === 'ArrowDown') playerDrop();
  else if (event.key === 'q') playerRotate(-1);
  else if (event.key === 'w') playerRotate(1);
});