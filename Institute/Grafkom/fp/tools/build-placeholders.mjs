// Generates the whitebox placeholder components into public/components/placeholder/.
// Run: npm run gen:placeholder
import path from 'node:path';
import * as THREE from 'three';
import { MAT, meterUVs, boxFromMin, collider, anchor, group } from './lib/geom.mjs';
import { writeGLB } from './lib/glb-writer.mjs';

const OUT = path.resolve(import.meta.dirname, '../public/components/placeholder');
const W = MAT.whitebox;

// ---- a) atap (roof). Local origin = wall-top centre (world y 5.6). ----
function buildAtap() {
  const eave = boxFromMin('atap_eave', W, -20.4, 0, -5.8, 20.4, 0.3, 7.0);

  // Gable prism: triangle in the Y-Z plane, extruded along X from -19 to 19.
  // ExtrudeGeometry works in its own XY plane and extrudes along +Z. Shape x = -z_world
  // so that the final rotateY(+90deg) maps local z -> world x and local x -> world -z.
  const shape = new THREE.Shape([
    new THREE.Vector2(5.0, 0.3),   // world z -5.0, base rear edge
    new THREE.Vector2(-6.2, 0.3),  // world z +6.2, base front edge
    new THREE.Vector2(-0.6, 4.2),  // ridge at world z 0.6
  ]);
  const g = new THREE.ExtrudeGeometry(shape, { depth: 38, bevelEnabled: false });
  g.translate(0, 0, -19);
  g.rotateY(Math.PI / 2); // extrusion now spans world x -19..19 (normals rotate with it)
  const gable = new THREE.Mesh(meterUVs(g), W);
  gable.name = 'atap_gable';

  const ridge = boxFromMin('atap_ridge', W, -19, 4.2, 0.1, 19, 4.35, 1.1);

  return group('atap', anchor('anchor_base', 0, 0, 0), eave, gable, ridge);
}

// ---- b) interior. Local origin = floor-top centre (world y 2.6). ----
function buildInterior() {
  const H = 2.6;   // partition height
  const T = 0.08;  // partition thickness
  const INNER_X = 17.85;
  const pieces = []; // { name, box: [x0, y0, z0, x1, y1, z1] }

  // Room partitions every 3 m along x, running z -3.95..-1.0
  const partX = [];
  for (let i = 0; i < 12; i++) {
    const x = -16.5 + 3 * i;
    partX.push(x);
    pieces.push({
      name: `partition_room_${String(i + 1).padStart(2, '0')}`,
      box: [x - T / 2, 0, -3.95, x + T / 2, H, -1.0],
    });
  }

  // Front partition at z -1.0 with a 0.9 m opening in the middle of each room.
  const edges = [-INNER_X, ...partX, INNER_X];
  const roomCentres = edges.slice(0, -1).map((e, i) => (e + edges[i + 1]) / 2);
  const openings = roomCentres.map((c) => [c - 0.45, c + 0.45]);
  const segments = [];
  let start = -INNER_X;
  for (const [o0, o1] of openings) {
    if (o0 > start) segments.push([start, o0]);
    start = o1;
  }
  if (start < INNER_X) segments.push([start, INNER_X]);
  segments.forEach(([x0, x1], i) => {
    pieces.push({
      name: `partition_front_${String(i + 1).padStart(2, '0')}`,
      box: [x0, 0, -1.0 - T / 2, x1, H, -1.0 + T / 2],
    });
  });

  const visible = pieces.map((p) => boxFromMin(p.name, W, ...p.box));
  const colliders = pieces.map((p) => collider(`col_${p.name}`, ...p.box));

  // Ceiling slab (visible only, no collider)
  const ceiling = boxFromMin('ceiling_slab', W, -INNER_X, 2.9, -3.95, INNER_X, 2.95, 1.95);

  return group('interior', anchor('anchor_base', 0, 0, 0), ceiling, visible, colliders);
}

// ---- c) patung (guardian statue). Local origin = bottom centre. ----
function buildPatung() {
  const post = boxFromMin('patung_post', W, -0.25, 0, -0.25, 0.25, 4.6, 0.25);
  const head = boxFromMin('patung_head', W, -0.35, 4.6, -0.35, 0.35, 5.3, 0.35);
  const col = collider('col_patung', -0.35, 0, -0.35, 0.35, 5.3, 0.35);
  return group('patung', anchor('anchor_ground', 0, 0, 0), post, head, col);
}

const outputs = [
  ['atap.glb', buildAtap()],
  ['interior.glb', buildInterior()],
  ['patung.glb', buildPatung()],
];

for (const [file, root] of outputs) {
  const info = writeGLB(path.join(OUT, file), root);
  console.log(`${path.relative(process.cwd(), path.join(OUT, file))}: ${info.nodes} nodes, ${info.meshes} meshes, ${info.bytes} bytes`);
}
