// Minimal GLB writer for Node. Converts a three.js Object3D tree into a binary glTF file.
// Supports: node hierarchy + TRS, meshes (one material each), PBR base colour,
// embedded PNG textures (material.userData.texture = '<file>.png' in assets/textures).
import fs from 'node:fs';
import path from 'node:path';
import * as THREE from 'three';

const TEXTURE_DIR = path.resolve(import.meta.dirname, '../../assets/textures');

const FLOAT = 5126;
const UINT16 = 5123;
const UINT32 = 5125;
const ARRAY_BUFFER = 34962;
const ELEMENT_ARRAY_BUFFER = 34963;

export function writeGLB(outPath, root) {
  const json = {
    asset: { version: '2.0', generator: 'rumah-lamin glb-writer' },
    scene: 0,
    scenes: [{ name: root.name || 'Scene', nodes: [] }],
    nodes: [],
    meshes: [],
    materials: [],
    accessors: [],
    bufferViews: [],
    buffers: [],
  };
  const chunks = [];
  let byteLength = 0;
  const materialIndex = new Map();
  const textureIndex = new Map();

  function pushBytes(bytes, target) {
    const pad = (4 - (byteLength % 4)) % 4;
    if (pad) {
      chunks.push(new Uint8Array(pad));
      byteLength += pad;
    }
    const view = { buffer: 0, byteOffset: byteLength, byteLength: bytes.byteLength };
    if (target) view.target = target;
    json.bufferViews.push(view);
    chunks.push(new Uint8Array(bytes.buffer, bytes.byteOffset, bytes.byteLength));
    byteLength += bytes.byteLength;
    return json.bufferViews.length - 1;
  }

  function addAccessor(array, type, componentType, target, withBounds) {
    const view = pushBytes(array, target);
    const size = { SCALAR: 1, VEC2: 2, VEC3: 3 }[type];
    const acc = { bufferView: view, componentType, count: array.length / size, type };
    if (withBounds) {
      const min = new Array(size).fill(Infinity);
      const max = new Array(size).fill(-Infinity);
      for (let i = 0; i < array.length; i += size) {
        for (let k = 0; k < size; k++) {
          min[k] = Math.min(min[k], array[i + k]);
          max[k] = Math.max(max[k], array[i + k]);
        }
      }
      acc.min = min;
      acc.max = max;
    }
    json.accessors.push(acc);
    return json.accessors.length - 1;
  }

  function addTexture(file) {
    if (textureIndex.has(file)) return textureIndex.get(file);
    const bytes = fs.readFileSync(path.join(TEXTURE_DIR, file));
    json.images ??= [];
    json.textures ??= [];
    json.samplers ??= [{ magFilter: 9729, minFilter: 9987, wrapS: 10497, wrapT: 10497 }];
    const view = pushBytes(new Uint8Array(bytes));
    json.images.push({ name: file, bufferView: view, mimeType: 'image/png' });
    json.textures.push({ sampler: 0, source: json.images.length - 1 });
    const idx = json.textures.length - 1;
    textureIndex.set(file, idx);
    return idx;
  }

  function addMaterial(mat) {
    if (materialIndex.has(mat)) return materialIndex.get(mat);
    const c = mat.color ?? new THREE.Color(1, 1, 1);
    const pbr = {
      baseColorFactor: [c.r, c.g, c.b, mat.opacity ?? 1],
      metallicFactor: mat.metalness ?? 0,
      roughnessFactor: mat.roughness ?? 0.9,
    };
    if (mat.userData?.texture) pbr.baseColorTexture = { index: addTexture(mat.userData.texture) };
    const out = { name: mat.name || `mat_${json.materials.length}`, pbrMetallicRoughness: pbr };
    if (mat.side === THREE.DoubleSide) out.doubleSided = true;
    json.materials.push(out);
    const idx = json.materials.length - 1;
    materialIndex.set(mat, idx);
    return idx;
  }

  function addMesh(mesh) {
    if (Array.isArray(mesh.material)) throw new Error(`${mesh.name}: one material per mesh`);
    const g = mesh.geometry;
    const attributes = {};
    const pos = g.getAttribute('position');
    attributes.POSITION = addAccessor(Float32Array.from(pos.array), 'VEC3', FLOAT, ARRAY_BUFFER, true);
    const nrm = g.getAttribute('normal');
    if (nrm) attributes.NORMAL = addAccessor(Float32Array.from(nrm.array), 'VEC3', FLOAT, ARRAY_BUFFER);
    const uv = g.getAttribute('uv');
    if (uv) attributes.TEXCOORD_0 = addAccessor(Float32Array.from(uv.array), 'VEC2', FLOAT, ARRAY_BUFFER);
    const prim = { attributes, material: addMaterial(mesh.material) };
    if (g.index) {
      const big = pos.count > 65535;
      const arr = big ? Uint32Array.from(g.index.array) : Uint16Array.from(g.index.array);
      prim.indices = addAccessor(arr, 'SCALAR', big ? UINT32 : UINT16, ELEMENT_ARRAY_BUFFER);
    }
    json.meshes.push({ name: mesh.name, primitives: [prim] });
    return json.meshes.length - 1;
  }

  function addNode(obj) {
    const node = { name: obj.name || undefined };
    const p = obj.position, q = obj.quaternion, s = obj.scale;
    if (p.x || p.y || p.z) node.translation = [p.x, p.y, p.z];
    if (q.x || q.y || q.z || q.w !== 1) node.rotation = [q.x, q.y, q.z, q.w];
    if (s.x !== 1 || s.y !== 1 || s.z !== 1) node.scale = [s.x, s.y, s.z];
    if (obj.isMesh) node.mesh = addMesh(obj);
    const idx = json.nodes.push(node) - 1;
    const children = obj.children.map(addNode);
    if (children.length) node.children = children;
    return idx;
  }

  json.scenes[0].nodes = root.children.map(addNode);

  const bin = new Uint8Array(byteLength + ((4 - (byteLength % 4)) % 4));
  let off = 0;
  for (const c of chunks) {
    bin.set(c, off);
    off += c.byteLength;
  }
  json.buffers.push({ byteLength: bin.byteLength });

  let jsonBytes = Buffer.from(JSON.stringify(json));
  const jsonPad = (4 - (jsonBytes.length % 4)) % 4;
  jsonBytes = Buffer.concat([jsonBytes, Buffer.alloc(jsonPad, 0x20)]);

  const total = 12 + 8 + jsonBytes.length + 8 + bin.byteLength;
  const header = Buffer.alloc(12);
  header.writeUInt32LE(0x46546c67, 0);
  header.writeUInt32LE(2, 4);
  header.writeUInt32LE(total, 8);
  const jsonHeader = Buffer.alloc(8);
  jsonHeader.writeUInt32LE(jsonBytes.length, 0);
  jsonHeader.writeUInt32LE(0x4e4f534a, 4);
  const binHeader = Buffer.alloc(8);
  binHeader.writeUInt32LE(bin.byteLength, 0);
  binHeader.writeUInt32LE(0x004e4942, 4);

  fs.mkdirSync(path.dirname(outPath), { recursive: true });
  fs.writeFileSync(outPath, Buffer.concat([header, jsonHeader, jsonBytes, binHeader, Buffer.from(bin)]));
  return { nodes: json.nodes.length, meshes: json.meshes.length, bytes: total };
}
