import { test } from 'node:test';
import assert from 'node:assert/strict';
import { Matrix4, Vector3, MathUtils } from 'three';
import { solveAssembly } from '../src/assembly/solve.js';

const T = (x = 0, y = 0, z = 0, rotYDeg = 0) =>
  new Matrix4().makeRotationY(MathUtils.degToRad(rotYDeg)).setPosition(x, y, z);
const pos = (m) => new Vector3().setFromMatrixPosition(m);
const near = (a, b, eps = 1e-9) => {
  assert.ok(Math.abs(a.x - b.x) < eps && Math.abs(a.y - b.y) < eps && Math.abs(a.z - b.z) < eps,
    `expected ${a.toArray()} ~ ${b.toArray()}`);
};
const byId = (r, id) => r.instances.find((i) => i.id === id);
const worldAnchor = (inst, anchors, name) => pos(inst.matrix.clone().multiply(anchors[name]));

const anchors = {
  base: {
    anchor_top: T(0, 2, 0),
    anchor_side: T(1, 0, 0, 90),
    anchor_tiang_00: T(0, 0, 0),
    anchor_tiang_01: T(1, 0, 0),
    anchor_tiang_02: T(2, 0, 0),
  },
  child: { anchor_bottom: T(0, -0.5, 0), anchor_off: T(0.3, 0.1, 0.2) },
  tiang: { anchor_foot: T(0, 0, 0) },
};

test('root instance at identity', () => {
  const r = solveAssembly({ instances: [{ id: 'a', component: 'base' }] }, anchors);
  assert.deepEqual(r.errors, []);
  const a = byId(r, 'a');
  assert.ok(a.matrix.equals(new Matrix4()));
  assert.equal(a.parent, null);
});

test('root with position and rotationY', () => {
  const r = solveAssembly({ instances: [{ id: 'a', component: 'base', position: [1, 2, 3], rotationY: 90 }] }, anchors);
  const m = byId(r, 'a').matrix;
  near(pos(m), new Vector3(1, 2, 3));
  // local +X maps to world -Z after +90deg about Y
  near(new Vector3(1, 0, 0).applyMatrix4(m), new Vector3(1, 2, 2));
});

test('child anchor coincides with parent anchor', () => {
  const r = solveAssembly({
    instances: [
      { id: 'p', component: 'base', position: [5, 0, -2], rotationY: 30 },
      { id: 'c', component: 'child', attach: { anchor: 'anchor_off', to: 'p.anchor_top' } },
    ],
  }, anchors);
  assert.deepEqual(r.errors, []);
  const p = byId(r, 'p'), c = byId(r, 'c');
  near(worldAnchor(c, anchors.child, 'anchor_off'), worldAnchor(p, anchors.base, 'anchor_top'));
  assert.equal(c.parent, 'p');
  assert.equal(c.joint, 'anchor_off -> p.anchor_top');
});

test('rotated parent anchor rotates the child', () => {
  const r = solveAssembly({
    instances: [
      { id: 'p', component: 'base' },
      { id: 'c', component: 'child', attach: { anchor: 'anchor_bottom', to: 'p.anchor_side' } },
    ],
  }, anchors);
  const p = byId(r, 'p'), c = byId(r, 'c');
  near(worldAnchor(c, anchors.child, 'anchor_bottom'), worldAnchor(p, anchors.base, 'anchor_side'));
  // child local +X must follow parent anchor's rotated +X (90deg about Y => world -Z)
  near(new Vector3(1, 0, 0).transformDirection(c.matrix), new Vector3(0, 0, -1));
});

test('attach.rotationY rotates child about the joint', () => {
  const mk = (rot) => solveAssembly({
    instances: [
      { id: 'p', component: 'base' },
      { id: 'c', component: 'child', attach: { anchor: 'anchor_bottom', to: 'p.anchor_top', rotationY: rot } },
    ],
  }, anchors);
  const c = byId(mk(90), 'c');
  near(worldAnchor(c, anchors.child, 'anchor_bottom'), new Vector3(0, 2, 0));
  near(new Vector3(1, 0, 0).transformDirection(c.matrix), new Vector3(0, 0, -1));
  near(new Vector3(1, 0, 0).transformDirection(byId(mk(0), 'c').matrix), new Vector3(1, 0, 0));
});

test('wildcard expands into one instance per match', () => {
  const r = solveAssembly({
    instances: [
      { id: 'p', component: 'base', position: [0, 1, 0] },
      { id: 'tiang', component: 'tiang', attach: { anchor: 'anchor_foot', to: 'p.anchor_tiang_*' } },
    ],
  }, anchors);
  assert.deepEqual(r.errors, []);
  assert.deepEqual(r.instances.map((i) => i.id).sort(), ['p', 'tiang_00', 'tiang_01', 'tiang_02']);
  near(pos(byId(r, 'tiang_01').matrix), new Vector3(1, 1, 0));
  near(pos(byId(r, 'tiang_02').matrix), new Vector3(2, 1, 0));
  assert.equal(byId(r, 'tiang_01').joint, 'anchor_foot -> p.anchor_tiang_01');
});

test('instance order independence (child listed before parent)', () => {
  const r = solveAssembly({
    instances: [
      { id: 'c', component: 'child', attach: { anchor: 'anchor_bottom', to: 'p.anchor_top' } },
      { id: 'p', component: 'base', position: [1, 0, 1] },
    ],
  }, anchors);
  assert.deepEqual(r.errors, []);
  near(worldAnchor(byId(r, 'c'), anchors.child, 'anchor_bottom'), new Vector3(1, 2, 1));
});

test('error: unknown component', () => {
  const r = solveAssembly({ instances: [{ id: 'x', component: 'nope' }] }, anchors);
  assert.equal(r.errors.length, 1);
  assert.match(r.errors[0], /x: component "nope" not loaded/);
  assert.equal(r.instances.length, 0);
});

test('error: missing own anchor', () => {
  const r = solveAssembly({
    instances: [
      { id: 'p', component: 'base' },
      { id: 'c', component: 'child', attach: { anchor: 'anchor_zzz', to: 'p.anchor_top' } },
    ],
  }, anchors);
  assert.match(r.errors[0], /own anchor "anchor_zzz" missing in child/);
  assert.equal(byId(r, 'c'), undefined);
});

test('error: missing parent anchor', () => {
  const r = solveAssembly({
    instances: [
      { id: 'p', component: 'base' },
      { id: 'c', component: 'child', attach: { anchor: 'anchor_bottom', to: 'p.anchor_zzz' } },
    ],
  }, anchors);
  assert.equal(r.errors.length, 1);
  assert.match(r.errors[0], /parent anchor "p.anchor_zzz" missing in base/);
  assert.equal(byId(r, 'c'), undefined);
});

test('error: wildcard with no matches', () => {
  const r = solveAssembly({
    instances: [
      { id: 'p', component: 'base' },
      { id: 'c', component: 'child', attach: { anchor: 'anchor_bottom', to: 'p.anchor_nothing_*' } },
    ],
  }, anchors);
  assert.equal(r.errors.length, 1);
  assert.match(r.errors[0], /no anchor matches "p.anchor_nothing_\*"/);
  assert.deepEqual(r.instances.map((i) => i.id), ['p']);
});

test('error: unresolvable parent id', () => {
  const r = solveAssembly({
    instances: [{ id: 'c', component: 'child', attach: { anchor: 'anchor_bottom', to: 'ghost.anchor_top' } }],
  }, anchors);
  assert.equal(r.errors.length, 1);
  assert.match(r.errors[0], /c: parent "ghost.anchor_top" never resolved/);
  assert.equal(r.instances.length, 0);
});
