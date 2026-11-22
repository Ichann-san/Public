import { test } from 'node:test';
import assert from 'node:assert/strict';
import { Box3, Vector3 } from 'three';
import { stepPlayer, createPlayerState, PLAYER, SPAWN } from '../src/walk/collision.js';

const box = (x0, y0, z0, x1, y1, z1) => new Box3(new Vector3(x0, y0, z0), new Vector3(x1, y1, z1));
const floor = () => box(-50, -1, -50, 50, 0, 50);
const FWD = { forward: 1, right: 0, jump: false, run: false, yaw: 0 };
const IDLE = { ...FWD, forward: 0 };
const dt = 1 / 60;
const sim = (state, input, colliders, steps) => {
  let s = state;
  for (let i = 0; i < steps; i++) s = stepPlayer(s, input, colliders, dt);
  return s;
};
// Settle onto the floor first so onGround is true.
const grounded = (x, z, colliders) => sim(createPlayerState({ x, y: 0, z }), IDLE, colliders, 5);

test('createPlayerState defaults to SPAWN', () => {
  const s = createPlayerState();
  assert.deepEqual(s.position.toArray(), [SPAWN.x, SPAWN.y, SPAWN.z]);
  assert.equal(s.onGround, false);
});

test('standing on the floor settles onGround at y=0', () => {
  const s = grounded(0, 0, [floor()]);
  assert.equal(s.onGround, true);
  assert.ok(Math.abs(s.position.y) < 1e-9);
});

test('climbs 0.2 m steps to 1.0 m and is blocked by a 1 m wall (radius clearance)', () => {
  const colliders = [floor()];
  for (let i = 0; i < 5; i++) colliders.push(box(-2, 0, -0.4 * (i + 1), 2, 0.2 * (i + 1), -0.4 * i));
  colliders.push(box(-5, 0, -6.5, 5, 1, -6)); // wall front face at z=-6
  let s = createPlayerState({ x: 0, y: 0, z: 3 });
  let maxY = 0;
  for (let t = 0; t < 600; t++) {
    s = stepPlayer(s, FWD, colliders, dt);
    maxY = Math.max(maxY, s.position.y);
  }
  assert.ok(maxY > 0.99, `max height ${maxY}`);
  assert.ok(Math.abs(s.position.y) < 1e-6, `walked off the far side of the stairs back to the floor; final y ${s.position.y}`);
  assert.ok(s.position.z > -6 + PLAYER.radius - 1e-3, `z ${s.position.z}`);
  assert.ok(s.position.z < -5.6, `z ${s.position.z}`);
});

test('blocked by a tall wall with radius clearance', () => {
  const colliders = [floor(), box(-5, 0, -3.5, 5, 3, -3)];
  const s = sim(createPlayerState({ x: 0, y: 0, z: 0 }), FWD, colliders, 300);
  assert.ok(Math.abs(s.position.z - (-3 + PLAYER.radius)) < 1e-6, `z ${s.position.z}`);
  assert.equal(s.position.y, 0);
  assert.equal(s.onGround, true);
});

test('cannot step up a 0.5 m ledge', () => {
  const colliders = [floor(), box(-5, 0, -4, 5, 0.5, -3)];
  const s = sim(grounded(0, 0, colliders), FWD, colliders, 300);
  assert.ok(s.position.y < 1e-6, `y ${s.position.y}`);
  assert.ok(s.position.z >= -3 + PLAYER.radius - 1e-6, `z ${s.position.z}`);
});

test('can step up a 0.35 m ledge', () => {
  const colliders = [floor(), box(-5, 0, -10, 5, 0.35, -3)];
  const s = sim(grounded(0, 0, colliders), FWD, colliders, 90); // ends ~z=-4.5, on the ledge
  assert.ok(Math.abs(s.position.y - 0.35) < 1e-6, `y ${s.position.y}`);
  assert.ok(s.position.z < -3);
  assert.equal(s.onGround, true);
});

