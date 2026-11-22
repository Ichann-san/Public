// Integration tests: the generated GLBs in public/components must satisfy docs/contract.md,
// assemble without errors, and be walkable. Run `npm run gen` first if GLBs are stale.
import { test } from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import { Box3, Vector3 } from 'three';
import { readGLB } from '../tools/lib/glb-reader.mjs';
import { solveAssembly } from '../src/assembly/solve.js';
import { checkAssembly } from '../src/assembly/check.js';
import { createPlayerState, stepPlayer } from '../src/walk/collision.js';

const manifest = JSON.parse(fs.readFileSync(new URL('../src/assembly/manifest.json', import.meta.url)));
const parts = {};
for (const [name, c] of Object.entries(manifest.components)) {
  parts[name] = readGLB(new URL(`../public/${c.src}`, import.meta.url));
}
const anchorsBy = Object.fromEntries(Object.entries(parts).map(([k, p]) => [k, p.anchors]));
const solved = solveAssembly(manifest, anchorsBy);
const byId = Object.fromEntries(solved.instances.map((i) => [i.id, i]));

const EPS = 1e-4;
const pos = (m) => new Vector3().setFromMatrixPosition(m);
const near = (a, b, msg) => assert.ok(Math.abs(a - b) < EPS, `${msg}: ${a} != ${b}`);

// World bounds of an instance's visible meshes (optionally filtered by mesh-name prefix).
function bounds(id, prefix = '') {
  const inst = byId[id];
  const out = new Box3();
  for (const m of parts[inst.component].meshes) {
    if (m.name.startsWith('col_') || !m.name.startsWith(prefix)) continue;
    out.union(new Box3(new Vector3(...m.min), new Vector3(...m.max)).applyMatrix4(inst.matrix.clone().multiply(m.matrix)));
  }
  return out;
}

// ---- Contract section 4: anchors per component (local coordinates) ----
const REQUIRED = {
  tanah: { anchor_house: [0, 0, 0] },
  lantai: {
    anchor_base: [0, -2.6, 0], anchor_dinding: [0, 0, 0], anchor_pagar: [0, 0, 5.4], anchor_interior: [0, 0, 0],
    anchor_tangga_kiri: [-15, 0, 5.4], anchor_tangga_tengah: [0, 0, 5.4], anchor_tangga_kanan: [15, 0, 5.4],
  },
  tiang: { anchor_ground: [0, 0, 0], anchor_top: [0, 2.4, 0] },
  dinding: { anchor_base: [0, 0, 0], anchor_atap: [0, 3.0, 0] },
  pagar: { anchor_base: [0, 0, 0] },
  tangga: { anchor_top: [0, 0, 0], anchor_patung_kiri: [-2, -2.6, 2.4], anchor_patung_kanan: [2, -2.6, 2.4] },
  atap: { anchor_base: [0, 0, 0] },
  interior: { anchor_base: [0, 0, 0] },
  patung: { anchor_ground: [0, 0, 0] },
};

for (const [comp, anchors] of Object.entries(REQUIRED)) {
  test(`contract: ${comp} has required anchors at contract positions`, () => {
    for (const [name, xyz] of Object.entries(anchors)) {
      const m = parts[comp].anchors[name];
      assert.ok(m, `${comp} missing ${name}`);
      const p = pos(m);
      near(p.x, xyz[0], `${comp}.${name}.x`);
      near(p.y, xyz[1], `${comp}.${name}.y`);
      near(p.z, xyz[2], `${comp}.${name}.z`);
    }
  });
}

test('contract: lantai has 52 pillar anchors on the 13 x 4 grid at y = -0.2', () => {
  const pillars = Object.entries(parts.lantai.anchors).filter(([n]) => n.startsWith('anchor_tiang_'));
  assert.equal(pillars.length, 52);
  const xs = new Set(), zs = new Set();
  for (const [, m] of pillars) {
    const p = pos(m);
    near(p.y, -0.2, 'pillar anchor y');
    xs.add(p.x.toFixed(2));
    zs.add(p.z.toFixed(2));
  }
  assert.equal(xs.size, 13);
  assert.deepEqual([...zs].map(Number).sort((a, b) => a - b), [-4.1, -1, 2.1, 5.2]);
});

test('contract: every component except tanah/atap has col_ colliders', () => {
  for (const comp of ['lantai', 'tiang', 'dinding', 'pagar', 'tangga', 'interior', 'patung']) {
    assert.ok(parts[comp].meshes.some((m) => m.name.startsWith('col_')), `${comp} has no col_ mesh`);
  }
});

// ---- Assembly ----
test('assembly: solves 63 instances (11 + 52 pillars) without errors', () => {
  assert.deepEqual(solved.errors, []);
  assert.equal(solved.instances.length, 63);
  assert.equal(solved.instances.filter((i) => i.component === 'tiang').length, 52);
});

test('assembly: check passes (ground contact + no overlaps > 1 cm)', () => {
  const r = checkAssembly({ instances: solved.instances, parts, manifest });
  assert.deepEqual(r.groundErrors, []);
  assert.deepEqual(r.overlaps, []);
  assert.ok(r.ok);
});

// ---- Contract section 5: key world dimensions ----
test('world: deck slab y 2.4..2.6, x ±18.4, z -4.3..5.4', () => {
  const b = bounds('lantai');
  near(b.min.y, 2.4, 'deck bottom'); near(b.max.y, 2.6, 'deck top');
  near(b.min.x, -18.4, 'deck -x'); near(b.max.x, 18.4, 'deck +x');
  near(b.min.z, -4.3, 'deck back'); near(b.max.z, 5.4, 'deck front');
});

