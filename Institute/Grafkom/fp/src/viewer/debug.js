// Debug overlays: collider wireframes, anchor axes, placeholder highlight.
import { AxesHelper, Box3Helper, Color, Group } from 'three';

export function makeColliderHelpers(colliders) {
  const g = new Group();
  for (const b of colliders) g.add(new Box3Helper(b, new Color(0xff00ff)));
  g.visible = false;
  return g;
}

export function makeAnchorHelpers(instanceGroups, parts) {
  const g = new Group();
  for (const inst of instanceGroups) {
    const part = parts[inst.userData.component];
    if (!part) continue;
    for (const m of Object.values(part.anchors)) {
      const axes = new AxesHelper(0.4);
      axes.matrixAutoUpdate = false;
      axes.matrix.copy(inst.matrix).multiply(m);
      g.add(axes);
    }
  }
  g.visible = false;
  return g;
}

// Clone materials of placeholder instances once, so tinting never touches shared ones.
export function preparePlaceholderMaterials(instanceGroups) {
  const entries = [];
  for (const inst of instanceGroups) {
    if (!inst.userData.placeholder) continue;
    inst.traverse((n) => {
      if (!n.isMesh || n.name.startsWith('col_')) return;
      const orig = n.material;
      const clone = Array.isArray(orig) ? orig.map((m) => m.clone()) : orig.clone();
      entries.push({ mesh: n, orig, clone });
      n.material = clone;
      for (const m of Array.isArray(clone) ? clone : [clone]) {
        m.userData.baseColor = m.color ? m.color.clone() : null;
        m.userData.baseTransparent = m.transparent;
        m.userData.baseOpacity = m.opacity;
      }
    });
  }
  return entries;
}

export function setHighlight(entries, on) {
  const orange = new Color(0xff8a1f);
  for (const { clone } of entries) {
    for (const m of Array.isArray(clone) ? clone : [clone]) {
      if (on) {
        if (m.color && m.userData.baseColor) m.color.copy(m.userData.baseColor).lerp(orange, 0.6);
        m.transparent = true;
        m.opacity = 0.55;
      } else {
        if (m.color && m.userData.baseColor) m.color.copy(m.userData.baseColor);
        m.transparent = m.userData.baseTransparent;
        m.opacity = m.userData.baseOpacity;
      }
      m.needsUpdate = true;
    }
  }
}
