// Anchor-based assembly solver. Pure: shared by the browser viewer and the Node checker.
//
// anchorsByComponent: { [componentName]: { [anchorName]: Matrix4 } }   (component-local)
// manifest.instances: [{ id, component, attach?: { anchor, to: 'parentId.anchorName', rotationY? },
//                        position?: [x,y,z], rotationY? }]
// A '*' in attach.to expands into one instance per matching parent anchor; the matched
// part is appended to the id (tiang + anchor_tiang_03 -> tiang_03).
import { MathUtils, Matrix4 } from 'three';

function rotY(deg = 0) {
  return new Matrix4().makeRotationY(MathUtils.degToRad(deg));
}

function wildcardRegex(pattern) {
  const esc = pattern.replace(/[.+?^${}()|[\]\\]/g, '\\$&').replace('*', '(.+)');
  return new RegExp(`^${esc}$`);
}

export function solveAssembly(manifest, anchorsByComponent) {
  const errors = [];
  const world = new Map(); // instanceId -> { id, component, matrix, parent, joint }
  let pending = manifest.instances.slice();

  while (pending.length) {
    const next = [];
    for (const inst of pending) {
      const anchors = anchorsByComponent[inst.component];
      if (!anchors) {
        errors.push(`${inst.id}: component "${inst.component}" not loaded`);
        continue;
      }
      if (!inst.attach) {
        const m = new Matrix4().multiply(rotY(inst.rotationY));
        if (inst.position) m.setPosition(...inst.position);
        world.set(inst.id, { id: inst.id, component: inst.component, matrix: m, parent: null, joint: null });
        continue;
      }
      const [parentId, parentAnchorPattern] = inst.attach.to.split('.');
      const parent = world.get(parentId);
      if (!parent) {
        next.push(inst);
        continue;
      }
      const childAnchor = anchors[inst.attach.anchor];
      if (!childAnchor) {
        errors.push(`${inst.id}: own anchor "${inst.attach.anchor}" missing in ${inst.component}`);
        continue;
      }
      const parentAnchors = anchorsByComponent[parent.component];
      const targets = [];
      if (parentAnchorPattern.includes('*')) {
        const re = wildcardRegex(parentAnchorPattern);
        for (const name of Object.keys(parentAnchors).sort()) {
          const hit = name.match(re);
          if (hit) targets.push({ name, id: `${inst.id}_${hit[1]}` });
        }
        if (!targets.length) errors.push(`${inst.id}: no anchor matches "${inst.attach.to}"`);
      } else if (parentAnchors[parentAnchorPattern]) {
        targets.push({ name: parentAnchorPattern, id: inst.id });
      } else {
        errors.push(`${inst.id}: parent anchor "${inst.attach.to}" missing in ${parent.component}`);
      }
      const childInv = childAnchor.clone().invert();
      for (const t of targets) {
        const m = parent.matrix.clone()
          .multiply(parentAnchors[t.name])
          .multiply(rotY(inst.attach.rotationY))
          .multiply(childInv);
        world.set(t.id, {
          id: t.id,
          component: inst.component,
          matrix: m,
          parent: parentId,
          joint: `${inst.attach.anchor} -> ${parentId}.${t.name}`,
        });
      }
    }
    if (next.length === pending.length) {
      for (const inst of next) errors.push(`${inst.id}: parent "${inst.attach.to}" never resolved (cycle or missing)`);
      break;
    }
    pending = next;
  }
  return { instances: [...world.values()], errors };
}
