import * as THREE from 'three';
import './style.css';

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x0b1020);

const camera = new THREE.PerspectiveCamera(
  50,
  window.innerWidth / window.innerHeight,
  0.1,
  100,
);
camera.position.set(0, 5, 10);
camera.lookAt(0, 0, 0);

const orthographicCamera = new THREE.OrthographicCamera(-5, 5, 5, -5, 0.1, 100);
orthographicCamera.position.copy(camera.position);
orthographicCamera.lookAt(0, 0, 0);
let activeCamera = camera;
const cameraInfo = document.getElementById('camera-info');
const viewHeight = 2 * camera.position.length()
  * Math.tan(THREE.MathUtils.degToRad(camera.fov / 2));

const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.shadowMap.enabled = true;
document.getElementById('app').appendChild(renderer.domElement);

const cube = new THREE.Mesh(
  new THREE.BoxGeometry(1, 1, 1),
  new THREE.MeshLambertMaterial({ color: 0x22d3ee }),
);
cube.position.set(-1.4, 0.75, 0);
cube.rotation.set(0.2, 0.4, 0);
cube.scale.set(1.2, 1.2, 1.2);
cube.castShadow = true;
scene.add(cube);

const sphere = new THREE.Mesh(
  new THREE.SphereGeometry(0.7, 32, 16),
  new THREE.MeshPhongMaterial({ color: 0xf59e0b, shininess: 64 }),
);
sphere.position.set(1.4, 0.9, 0);
sphere.castShadow = true;
scene.add(sphere);

// Challenge A: two additional geometries, spaced apart from the other objects.
const cylinder = new THREE.Mesh(
  new THREE.CylinderGeometry(0.5, 0.5, 1.2, 32),
  new THREE.MeshLambertMaterial({ color: 0xa78bfa }),
);
cylinder.position.set(-3, 0.6, 1);
cylinder.rotation.y = 0.3;
cylinder.castShadow = true;
scene.add(cylinder);

const cone = new THREE.Mesh(
  new THREE.ConeGeometry(0.6, 1.4, 32),
  new THREE.MeshPhongMaterial({ color: 0x4ade80, shininess: 32 }),
);
cone.position.set(3, 0.7, 1);
cone.rotation.y = 0.3;
cone.castShadow = true;
scene.add(cone);

// Challenge B: identical geometry and color make material differences visible.
const galleryGeometry = new THREE.SphereGeometry(0.55, 32, 16);
const galleryMaterials = [
  new THREE.MeshBasicMaterial({ color: 0xf472b6 }),
  new THREE.MeshNormalMaterial(),
  new THREE.MeshLambertMaterial({ color: 0xf472b6 }),
  new THREE.MeshPhongMaterial({ color: 0xf472b6, shininess: 64 }),
];

galleryMaterials.forEach((material, index) => {
  const mesh = new THREE.Mesh(galleryGeometry, material);
  mesh.position.set(-3 + index * 2, 0.55, -2);
  mesh.castShadow = true;
  scene.add(mesh);
});

const ground = new THREE.Mesh(
  new THREE.PlaneGeometry(10, 10),
  new THREE.MeshLambertMaterial({ color: 0x475569 }),
);
ground.rotation.x = -Math.PI / 2;
ground.receiveShadow = true;
scene.add(ground);

const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 2);
directionalLight.position.set(3, 5, 4);
directionalLight.castShadow = true;
directionalLight.shadow.mapSize.set(1024, 1024);
Object.assign(directionalLight.shadow.camera, {
  left: -5,
  right: 5,
  top: 5,
  bottom: -5,
  near: 0.5,
  far: 20,
});
scene.add(directionalLight);

// Challenge C: keep both projections responsive, including portrait windows.
function resize() {
  const aspect = window.innerWidth / window.innerHeight;
  camera.aspect = aspect;
  camera.zoom = Math.min(1, aspect * viewHeight / 10);
  camera.updateProjectionMatrix();

  const halfHeight = viewHeight / (2 * camera.zoom);
  orthographicCamera.left = -halfHeight * aspect;
  orthographicCamera.right = halfHeight * aspect;
  orthographicCamera.top = halfHeight;
  orthographicCamera.bottom = -halfHeight;
  orthographicCamera.updateProjectionMatrix();

  renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
  renderer.setSize(window.innerWidth, window.innerHeight);
}

window.addEventListener('resize', resize);
resize();

window.addEventListener('keydown', (event) => {
  if (event.code !== 'KeyP' || event.repeat) return;
  activeCamera = activeCamera === camera ? orthographicCamera : camera;
  cameraInfo.textContent = activeCamera === camera
    ? 'Perspective camera | P: switch projection'
    : 'Orthographic camera | P: switch projection';
});

let previousTime = performance.now();
let elapsed = 0;

function animate(time) {
  const delta = Math.min((time - previousTime) / 1000, 0.05);
  previousTime = time;
  elapsed += delta;

  cube.rotation.y += 0.8 * delta;
  sphere.rotation.y += 0.5 * delta;
  sphere.position.y = 0.9 + Math.sin(elapsed * 2) * 0.15;

  renderer.render(scene, activeCamera);
  requestAnimationFrame(animate);
}

requestAnimationFrame(animate);
