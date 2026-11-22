import { test } from 'node:test';
import assert from 'node:assert/strict';
import { Matrix4 } from 'three';
import { checkAssembly, TOLERANCE } from '../src/assembly/check.js';

const T = (x = 0, y = 0, z = 0) => new Matrix4().makeTranslation(x, y, z);
const mesh = (name, min, max, matrix = new Matrix4()) => ({ name, matrix, min, max });
const unitBox = (name = 'm') => mesh(name, [0, 0, 0], [1, 1, 1]);
const run = (instances, parts, manifest = {}) => checkAssembly({ instances, parts, manifest });
const inst = (id, component, matrix = new Matrix4()) => ({ id, component, matrix });
const boxPart = { anchors: {}, meshes: [unitBox()] };
const groundPart = (y) => ({ anchors: { anchor_ground: T(0, y, 0) }, meshes: [] });

test('tolerance constant is 0.01', () => assert.equal(TOLERANCE, 0.01));

test('ground anchor at y=0 passes', () => {
  const r = run([inst('a', 'g')], { g: groundPart(0) });
  assert.deepEqual(r.groundErrors, []);
  assert.equal(r.ok, true);
});

test('ground anchor at y=0.02 fails', () => {
  const r = run([inst('a', 'g')], { g: { anchors: { anchor_ground_1: T(0, 0.02, 0) }, meshes: [] } });
  assert.deepEqual(r.groundErrors, [{ instance: 'a', anchor: 'anchor_ground_1', y: 0.02 }]);
  assert.equal(r.ok, false);
});

test('ground anchor at y=0.009 passes', () => {
  const r = run([inst('a', 'g')], { g: groundPart(0.009) });
  assert.deepEqual(r.groundErrors, []);
  assert.equal(r.ok, true);
});

test('non-ground anchors are not checked', () => {
  const r = run([inst('a', 'g')], { g: { anchors: { anchor_top: T(0, 5, 0) }, meshes: [] } });
  assert.equal(r.ok, true);
});

test('ground anchor uses instance transform', () => {
  const r = run([inst('a', 'g', T(0, 0.5, 0))], { g: groundPart(0) });
  assert.equal(r.groundErrors.length, 1);
});

test('touching boxes (shared face) do not overlap', () => {
  const r = run([inst('a', 'b'), inst('b', 'b', T(1, 0, 0))], { b: boxPart });
  assert.deepEqual(r.overlaps, []);
  assert.equal(r.ok, true);
});

test('overlap of 0.05 is reported with depth 0.05', () => {
  const r = run([inst('a', 'b'), inst('b', 'b', T(0.95, 0, 0))], { b: boxPart });
  assert.equal(r.overlaps.length, 1);
  assert.equal(r.overlaps[0].depth, 0.05);
  assert.equal(r.overlaps[0].a, 'a/m');
  assert.equal(r.overlaps[0].b, 'b/m');
  assert.equal(r.ok, false);
});

test('overlap of 0.005 is within tolerance', () => {
  const r = run([inst('a', 'b'), inst('b', 'b', T(0.995, 0, 0))], { b: boxPart });
  assert.deepEqual(r.overlaps, []);
  assert.equal(r.ok, true);
});

test('overlap depth is the minimum axis penetration', () => {
  const r = run([inst('a', 'b'), inst('b', 'b', T(0.5, 0.8, 0.1))], { b: boxPart });
  assert.equal(r.overlaps[0].depth, 0.2);
});

test('same-instance overlap is ignored', () => {
  const part = { anchors: {}, meshes: [unitBox('one'), unitBox('two')] };
  const r = run([inst('a', 'p')], { p: part });
  assert.deepEqual(r.overlaps, []);
  assert.equal(r.boxes.length, 2);
});

test('col_* meshes are ignored', () => {
  const part = { anchors: {}, meshes: [mesh('col_wall', [0, 0, 0], [1, 1, 1]), unitBox('vis')] };
  const r = run([inst('a', 'p'), inst('b', 'p', T(5, 0, 0))], { p: part });
  assert.ok(r.boxes.every((b) => !b.mesh.startsWith('col_')));
  assert.equal(r.boxes.length, 2);
  const only = run([inst('a', 'c'), inst('b', 'c')], { c: { anchors: {}, meshes: [mesh('col_x', [0, 0, 0], [1, 1, 1])] } });
  assert.deepEqual(only.overlaps, []);
  assert.equal(only.boxes.length, 0);
});

test('mesh local matrix is applied', () => {
  const part = { anchors: {}, meshes: [mesh('m', [0, 0, 0], [1, 1, 1], T(10, 0, 0))] };
  const r = run([inst('a', 'p'), inst('b', 'p', T(0.5, 0, 0))], { p: part });
  assert.equal(r.overlaps.length, 1);
  assert.equal(r.overlaps[0].depth, 0.5);
});

test('allowOverlap with wildcard suppresses a pair, either order', () => {
  const instances = [inst('lantai_00', 'b'), inst('tiang_01', 'b', T(0.5, 0, 0))];
  assert.equal(run(instances, { b: boxPart }).overlaps.length, 1);
  assert.deepEqual(run(instances, { b: boxPart }, { allowOverlap: [['lantai_*', 'tiang_*']] }).overlaps, []);
  assert.deepEqual(run(instances, { b: boxPart }, { allowOverlap: [['tiang_*', 'lantai_*']] }).overlaps, []);
  const r = run(instances, { b: boxPart }, { allowOverlap: [['lantai_*', 'atap']] });
  assert.equal(r.overlaps.length, 1);
  assert.equal(r.ok, false);
});

test('report.ok reflects errors', () => {
  assert.equal(run([inst('a', 'g')], { g: { anchors: { anchor_ground: T() }, meshes: [unitBox()] } }).ok, true);
  assert.equal(run([inst('a', 'g', T(0, 1, 0))], { g: groundPart(0) }).ok, false);
});

test('instance with unknown component is skipped', () => {
  const r = run([inst('a', 'missing')], {});
  assert.equal(r.ok, true);
  assert.equal(r.boxes.length, 0);
});
