// Assembly verification. Pure: shared by the browser viewer and the Node checker.
//
// input.instances: [{ id, component, matrix }]               (from solveAssembly)
// input.parts[component]: { anchors: {name: Matrix4}, meshes: [{ name, matrix, min, max }] }
//   mesh.matrix is component-local; min/max are the mesh's own POSITION bounds.
// manifest.allowOverlap: [['idPatternA', 'idPatternB'], ...]  ('*' wildcard allowed)
import { Box3, Vector3 } from 'three';

export const TOLERANCE = 0.01; // metres

function globToRegex(p) {
  return new RegExp(`^${p.replace(/[.+?^${}()|[\]\\]/g, '\\$&').replace(/\*/g, '.*')}$`);
}

export function checkAssembly({ instances, parts, manifest, tolerance = TOLERANCE }) {
  const report = { groundErrors: [], overlaps: [], boxes: [] };
  const allow = (manifest.allowOverlap ?? []).map(([a, b]) => [globToRegex(a), globToRegex(b)]);
  const allowed = (a, b) => allow.some(([ra, rb]) => (ra.test(a) && rb.test(b)) || (ra.test(b) && rb.test(a)));

  const boxes = [];
  const p = new Vector3();
  for (const inst of instances) {
    const part = parts[inst.component];
    if (!part) continue;
    for (const [name, m] of Object.entries(part.anchors)) {
      if (!name.startsWith('anchor_ground')) continue;
      p.setFromMatrixPosition(inst.matrix.clone().multiply(m));
      if (Math.abs(p.y) > tolerance) {
        report.groundErrors.push({ instance: inst.id, anchor: name, y: +p.y.toFixed(4) });
      }
    }
    for (const mesh of part.meshes) {
      if (mesh.name.startsWith('col_')) continue;
      const b = new Box3(new Vector3(...mesh.min), new Vector3(...mesh.max))
        .applyMatrix4(inst.matrix.clone().multiply(mesh.matrix));
      boxes.push({ instance: inst.id, mesh: mesh.name, box: b });
    }
  }
  report.boxes = boxes;

  for (let i = 0; i < boxes.length; i++) {
    for (let j = i + 1; j < boxes.length; j++) {
      const A = boxes[i], B = boxes[j];
      if (A.instance === B.instance) continue;
      const dx = Math.min(A.box.max.x, B.box.max.x) - Math.max(A.box.min.x, B.box.min.x);
      const dy = Math.min(A.box.max.y, B.box.max.y) - Math.max(A.box.min.y, B.box.min.y);
      const dz = Math.min(A.box.max.z, B.box.max.z) - Math.max(A.box.min.z, B.box.min.z);
      const depth = Math.min(dx, dy, dz);
      if (depth > tolerance && !allowed(A.instance, B.instance)) {
        report.overlaps.push({
          a: `${A.instance}/${A.mesh}`,
          b: `${B.instance}/${B.mesh}`,
          depth: +depth.toFixed(4),
        });
      }
    }
  }
  report.ok = !report.groundErrors.length && !report.overlaps.length;
  return report;
}
