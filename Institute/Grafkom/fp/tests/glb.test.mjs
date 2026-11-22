import { test, before, after } from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import * as THREE from 'three';
import { writeGLB } from '../tools/lib/glb-writer.mjs';
import { readGLB } from '../tools/lib/glb-reader.mjs';
import { MAT, group, box, merge, anchor, collider, meterUVs } from '../tools/lib/geom.mjs';

let dir, file, buf, json, read, info;

function parseRaw(b) {
  const jl = b.readUInt32LE(12);
  return JSON.parse(b.subarray(20, 20 + jl).toString('utf8'));
}

before(() => {
  dir = fs.mkdtempSync(path.join(os.tmpdir(), 'glbtest-'));
  file = path.join(dir, 'a.glb');
  const inner = group('inner', anchor('deep', 1, 0, 0), box('b', MAT.whitebox, 1, 1, 1));
  inner.position.set(0, 0, 5);
  const outer = group('outer', inner);
  outer.position.set(10, 0, 0);
  outer.rotation.y = Math.PI / 2;
  const root = group('root',
    box('slab', MAT.kayuUlin, 2, 1, 4, 0, 0.5, 0),
    box('slab2', MAT.kayuUlin, 1, 1, 1, 5, 0.5, 0),
    box('plain', MAT.whitebox, 1, 1, 1, 0, 0, 10),
    collider('wall', 0, 0, 0, 1, 2, 3),
    anchor('top', 1, 2, 3),
    anchor('turn', 0, 0, 0, 90),
    outer,
  );
  info = writeGLB(file, root);
  buf = fs.readFileSync(file);
  json = parseRaw(buf);
  read = readGLB(file);
});
after(() => fs.rmSync(dir, { recursive: true, force: true }));

test('header magic, version, total length', () => {
  assert.equal(buf.readUInt32LE(0), 0x46546c67);
  assert.equal(buf.readUInt32LE(4), 2);
  assert.equal(buf.readUInt32LE(8), buf.length);
  assert.equal(info.bytes, buf.length);
});

test('chunks are 4-byte aligned and well-formed', () => {
  const jl = buf.readUInt32LE(12);
  assert.equal(buf.readUInt32LE(16), 0x4e4f534a);
  assert.equal(jl % 4, 0);
  const binOff = 20 + jl;
  const bl = buf.readUInt32LE(binOff);
  assert.equal(buf.readUInt32LE(binOff + 4), 0x004e4942);
  assert.equal(bl % 4, 0);
  assert.equal(binOff + 8 + bl, buf.length);
  assert.equal(json.buffers[0].byteLength, bl);
  for (const v of json.bufferViews) assert.equal(v.byteOffset % 4, 0);
});

test('anchors present with correct translation and rotation', () => {
  assert.ok(read.anchors.anchor_top && read.anchors.anchor_turn);
  const p = new THREE.Vector3().setFromMatrixPosition(read.anchors.anchor_top);
  assert.ok(p.distanceTo(new THREE.Vector3(1, 2, 3)) < 1e-6);
  const q = new THREE.Quaternion().setFromRotationMatrix(read.anchors.anchor_turn);
  const expect = new THREE.Quaternion().setFromAxisAngle(new THREE.Vector3(0, 1, 0), Math.PI / 2);
  assert.ok(Math.abs(Math.abs(q.dot(expect)) - 1) < 1e-6);
  // local +X rotated 90deg about Y points to world -Z
  const d = new THREE.Vector3(1, 0, 0).transformDirection(read.anchors.anchor_turn);
  assert.ok(d.distanceTo(new THREE.Vector3(0, 0, -1)) < 1e-6);
  // raw JSON: rotation stored on the node
  const raw = json.nodes.find((n) => n.name === 'anchor_turn');
  assert.ok(raw.rotation && Math.abs(raw.rotation[1] - Math.SQRT1_2) < 1e-6);
});

test('nested group transforms are composed by the reader', () => {
  const a = read.anchors.anchor_deep;
  assert.ok(a, 'anchor_deep missing');
  // inner (1,0,0)+(0,0,5) = (1,0,5); outer rot +90 about Y maps (x,z)->(z,-x) => (5,0,-1); +(10,0,0)
  const p = new THREE.Vector3().setFromMatrixPosition(a);
  assert.ok(p.distanceTo(new THREE.Vector3(15, 0, -1)) < 1e-5, p.toArray().join());
});