test('world: every pillar spans ground (0) to deck bottom (2.4)', () => {
  for (const inst of solved.instances.filter((i) => i.component === 'tiang')) {
    const b = bounds(inst.id);
    near(b.min.y, 0, `${inst.id} bottom`);
    near(b.max.y, 2.4, `${inst.id} top`);
  }
});

test('world: walls sit on the deck, top at 5.6, inside x ±18 / z -4.1..2.1 (frames ≤ 2.15)', () => {
  const b = bounds('dinding', 'dinding_');
  near(b.min.y, 2.6, 'wall base'); near(b.max.y, 5.6, 'wall top');
  assert.ok(b.min.x >= -18 - EPS && b.max.x <= 18 + EPS);
  assert.ok(b.min.z >= -4.1 - EPS && b.max.z <= 2.15 + EPS, `wall z ${b.min.z}..${b.max.z}`);
});

test('world: roof posts end exactly at roof base (y 5.6), balustrade stays on the deck', () => {
  const b = bounds('pagar');
  near(b.min.y, 2.6, 'pagar base');
  near(b.max.y, 5.6, 'post top');
  assert.ok(b.max.z <= 5.4 + EPS, `pagar front ${b.max.z}`);
});

test('world: each stair runs from deck top (2.6) at z 5.4 down to the ground', () => {
  for (const id of ['tangga_kiri', 'tangga_tengah', 'tangga_kanan']) {
    const treads = bounds(id, 'tangga_treads');
    assert.ok(treads.max.y <= 2.6 + EPS, `${id} treads above deck: ${treads.max.y}`);
    const all = bounds(id);
    assert.ok(all.min.y >= -EPS, `${id} below ground: ${all.min.y}`);
    assert.ok(all.min.z >= 5.4 - EPS, `${id} intrudes into deck: ${all.min.z}`);
    near(pos(byId[id].matrix).y, 2.6, `${id} top anchor`);
  }
  near(pos(byId.tangga_kiri.matrix).x, -15, 'left stair x');
  near(pos(byId.tangga_kanan.matrix).x, 15, 'right stair x');
});

test('world: statues stand on the ground beside the centre stair', () => {
  for (const [id, x] of [['patung_kiri', -2], ['patung_kanan', 2]]) {
    const b = bounds(id);
    near(b.min.y, 0, `${id} base`);
    near((b.min.x + b.max.x) / 2, x, `${id} x`);
    near((b.min.z + b.max.z) / 2, 7.8, `${id} z`);
  }
});

test('world: roof placeholder starts at wall top and stays within contract box', () => {
  const b = bounds('atap');
  near(b.min.y, 5.6, 'roof base');
  assert.ok(b.max.y <= 12.3 + EPS && b.min.x >= -20.4 - EPS && b.max.x <= 20.4 + EPS);
  assert.ok(b.min.z >= -5.8 - EPS && b.max.z <= 7.0 + EPS);
});

test('world: interior placeholder fits inside the walls', () => {
  const b = bounds('interior');
  assert.ok(b.min.x >= -17.88 && b.max.x <= 17.88, `interior x ${b.min.x}..${b.max.x}`);
  assert.ok(b.min.z >= -3.98 && b.max.z <= 1.98, `interior z ${b.min.z}..${b.max.z}`);
  assert.ok(b.min.y >= 2.6 - EPS && b.max.y <= 5.6 + EPS);
});

// ---- Walkability on the real colliders ----
const colliders = [];
for (const inst of solved.instances) {
  for (const m of parts[inst.component].meshes) {
    if (!m.name.startsWith('col_')) continue;
    colliders.push(new Box3(new Vector3(...m.min), new Vector3(...m.max)).applyMatrix4(inst.matrix.clone().multiply(m.matrix)));
  }
}

function walk(start, input, seconds) {
  let s = createPlayerState(start);
  let maxY = s.position.y;
  for (let n = 0; n < seconds * 60; n++) {
    s = stepPlayer(s, { forward: 0, right: 0, jump: false, run: false, yaw: 0, ...input }, colliders, 1 / 60);
    maxY = Math.max(maxY, s.position.y);
  }
  return { s, maxY };
}

test('walk: each staircase climbs from the ground onto the deck', () => {
  for (const x of [-15, 0, 15]) {
    const { s } = walk({ x, y: 0, z: 12 }, { forward: 1 }, 3.2);
    near(s.position.y, 2.6, `stair x=${x} height`);
    assert.ok(s.position.z < 5.4, `stair x=${x} reached deck (z=${s.position.z})`);
  }
});

test('walk: centre door leads into the house and the back wall stops the player', () => {
  const { s } = walk({ x: 0, y: 0, z: 13 }, { forward: 1 }, 7);
  near(s.position.y, 2.6, 'floor height');
  near(s.position.z, -3.98 + 0.3, 'stopped at back wall inner face + radius');
});

test('walk: front wall blocks where there is no door', () => {
  const { s } = walk({ x: -7.5, y: 2.6, z: 4 }, { forward: 1 }, 2);
  near(s.position.z, 2.1 + 0.3, 'stopped at front wall');
});

test('walk: veranda balustrade stops the player walking off the deck', () => {
  const { s } = walk({ x: -7.5, y: 2.6, z: 3 }, { forward: -1 }, 2);
  near(s.position.y, 2.6, 'still on deck');
  assert.ok(s.position.z < 5.4, `fell off deck (z=${s.position.z})`);
});
