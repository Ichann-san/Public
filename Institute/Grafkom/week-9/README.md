# Three.js Mini 3D Scene

Task 82 implementation using Node.js, Vite, and Three.js, with Challenges A–C
(sections 83–85).

The scene contains a cube (`BoxGeometry`), a sphere (`SphereGeometry`), and ground
(`PlaneGeometry`). The cube and ground use `MeshLambertMaterial`; the sphere uses
`MeshPhongMaterial`. Lighting uses `AmbientLight` and `DirectionalLight`.

Shadow mapping is enabled on the renderer and DirectionalLight at 1024 × 1024.
The cube and sphere have `castShadow` enabled; the ground has `receiveShadow`
enabled. The cube rotates; the sphere rotates and bobs vertically. Animation uses
`requestAnimationFrame` and delta time in seconds. The renderer and camera aspect
update on window resize, with pixel ratio capped at 2.

## Run

```bash
npm install
npm run dev
```

Open the local URL printed by Vite. Animation runs automatically.
Press **P** to switch between perspective and orthographic projection.

To build and preview the production version:

```bash
npm run build
npm run preview
```

## Challenges

- **83 — Additional geometry:** a purple cylinder (`CylinderGeometry`) and green
  cone (`ConeGeometry`), each with its own material and transform, placed apart
  from the other objects.
- **84 — Material gallery:** four identical spheres in the back row, ordered
  left to right: `MeshBasicMaterial`, `MeshNormalMaterial`,
  `MeshLambertMaterial`, and `MeshPhongMaterial`. Basic, Lambert, and Phong share
  the same base color for comparison; Normal derives color from surface normals.
- **85 — OrthographicCamera:** press **P** to toggle projection. Both cameras
  share the same position and target. Resize updates perspective aspect and the
  orthographic frustum, preserving proportions and fitting narrow windows.
