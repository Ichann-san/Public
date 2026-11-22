// Generates the exterior components of the Rumah Lamin (see docs/contract.md).
import fs from 'node:fs';
import path from 'node:path';
import { MAT, box, boxFromMin, cylinder, collider, anchor, merge, group } from './lib/geom.mjs';
import { writeGLB } from './lib/glb-writer.mjs';

const OUT = path.resolve(import.meta.dirname, '../public/components/exterior');
fs.mkdirSync(OUT, { recursive: true });
const f2 = (n) => String(n).padStart(2, '0');

function emit(name, root) {
  const file = path.join(OUT, `${name}.glb`);
  writeGLB(file, root);
  let meshes = 0;
  root.traverse((o) => { if (o.isMesh) meshes++; });
  console.log(`${name}.glb: ${root.children.length} nodes, ${meshes} meshes, ${fs.statSync(file).size} bytes`);
}

// ---------------- tanah ----------------
function tanah() {
  const slab = box('tanah_slab', MAT.tanah, 80, 0.1, 50, 0, -0.05, 0, 4);
  return group('tanah', slab, collider('col_tanah', -40, -0.1, -25, 40, 0, 25), anchor('anchor_house', 0, 0, 0));
}

// ---------------- lantai ----------------
function lantai() {
  const slab = boxFromMin('lantai_slab', MAT.kayuUlin, -18.4, -0.2, -4.3, 18.4, 0, 5.4, 1);
  const kids = [slab, collider('col_lantai', -18.4, -0.2, -4.3, 18.4, 0, 5.4),
    anchor('anchor_base', 0, -2.6, 0), anchor('anchor_dinding', 0, 0, 0), anchor('anchor_interior', 0, 0, 0),
    anchor('anchor_pagar', 0, 0, 5.4), anchor('anchor_tangga_kiri', -15, 0, 5.4),
    anchor('anchor_tangga_tengah', 0, 0, 5.4), anchor('anchor_tangga_kanan', 15, 0, 5.4)];
  let n = 0;
  for (const z of [-4.1, -1.0, 2.1, 5.2])
    for (let c = 0; c < 13; c++) kids.push(anchor(`anchor_tiang_${f2(n++)}`, -18 + 3 * c, -0.2, z));
  return group('lantai', kids);
}

// ---------------- tiang ----------------
function tiang() {
  const merged = merge('tiang_body', [
    cylinder('base', MAT.kayuUlin, 0.2, 0.2, 0, 0.1, 0, 8),
    cylinder('shaft', MAT.kayuUlin, 0.16, 1.8, 0, 1.1, 0, 8),
    cylinder('ring', MAT.kayuUlin, 0.19, 0.08, 0, 1.2, 0, 8),
    cylinder('cap', MAT.kayuUlin, 0.2, 0.2, 0, 2.3, 0, 8),
  ]);
  return group('tiang', merged, collider('col_tiang', -0.16, 0, -0.16, 0.16, 2.4, 0.16),
    anchor('anchor_ground', 0, 0, 0), anchor('anchor_top', 0, 2.4, 0));
}

// ---------------- dinding ----------------
function dinding() {
  const H = 3.0, doors = [-15, 0, 15], DW = 1.2, DH = 2.1;
  const wood = [], cols = [];
  const seg = (name, x0, y0, z0, x1, y1, z1) => {
    wood.push(boxFromMin(name, MAT.kayuGelap, x0, y0, z0, x1, y1, z1));
    cols.push(collider(`col_${name}`, x0, y0, z0, x1, y1, z1));
  };
  const edges = [-18];
  for (const d of doors) edges.push(d - DW / 2, d + DW / 2);
  edges.push(18);
  for (let i = 0; i < edges.length; i += 2) seg(`front_${i / 2}`, edges[i], 0, 1.98, edges[i + 1], H, 2.1);
  for (const d of doors) seg(`lintel_${d}`, d - DW / 2, DH, 1.98, d + DW / 2, H, 2.1);
  seg('back', -18, 0, -4.1, 18, H, -3.98);
  seg('side_l', -18, 0, -3.98, -17.88, H, 1.98);
  seg('side_r', 17.88, 0, -3.98, 18, H, 1.98);
  const fr = [];
  for (const d of doors) {
    const a = d - DW / 2, b = d + DW / 2;
    fr.push(boxFromMin('fl', MAT.kayuGelap, a - 0.08, 0, 2.1, a, DH + 0.08, 2.14));
    fr.push(boxFromMin('fr', MAT.kayuGelap, b, 0, 2.1, b + 0.08, DH + 0.08, 2.14));
    fr.push(boxFromMin('fh', MAT.kayuGelap, a - 0.08, DH, 2.1, b + 0.08, DH + 0.08, 2.14));
  }
  const band = boxFromMin('dinding_motif', MAT.motifGelap, -18, 2.3, 2.1, 18, 2.9, 2.12, { u: 1.2, v: 0.6 });
  // One mesh per wall so each bounding box stays thin (a single merged mesh would
  // enclose the whole interior and trip the overlap check).
  const byName = (p) => wood.filter((m) => m.name.startsWith(p));
  return group('dinding',
    merge('dinding_depan', [...byName('front_'), ...byName('lintel_'), ...fr]),
    merge('dinding_belakang', byName('back')),
    merge('dinding_kiri', byName('side_l')),
    merge('dinding_kanan', byName('side_r')),
    band, cols,
    anchor('anchor_base', 0, 0, 0), anchor('anchor_atap', 0, H, 0));
}

