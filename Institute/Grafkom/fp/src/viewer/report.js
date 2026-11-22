// Renders the assembly check into the HUD (textContent only).
import { checkAssembly } from '../assembly/check.js';

function line(parent, text, cls) {
  const d = document.createElement('div');
  if (cls) d.className = cls;
  d.textContent = text;
  parent.appendChild(d);
}

export function runCheck(asm, el) {
  el.textContent = '';
  const { manifest, instances, parts, solveErrors, loadErrors } = asm;
  let report = { groundErrors: [], overlaps: [], ok: false };
  try {
    report = checkAssembly({ instances, parts, manifest });
  } catch (e) {
    loadErrors.push(`checkAssembly threw: ${e?.message ?? e}`);
  }
  const ok = report.ok && !solveErrors.length && !loadErrors.length;
  line(el, ok ? 'Assembly check: PASS' : 'Assembly check: FAIL', ok ? 'pass' : 'fail');
  line(el, `${instances.length} instances, ${report.overlaps.length} overlaps, ${report.groundErrors.length} ground errors`, 'dim');

  if (loadErrors.length) {
    line(el, 'Load errors:', 'err');
    loadErrors.forEach((e) => line(el, '• ' + e, 'err'));
  }
  if (solveErrors.length) {
    line(el, 'Solver errors:', 'err');
    solveErrors.forEach((e) => line(el, '• ' + e, 'err'));
  }
  if (report.groundErrors.length) {
    line(el, 'Ground errors:', 'err');
    report.groundErrors.forEach((g) => line(el, `• ${g.instance}.${g.anchor}: y = ${g.y} m`, 'err'));
  }
  if (report.overlaps.length) {
    line(el, `Overlaps (first 10 of ${report.overlaps.length}):`, 'err');
    report.overlaps.slice(0, 10).forEach((o) => line(el, `• ${o.a} ↔ ${o.b}, ${o.depth} m`));
    console.table(report.overlaps);
  }
  return report;
}
