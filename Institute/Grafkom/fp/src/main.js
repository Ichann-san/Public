import './style.css';
import {
  ACESFilmicToneMapping, Color, DirectionalLight, Euler, Fog, HemisphereLight, PCFShadowMap,
  PerspectiveCamera, Scene, SRGBColorSpace, WebGLRenderer,
} from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { PointerLockControls } from 'three/addons/controls/PointerLockControls.js';
import { assemble } from './viewer/assemble.js';
import { makeAnchorHelpers, makeColliderHelpers, preparePlaceholderMaterials, setHighlight } from './viewer/debug.js';
import { runCheck } from './viewer/report.js';
import { PLAYER, createPlayerState, stepPlayer } from './walk/collision.js';

const app = document.getElementById('app');
const $ = (id) => document.getElementById(id);

const renderer = new WebGLRenderer({ antialias: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.outputColorSpace = SRGBColorSpace;
renderer.toneMapping = ACESFilmicToneMapping;
renderer.toneMappingExposure = 1.0;
renderer.shadowMap.enabled = true;
renderer.shadowMap.type = PCFShadowMap;
app.prepend(renderer.domElement);

const scene = new Scene();
scene.background = new Color(0x87ceeb);
scene.fog = new Fog(0x87ceeb, 90, 260);

const camera = new PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.05, 400);
camera.position.set(28, 14, 32);

scene.add(new HemisphereLight(0xcfe8ff, 0x6b5b45, 1.0));
const sun = new DirectionalLight(0xfff1d6, 2.6);
sun.position.set(25, 40, 30);
sun.target.position.set(0, 3, 2);
sun.castShadow = true;
sun.shadow.mapSize.set(4096, 4096);
Object.assign(sun.shadow.camera, { left: -32, right: 32, top: 24, bottom: -24, near: 1, far: 120 });
sun.shadow.bias = -0.0004;
sun.shadow.normalBias = 0.03;
scene.add(sun, sun.target);

const orbit = new OrbitControls(camera, renderer.domElement);
orbit.target.set(0, 4, 0);
orbit.enableDamping = true;
orbit.maxPolarAngle = Math.PI * 0.495;
orbit.update();

// ---------------------------------------------------------------- walk mode
const pointer = new PointerLockControls(camera, renderer.domElement);
let walking = false;
let player = createPlayerState();
const keys = new Set();
let colliders = [];
let savedOrbit = null;
const modeInfo = $('mode-info');
const crosshair = $('crosshair');

function setMode(walk) {
  walking = walk;
  if (walk) {
    savedOrbit = { pos: camera.position.clone(), target: orbit.target.clone() };
    orbit.enabled = false;
    player = createPlayerState();
    camera.rotation.set(0, 0, 0, 'YXZ'); // facing -Z
    camera.position.set(player.position.x, player.position.y + PLAYER.eye, player.position.z);
    modeInfo.textContent = 'Walk (F: orbit) — click to look, WASD, Shift run, Space jump';
  } else {
    if (pointer.isLocked) pointer.unlock();
    keys.clear();
    if (savedOrbit) {
      camera.position.copy(savedOrbit.pos);
      orbit.target.copy(savedOrbit.target);
    }
    orbit.enabled = true;
    orbit.update();
    modeInfo.textContent = 'Orbit (F: walk)';
  }
  crosshair.hidden = !walk;
}

renderer.domElement.addEventListener('click', () => {
  if (walking && !pointer.isLocked) pointer.lock();
});
window.addEventListener('keydown', (e) => {
  if (e.code === 'KeyF' && !e.repeat) { setMode(!walking); return; }
  if (walking) {
    keys.add(e.code);
    if (e.code === 'Space') e.preventDefault();
  }
});
window.addEventListener('keyup', (e) => keys.delete(e.code));
window.addEventListener('blur', () => keys.clear());

const euler = new Euler(0, 0, 0, 'YXZ');
function updateWalk(dt) {
  if (!pointer.isLocked) return;
  euler.setFromQuaternion(camera.quaternion, 'YXZ');
  const input = {
    forward: (keys.has('KeyW') ? 1 : 0) - (keys.has('KeyS') ? 1 : 0),
    right: (keys.has('KeyD') ? 1 : 0) - (keys.has('KeyA') ? 1 : 0),
    jump: keys.has('Space'),
    run: keys.has('ShiftLeft') || keys.has('ShiftRight'),
    yaw: euler.y,
  };
  player = stepPlayer(player, input, colliders, dt);
  camera.position.set(player.position.x, player.position.y + PLAYER.eye, player.position.z);
}

// ---------------------------------------------------------------- load
const checkEl = $('check');
let placeholderGroups = [];
let helpers = {};
let highlightEntries = [];

async function load() {
  let asm;
  try {
    asm = await assemble();
  } catch (e) {
    checkEl.textContent = '';
    const d = document.createElement('div');
    d.className = 'err';
    d.textContent = 'Assembly failed: ' + (e?.message ?? e);
    checkEl.appendChild(d);
    console.error(e);
    return;
  }
  scene.add(asm.root);
  colliders = asm.colliders;
  placeholderGroups = asm.instanceGroups.filter((g) => g.userData.placeholder);
  highlightEntries = preparePlaceholderMaterials(asm.instanceGroups);
  helpers = {
    colliders: makeColliderHelpers(asm.colliders),
    anchors: makeAnchorHelpers(asm.instanceGroups, asm.parts),
  };
  scene.add(helpers.colliders, helpers.anchors);
  runCheck(asm, checkEl);
  applyOptions();
}

function applyOptions() {
  const showPh = $('opt-placeholders').checked;
  placeholderGroups.forEach((g) => (g.visible = showPh));
  if (helpers.colliders) helpers.colliders.visible = $('opt-colliders').checked;
  if (helpers.anchors) helpers.anchors.visible = $('opt-anchors').checked;
  setHighlight(highlightEntries, $('opt-highlight').checked);
}
['opt-placeholders', 'opt-colliders', 'opt-anchors', 'opt-highlight'].forEach((id) => {
  $(id).addEventListener('change', () => {
    applyOptions();
    $(id).blur(); // keep F / Space going to the page
  });
});

load();

// ---------------------------------------------------------------- loop / resize
window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

let last = performance.now();
renderer.setAnimationLoop((now) => {
  const dt = Math.min((now - last) / 1000, 0.05);
  last = now;
  if (walking) updateWalk(dt);
  else orbit.update();
  renderer.render(scene, camera);
});