test('falls under gravity when walking off a ledge and lands', () => {
  const colliders = [floor(), box(-5, 0, -2, 5, 1, 2)]; // 1 m platform, z in [-2, 2]
  let s = sim(createPlayerState({ x: 0, y: 1, z: 0 }), IDLE, colliders, 5);
  assert.equal(s.onGround, true);
  assert.ok(Math.abs(s.position.y - 1) < 1e-9);
  let sawAir = false;
  for (let i = 0; i < 400; i++) {
    s = stepPlayer(s, FWD, colliders, dt);
    if (!s.onGround) { sawAir = true; assert.ok(s.velocity.y <= 0); }
  }
  assert.ok(sawAir, 'never left the ground');
  assert.ok(s.position.z < -2);
  assert.ok(Math.abs(s.position.y) < 1e-9, `y ${s.position.y}`);
  assert.equal(s.onGround, true);
  assert.equal(s.velocity.y, 0);
});

test('gravity pulls an airborne player down at PLAYER.gravity', () => {
  const s = stepPlayer({ position: new Vector3(0, 5, 0), velocity: new Vector3(), onGround: false }, IDLE, [], dt);
  assert.ok(Math.abs(s.velocity.y + PLAYER.gravity * dt) < 1e-12);
  assert.ok(s.position.y < 5);
  assert.equal(s.onGround, false);
});

test('jump only when onGround', () => {
  const colliders = [floor()];
  const jump = { ...IDLE, jump: true };
  const j = stepPlayer(grounded(0, 0, colliders), jump, colliders, dt);
  assert.ok(j.velocity.y > 5, `vy ${j.velocity.y}`);
  assert.ok(j.position.y > 0);
  assert.equal(j.onGround, false);
  // airborne: jump input must not re-apply the impulse
  const air = { position: new Vector3(0, 3, 0), velocity: new Vector3(), onGround: false };
  const a = stepPlayer(air, jump, colliders, dt);
  assert.ok(a.velocity.y < 0, `vy ${a.velocity.y}`);
});

test('run is faster than walk', () => {
  const colliders = [floor()];
  const start = grounded(0, 0, colliders);
  const w = sim(start, FWD, colliders, 60);
  const r = sim(start, { ...FWD, run: true }, colliders, 60);
  assert.ok(Math.abs(-w.position.z - PLAYER.walk) < 1e-6, `walk ${w.position.z}`);
  assert.ok(Math.abs(-r.position.z - PLAYER.run) < 1e-6, `run ${r.position.z}`);
  assert.ok(-r.position.z > -w.position.z);
});

test('diagonal input is normalised', () => {
  const colliders = [floor()];
  const s = sim(grounded(0, 0, colliders), { ...FWD, right: 1 }, colliders, 60);
  assert.ok(Math.abs(Math.hypot(s.position.x, s.position.z) - PLAYER.walk) < 1e-6);
});

test('falling below voidY respawns at SPAWN with zero velocity', () => {
  // stepPlayer returns createPlayerState() (SPAWN, zero velocity, onGround=false) when y < voidY.
  const s = stepPlayer(
    { position: new Vector3(4, PLAYER.voidY + 0.01, 4), velocity: new Vector3(0, -30, 0), onGround: false },
    IDLE, [], dt);
  assert.deepEqual(s.position.toArray(), [SPAWN.x, SPAWN.y, SPAWN.z]);
  assert.deepEqual(s.velocity.toArray(), [0, 0, 0]);
  assert.equal(s.onGround, false);
});

test('above voidY does not respawn', () => {
  const s = stepPlayer({ position: new Vector3(4, 0, 4), velocity: new Vector3(), onGround: false }, IDLE, [], dt);
  assert.equal(s.position.x, 4);
});

test('yaw rotates movement direction', () => {
  // From the code: mx = -sin(yaw)*forward + cos(yaw)*right; mz = -cos(yaw)*forward - sin(yaw)*right.
  // yaw=0: forward -> -Z, right -> +X.  yaw=+PI/2: forward -> -X, right -> -Z.
  const colliders = [floor()];
  const start = grounded(0, 0, colliders);
  const f = sim(start, { ...FWD, yaw: Math.PI / 2 }, colliders, 30);
  assert.ok(f.position.x < -1.4 && Math.abs(f.position.z) < 1e-6, `${f.position.toArray()}`);
  const r = sim(start, { ...IDLE, right: 1, yaw: Math.PI / 2 }, colliders, 30);
  assert.ok(r.position.z < -1.4 && Math.abs(r.position.x) < 1e-6, `${r.position.toArray()}`);
  const z = sim(start, FWD, colliders, 30);
  assert.ok(z.position.z < -1.4 && Math.abs(z.position.x) < 1e-6);
});
