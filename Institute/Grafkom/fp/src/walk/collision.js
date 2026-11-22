// Pure first-person physics. No DOM, no rendering. Unit-testable in Node.
// state: { position: Vector3 (feet), velocity: Vector3, onGround: boolean }
// input: { forward, right, jump, run, yaw }   forward/right in [-1, 1]
// colliders: Box3[] (world AABBs; only .min/.max are used)
import { Vector3 } from 'three';

export const PLAYER = {
  radius: 0.3,
  eye: 1.6,
  height: 1.8,
  stepUp: 0.35,
  walk: 3,
  run: 6,
  gravity: 22,
  jump: 6.5,
  voidY: -10,
};
export const SPAWN = { x: 0, y: 0, z: 13 };

export function createPlayerState(spawn = SPAWN) {
  return { position: new Vector3(spawn.x, spawn.y, spawn.z), velocity: new Vector3(), onGround: false };
}

// Does the circle (cx, cz, r) touch the box footprint?
function footprintHits(b, cx, cz, r) {
  const px = Math.max(b.min.x, Math.min(cx, b.max.x));
  const pz = Math.max(b.min.z, Math.min(cz, b.max.z));
  const dx = cx - px, dz = cz - pz;
  return dx * dx + dz * dz < r * r;
}

// Push the circle out of an XZ rectangle. Mutates pos (x/z).
function pushOut(pos, b, r) {
  const px = Math.max(b.min.x, Math.min(pos.x, b.max.x));
  const pz = Math.max(b.min.z, Math.min(pos.z, b.max.z));
  let dx = pos.x - px, dz = pos.z - pz;
  const d2 = dx * dx + dz * dz;
  if (d2 >= r * r) return;
  if (d2 > 1e-12) {
    const d = Math.sqrt(d2);
    pos.x = px + (dx / d) * r;
    pos.z = pz + (dz / d) * r;
  } else {
    // centre inside the rectangle: exit through the nearest face
    const l = pos.x - b.min.x, rr = b.max.x - pos.x, f = pos.z - b.min.z, bk = b.max.z - pos.z;
    const m = Math.min(l, rr, f, bk);
    if (m === l) pos.x = b.min.x - r;
    else if (m === rr) pos.x = b.max.x + r;
    else if (m === f) pos.z = b.min.z - r;
    else pos.z = b.max.z + r;
  }
}

function resolveHorizontal(pos, colliders) {
  const { radius, stepUp, height } = PLAYER;
  for (let iter = 0; iter < 3; iter++) {
    for (const b of colliders) {
      if (b.max.y <= pos.y + stepUp) continue; // steppable / below
      if (b.min.y >= pos.y + height) continue; // overhead
      pushOut(pos, b, radius);
    }
  }
}

// Highest collider top under the footprint that is <= limitY. Returns -Infinity if none.
function groundHeight(pos, colliders, limitY) {
  let best = -Infinity;
  for (const b of colliders) {
    if (b.max.y > limitY || b.max.y <= best) continue;
    if (footprintHits(b, pos.x, pos.z, PLAYER.radius * 0.9)) best = b.max.y;
  }
  return best;
}

export function stepPlayer(state, input, colliders, dt) {
  const pos = state.position.clone();
  const vel = state.velocity.clone();
  let onGround = state.onGround;

  // Horizontal intent (camera looks down -Z at yaw 0)
  const sy = Math.sin(input.yaw), cy = Math.cos(input.yaw);
  let mx = -sy * input.forward + cy * input.right;
  let mz = -cy * input.forward - sy * input.right;
  const len = Math.hypot(mx, mz);
  if (len > 1) { mx /= len; mz /= len; }
  const speed = input.run ? PLAYER.run : PLAYER.walk;

  // Sub-step so fast movement cannot tunnel through thin walls.
  const dist = Math.hypot(mx, mz) * speed * dt;
  const n = Math.max(1, Math.ceil(dist / 0.1));
  for (let i = 0; i < n; i++) {
    pos.x += (mx * speed * dt) / n;
    pos.z += (mz * speed * dt) / n;
    resolveHorizontal(pos, colliders);
    // keep feet glued to steps during the sub-steps
    if (onGround) {
      const g = groundHeight(pos, colliders, pos.y + PLAYER.stepUp);
      if (g > pos.y) pos.y = g;
    }
  }

  // Vertical
  if (input.jump && onGround) { vel.y = PLAYER.jump; onGround = false; }
  vel.y -= PLAYER.gravity * dt;
  let newY = pos.y + vel.y * dt;
  const wasGround = onGround;
  // Landing: moving down and crossing a surface that was at/below our old feet (+step tolerance).
  const g = groundHeight(pos, colliders, pos.y + PLAYER.stepUp);
  if (vel.y <= 0 && g > -Infinity && newY <= g) {
    pos.y = g; vel.y = 0; onGround = true;
  } else if (wasGround && vel.y <= 0 && g > -Infinity && pos.y - g <= PLAYER.stepUp && newY <= g + 1e-6) {
    pos.y = g; vel.y = 0; onGround = true;
  } else {
    pos.y = newY; onGround = false;
  }

  if (pos.y < PLAYER.voidY) return createPlayerState();
  return { position: pos, velocity: vel, onGround };
}
