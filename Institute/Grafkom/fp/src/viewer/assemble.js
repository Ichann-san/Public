// Loads component GLBs once, solves the anchor assembly, and builds the instance groups.
import { Box3, Group } from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import manifest from '../assembly/manifest.json';
import { solveAssembly } from '../assembly/solve.js';

function analyse(scene) {
  scene.updateMatrixWorld(true);
  const anchors = {};
  const meshes = [];
  scene.traverse((node) => {
    if (node.name && node.name.startsWith('anchor_')) anchors[node.name] = node.matrixWorld.clone();
    if (node.isMesh) {
      const g = node.geometry;
      if (!g.boundingBox) g.computeBoundingBox();
      meshes.push({
        name: node.name,
        matrix: node.matrixWorld.clone(),
        min: g.boundingBox.min.toArray(),
        max: g.boundingBox.max.toArray(),
      });
    }
  });
  return { anchors, meshes };
}

export async function assemble() {
  const loader = new GLTFLoader();
  const loadErrors = [];
  const scenes = {};
  const parts = {};

  await Promise.all(
    Object.entries(manifest.components).map(async ([name, def]) => {
      try {
        const gltf = await loader.loadAsync(import.meta.env.BASE_URL + def.src);
        scenes[name] = gltf.scene;
        parts[name] = analyse(gltf.scene);
      } catch (e) {
        loadErrors.push(`${name} (${def.src}): ${e?.message ?? e}`);
      }
    }),
  );

  const anchorsByComponent = {};
  for (const [name, p] of Object.entries(parts)) anchorsByComponent[name] = p.anchors;
  const solved = solveAssembly(manifest, anchorsByComponent);

  const root = new Group();
  root.name = 'house';
  const instanceGroups = [];
  for (const inst of solved.instances) {
    const g = new Group();
    g.name = inst.id;
    g.matrixAutoUpdate = false;
    g.matrix.copy(inst.matrix);
    g.userData = { id: inst.id, component: inst.component, placeholder: !!manifest.components[inst.component]?.placeholder };
    g.add(scenes[inst.component].clone(true));
    root.add(g);
    instanceGroups.push(g);
  }
  root.updateMatrixWorld(true);

  // col_* meshes: hidden, world boxes collected for walking. Everything else casts/receives shadows.
  const colliders = [];
  root.traverse((n) => {
    if (!n.isMesh) return;
    if (n.name.startsWith('col_')) {
      n.visible = false;
      n.geometry.computeBoundingBox();
      colliders.push(new Box3().copy(n.geometry.boundingBox).applyMatrix4(n.matrixWorld));
    } else {
      n.castShadow = true;
      n.receiveShadow = true;
    }
  });

  return { manifest, root, instanceGroups, instances: solved.instances, solveErrors: solved.errors, parts, colliders, loadErrors };
}
