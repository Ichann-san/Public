// Assembly checker (Node, no browser). Run: npm run check
// Exit code 0 when the assembly passes, 1 otherwise.
import fs from 'node:fs';
import path from 'node:path';
import { readGLB } from './lib/glb-reader.mjs';
import { solveAssembly } from '../src/assembly/solve.js';
import { checkAssembly } from '../src/assembly/check.js';

const ROOT = path.resolve(import.meta.dirname, '..');
const MAX_OVERLAPS = 30;

const manifest = JSON.parse(fs.readFileSync(path.join(ROOT, 'src/assembly/manifest.json'), 'utf8'));

let errorCount = 0;
const anchorsByComponent = {};
const parts = {};

// 1. Load component GLBs; a broken component is reported and skipped, the rest still checked.
for (const [name, comp] of Object.entries(manifest.components)) {
  const rel = `public/${comp.src}`;
  const file = path.join(ROOT, rel);
  if (!fs.existsSync(file)) {
    console.log(`ERROR missing component "${name}": ${rel} not found`);
    errorCount++;
    continue;
  }
  try {
    const glb = readGLB(file);
    parts[name] = glb;
    anchorsByComponent[name] = glb.anchors;
  } catch (e) {
    console.log(`ERROR cannot read component "${name}": ${rel}: ${e.message}`);
    errorCount++;
  }
}

// 2. Solve placement and verify.
const { instances, errors: solverErrors } = solveAssembly(manifest, anchorsByComponent);
const report = checkAssembly({ instances, parts, manifest });

const placeholderById = new Map(
  instances.map((i) => [i.id, Boolean(manifest.components[i.component]?.placeholder)]),
);
// Overlap refs look like "instanceId/meshName"; instance ids never contain '/'.
const tag = (ref) => (placeholderById.get(ref.slice(0, ref.indexOf('/'))) ? ' [placeholder]' : '');

console.log(`Instances: ${instances.length}`);

console.log(`Solver errors: ${solverErrors.length}`);
for (const e of solverErrors) console.log(`  ${e}`);
errorCount += solverErrors.length;

console.log(`Ground contact errors: ${report.groundErrors.length}`);
for (const g of report.groundErrors) {
  console.log(`  ${g.instance} ${g.anchor}: y=${g.y} (expected 0 +/- 0.01)`);
}
errorCount += report.groundErrors.length;

const overlaps = [...report.overlaps].sort((x, y) => y.depth - x.depth);
console.log(`Overlaps: ${overlaps.length}`);
for (const o of overlaps.slice(0, MAX_OVERLAPS)) {
  console.log(`  depth ${o.depth.toFixed(4)} m  ${o.a}${tag(o.a)}  <->  ${o.b}${tag(o.b)}`);
}
if (overlaps.length > MAX_OVERLAPS) console.log(`  ... and ${overlaps.length - MAX_OVERLAPS} more`);
errorCount += overlaps.length;

if (errorCount === 0) {
  console.log('CHECK PASSED');
  process.exitCode = 0;
} else {
  console.log(`CHECK FAILED (${errorCount} errors)`);
  process.exitCode = 1;
}