// ---------------- pagar ----------------
function pagar() {
  const gaps = [-15, 0, 15], HG = 0.7;
  const xs = [-18.3];
  for (const g of gaps) xs.push(g - HG, g + HG);
  xs.push(18.3);
  const rails = [], panels = [], cols = [];
  for (let i = 0; i < xs.length; i += 2) {
    const x0 = xs[i], x1 = xs[i + 1], z0 = -0.16, z1 = -0.04;
    panels.push(boxFromMin(`bal_panel_${i / 2}`, MAT.motifTerang, x0, 0.1, -0.14, x1, 1.0, -0.06, { u: 2.2, v: 1.1 }));
    rails.push(boxFromMin('rt', MAT.kayuGelap, x0, 1.0, z0, x1, 1.1, z1));
    rails.push(boxFromMin('rb', MAT.kayuGelap, x0, 0, z0, x1, 0.1, z1));
    cols.push(collider(`col_bal_${i / 2}`, x0, 0, z0, x1, 1.1, z1));
  }
  // Side railings are separate meshes (thin bounding boxes) so they can reach the wall
  // front at local z -3.3 without their bbox swallowing the door frames.
  const sides = [];
  for (const s of [-1, 1]) {
    const xa = s * 18.26, xb = s * 18.34, x0 = Math.min(xa, xb), x1 = Math.max(xa, xb);
    const tag = s < 0 ? 'kiri' : 'kanan';
    sides.push(boxFromMin(`pagar_sisi_${tag}_panel`, MAT.motifTerang, x0, 0.1, -3.3, x1, 1.0, -0.04, { u: 2.2, v: 1.1 }));
    sides.push(merge(`pagar_sisi_${tag}_kayu`, [
      boxFromMin('srt', MAT.kayuGelap, x0, 1.0, -3.3, x1, 1.1, -0.04),
      boxFromMin('srb', MAT.kayuGelap, x0, 0, -3.3, x1, 0.1, -0.04),
    ]));
    cols.push(collider(`col_side_${tag}`, x0, 0, -3.3, x1, 1.1, -0.04));
  }
  const posts = [];
  for (let x = -16.5; x <= 16.6; x += 3) posts.push(box('post', MAT.kayuGelap, 0.16, 3.0, 0.16, x, 1.5, -0.1));
  return group('pagar', merge('pagar_kayu', [...rails, ...posts]), merge('pagar_panel', panels), ...sides, ...cols,
    anchor('anchor_base', 0, 0, 0));
}

// ---------------- tangga ----------------
function tangga() {
  const RISE = 0.2, RUN = 0.275, N = 13, W = 0.55;
  const treads = [], strings = [], rail = [], cols = [];
  for (let i = 1; i <= N - 1; i++) {
    const top = -RISE * i, z0 = (i - 1) * RUN, z1 = i * RUN;
    treads.push(boxFromMin(`tread_${i}`, MAT.kayuUlin, -W, top - 0.05, z0, W, top, z1));
    for (const s of [-1, 1]) {
      const xa = s * W, xb = s * (W + 0.06);
      strings.push(boxFromMin('str', MAT.kayuGelap, Math.min(xa, xb), -2.6, z0, Math.max(xa, xb), top, z1));
    }
    cols.push(collider(`col_step_${i}`, -W, -2.6, z0, W, top, z1));
  }
  const PH = 0.9, ang = Math.atan2(RISE, RUN);
  const postIdx = [1, 4, 7, 10, 12];
  const zc = (i) => (i - 0.5) * RUN;
  for (const s of [-1, 1]) {
    for (const i of postIdx) {
      const top = -RISE * i;
      rail.push(box('hp', MAT.kayuGelap, 0.06, PH, 0.06, s * 0.62, top + PH / 2, zc(i)));
    }
    const ia = postIdx[0], ib = postIdx[postIdx.length - 1];
    const ya = -RISE * ia + PH, yb = -RISE * ib + PH, za = zc(ia), zb = zc(ib);
    const L = Math.hypot(zb - za, yb - ya);
    const r = box('hr', MAT.kayuGelap, 0.07, 0.05, L, s * 0.62, (ya + yb) / 2, (za + zb) / 2);
    r.rotation.x = ang;
    rail.push(r);
    cols.push(collider(`col_rail_${s < 0 ? 'l' : 'r'}`, s * 0.62 - 0.03, -2.6, za, s * 0.62 + 0.03, ya, zb));
  }
  return group('tangga', merge('tangga_treads', treads), merge('tangga_kayu', [...strings, ...rail]), ...cols,
    anchor('anchor_top', 0, 0, 0), anchor('anchor_ground', 0, -2.6, 3.6),
    anchor('anchor_patung_kiri', -2, -2.6, 2.4), anchor('anchor_patung_kanan', 2, -2.6, 2.4));
}

emit('tanah', tanah());
emit('lantai', lantai());
emit('tiang', tiang());
emit('dinding', dinding());
emit('pagar', pagar());
emit('tangga', tangga());