test('mesh POSITION min/max correct', () => {
  const m = read.meshes.find((x) => x.name === 'slab');
  assert.deepEqual(m.min.map((v) => +v.toFixed(6)), [-1, -0.5, -2]);
  assert.deepEqual(m.max.map((v) => +v.toFixed(6)), [1, 0.5, 2]);
  const pos = new THREE.Vector3().setFromMatrixPosition(m.matrix);
  assert.ok(pos.distanceTo(new THREE.Vector3(0, 0.5, 0)) < 1e-6);
});

test('texture image embedded once even when used by 2 meshes', () => {
  assert.equal(json.images.length, 1);
  assert.equal(json.textures.length, 1);
  assert.equal(json.images[0].mimeType, 'image/png');
  assert.equal(json.materials.filter((m) => m.pbrMetallicRoughness.baseColorTexture).length, 1);
  const png = fs.readFileSync(path.resolve(import.meta.dirname, '../assets/textures/kayu_ulin.png'));
  assert.equal(json.bufferViews[json.images[0].bufferView].byteLength, png.length);
});

test('collider mesh name is prefixed col_', () => {
  assert.ok(read.meshes.some((m) => m.name === 'col_wall'));
  assert.ok(!read.meshes.some((m) => m.name === 'wall'));
  assert.equal(collider('col_x', 0, 0, 0, 1, 1, 1).name, 'col_x');
});

test('anchor() prefixes anchor_ only once', () => {
  assert.equal(anchor('anchor_q').name, 'anchor_q');
  assert.equal(anchor('q').name, 'anchor_q');
});

test('merge() rejects mixed materials', () => {
  assert.throws(() => merge('m', [box('a', MAT.whitebox, 1, 1, 1), box('b', MAT.kayuUlin, 1, 1, 1)]), /mixed materials/);
});

test('merge() combines same-material meshes into one mesh', () => {
  const m = merge('m', [box('a', MAT.whitebox, 1, 1, 1, 0, 0, 0), box('b', MAT.whitebox, 1, 1, 1, 3, 0, 0)]);
  m.geometry.computeBoundingBox();
  assert.equal(m.name, 'm');
  assert.ok(Math.abs(m.geometry.boundingBox.min.x + 0.5) < 1e-6);
  assert.ok(Math.abs(m.geometry.boundingBox.max.x - 3.5) < 1e-6);
});

test('writer rejects multi-material mesh', () => {
  const m = new THREE.Mesh(new THREE.BoxGeometry(1, 1, 1), [MAT.whitebox, MAT.kayuUlin]);
  m.name = 'multi';
  assert.throws(() => writeGLB(path.join(dir, 'bad.glb'), group('r', m)), /one material per mesh/);
});

test('reader rejects a non-GLB file', () => {
  const f = path.join(dir, 'junk.glb');
  fs.writeFileSync(f, Buffer.alloc(32));
  assert.throws(() => readGLB(f), /not a GLB/);
});

test('meterUVs: 2 m wide box with tile 1 has u range 0..2', () => {
  const g = meterUVs(new THREE.BoxGeometry(2, 1, 1), 1);
  const uv = g.getAttribute('uv');
  const nrm = g.getAttribute('normal');
  let umin = Infinity, umax = -Infinity;
  for (let i = 0; i < uv.count; i++) {
    if (Math.abs(nrm.getZ(i)) === 1) { // front/back faces span the 2 m width in u
      umin = Math.min(umin, uv.getX(i));
      umax = Math.max(umax, uv.getX(i));
    }
  }
  assert.ok(Math.abs(umin) < 1e-6 && Math.abs(umax - 2) < 1e-6, `${umin}..${umax}`);
});

test('meterUVs: v = 1 - b/tile on side faces; tile scales', () => {
  const g = meterUVs(new THREE.BoxGeometry(2, 1, 1), 1);
  const uv = g.getAttribute('uv'), pos = g.getAttribute('position'), nrm = g.getAttribute('normal');
  for (let i = 0; i < uv.count; i++) {
    if (Math.abs(nrm.getZ(i)) === 1) {
      assert.ok(Math.abs(uv.getY(i) - (1 - (pos.getY(i) + 0.5))) < 1e-6);
    }
  }
  const g2 = meterUVs(new THREE.BoxGeometry(2, 1, 1), { u: 4, v: 0.5 });
  const uv2 = g2.getAttribute('uv'), n2 = g2.getAttribute('normal'), p2 = g2.getAttribute('position');
  for (let i = 0; i < uv2.count; i++) {
    if (Math.abs(n2.getZ(i)) === 1) {
      assert.ok(Math.abs(uv2.getX(i) - (p2.getX(i) + 1) / 4) < 1e-6);
      assert.ok(Math.abs(uv2.getY(i) - (1 - (p2.getY(i) + 0.5) / 0.5)) < 1e-6);
    }
  }
});
