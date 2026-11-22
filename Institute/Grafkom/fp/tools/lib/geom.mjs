// Shared building blocks for component generators.
import * as THREE from 'three';
import { mergeGeometries } from 'three/addons/utils/BufferGeometryUtils.js';

// ---- Materials (one shared instance per name; textures live in assets/textures) ----
function mat(name, texture, color = 0xffffff, roughness = 0.9) {
  const m = new THREE.MeshStandardMaterial({ name, color, roughness, metalness: 0 });
  if (texture) m.userData.texture = texture;
  return m;
}

export const MAT = {
  kayuGelap: mat('Kayu_Gelap', 'kayu_gelap.png'),
  kayuUlin: mat('Kayu_Ulin', 'kayu_ulin.png'),
  motifGelap: mat('Motif_Gelap', 'motif_gelap.png', 0xffffff, 0.8),
  motifTerang: mat('Motif_Terang', 'motif_terang.png', 0xffffff, 0.8),
  tanah: mat('Tanah', 'tanah.png', 0xffffff, 1),
  whitebox: mat('Whitebox', null, 0xbfbfbf, 1),
  collider: mat('Collider', null, 0xff00ff, 1),
};

// ---- UVs in metres: box projection by dominant normal axis ----
// tile = metres per texture repeat; { u, v } may differ (e.g. motif bands).
// Origin is the geometry's bbox min, so bands start at their bottom edge.
export function meterUVs(geometry, tile = 1) {
  const tu = typeof tile === 'number' ? tile : tile.u;
  const tv = typeof tile === 'number' ? tile : tile.v;
  geometry.computeBoundingBox();
  const min = geometry.boundingBox.min;
  const pos = geometry.getAttribute('position');
  const nrm = geometry.getAttribute('normal');
  const uv = new Float32Array(pos.count * 2);
  for (let i = 0; i < pos.count; i++) {
    const x = pos.getX(i) - min.x, y = pos.getY(i) - min.y, z = pos.getZ(i) - min.z;
    const ax = Math.abs(nrm.getX(i)), ay = Math.abs(nrm.getY(i)), az = Math.abs(nrm.getZ(i));
    let a, b;
    if (ay >= ax && ay >= az) { a = x; b = z; }
    else if (ax >= az) { a = z; b = y; }
    else { a = x; b = y; }
    uv[i * 2] = a / tu;
    uv[i * 2 + 1] = 1 - b / tv; // glTF v=0 is image top
  }
  geometry.setAttribute('uv', new THREE.BufferAttribute(uv, 2));
  return geometry;
}

// Box mesh positioned by its CENTRE.
export function box(name, material, w, h, d, x = 0, y = 0, z = 0, tile = 1) {
  const g = meterUVs(new THREE.BoxGeometry(w, h, d), tile);
  const m = new THREE.Mesh(g, material);
  m.name = name;
  m.position.set(x, y, z);
  return m;
}

// Box mesh positioned by its MIN corner → easier to reason about extents.
export function boxFromMin(name, material, x0, y0, z0, x1, y1, z1, tile = 1) {
  return box(name, material, x1 - x0, y1 - y0, z1 - z0, (x0 + x1) / 2, (y0 + y1) / 2, (z0 + z1) / 2, tile);
}

export function cylinder(name, material, r, h, x = 0, y = 0, z = 0, segments = 12, tile = 1) {
  const g = meterUVs(new THREE.CylinderGeometry(r, r, h, segments), tile);
  const m = new THREE.Mesh(g, material);
  m.name = name;
  m.position.set(x, y, z);
  return m;
}

// Invisible collision box (axis-aligned in component space), defined by min/max corners.
export function collider(name, x0, y0, z0, x1, y1, z1) {
  const m = boxFromMin(name.startsWith('col_') ? name : `col_${name}`, MAT.collider, x0, y0, z0, x1, y1, z1);
  return m;
}

// Empty attachment node. rotY in degrees.
export function anchor(name, x = 0, y = 0, z = 0, rotY = 0) {
  const o = new THREE.Object3D();
  o.name = name.startsWith('anchor_') ? name : `anchor_${name}`;
  o.position.set(x, y, z);
  o.rotation.y = THREE.MathUtils.degToRad(rotY);
  return o;
}

// Merge meshes that share ONE material into a single mesh (bakes their transforms).
export function merge(name, meshes) {
  const material = meshes[0].material;
  const geos = meshes.map((m) => {
    if (m.material !== material) throw new Error(`merge(${name}): mixed materials`);
    m.updateMatrix();
    const g = m.geometry.clone().applyMatrix4(m.matrix);
    return g.index ? g.toNonIndexed() : g;
  });
  const out = new THREE.Mesh(mergeGeometries(geos), material);
  out.name = name;
  return out;
}

export function group(name, ...children) {
  const g = new THREE.Group();
  g.name = name;
  for (const c of children.flat()) g.add(c);
  return g;
}
