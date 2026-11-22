# Component Contract — Rumah Lamin

Every part of the house is a separate GLB **component**. Components are assembled at
runtime by snapping **anchors** together, as described in `src/assembly/manifest.json`.
Anyone can replace a component (for example, swap a placeholder for a real model made in
Blender) as long as it follows this contract.

## 1. Units and axes

| Rule | Value |
|---|---|
| Unit | 1 unit = 1 metre |
| Up | +Y |
| Front of house | +Z (the stairs and veranda face +Z) |
| Long axis | X (house spans x = -18.4 … +18.4) |
| Ground level | world y = 0 |
| Floor top (house deck) | world y = 2.6 |

Blender users: export glTF with "+Y Up" enabled (the default).

## 2. Component files

| Component | File | Owner | Status |
|---|---|---|---|
| tanah (ground) | `public/components/exterior/tanah.glb` | exterior | real |
| lantai (deck slab) | `public/components/exterior/lantai.glb` | exterior | real |
| tiang (pillar) | `public/components/exterior/tiang.glb` | exterior | real |
| dinding (walls + doors) | `public/components/exterior/dinding.glb` | exterior | real |
| pagar (veranda railing + roof posts) | `public/components/exterior/pagar.glb` | exterior | real |
| tangga (staircase) | `public/components/exterior/tangga.glb` | exterior | real |
| atap (roof) | `public/components/placeholder/atap.glb` | teammate | whitebox |
| interior | `public/components/placeholder/interior.glb` | teammate | whitebox |
| patung (statue) | `public/components/placeholder/patung.glb` | teammate | whitebox |

To replace a placeholder, drop the real GLB in and change its path in the manifest. The
replacement must have the same anchor names and stay inside the same bounding box (±5 cm).

## 3. Node naming

| Prefix | Meaning |
|---|---|
| `anchor_*` | Empty node. Its position + rotation is an attachment point. |
| `anchor_ground*` | Anchor that must end up exactly on the ground (world y = 0 ± 1 cm). Checked automatically. |
| `col_*` | Invisible collision box (axis-aligned box mesh). Hidden by the viewer, used for walking. |
| anything else | Visible mesh. |

The overlap check works on each mesh's bounding box. Never merge parts that enclose a
space (for example all four walls) into one mesh: its box would swallow everything inside
and report false overlaps. One mesh per wall, rail or panel run.

Anchors are matched by exact name. A wildcard such as `anchor_tiang_*` in the manifest
creates one instance per matching anchor.

## 4. Anchors per component

All coordinates are in the component's own local space.

| Component | Local origin | Anchors |
|---|---|---|
| tanah | world origin | `anchor_house` (0, 0, 0) |
| lantai | floor-top centre | `anchor_base` (0, -2.6, 0) · `anchor_tiang_NN` pillar tops at y = -0.2 · `anchor_dinding` (0, 0, 0) · `anchor_pagar` (0, 0, 5.4) · `anchor_interior` (0, 0, 0) · `anchor_tangga_kiri` (-15, 0, 5.4) · `anchor_tangga_tengah` (0, 0, 5.4) · `anchor_tangga_kanan` (15, 0, 5.4) |
| tiang | bottom centre | `anchor_ground` (0, 0, 0) · `anchor_top` (0, 2.4, 0) |
| dinding | base centre (floor top) | `anchor_base` (0, 0, 0) · `anchor_atap` (0, 3.0, 0) |
| pagar | front-edge base centre | `anchor_base` (0, 0, 0) |
| tangga | top landing, front edge of deck | `anchor_top` (0, 0, 0) · `anchor_ground` foot of stair (y = -2.6) · `anchor_patung_kiri` / `anchor_patung_kanan` (x = ∓2, y = -2.6) |
| atap | wall-top centre | `anchor_base` (0, 0, 0) |
| interior | floor-top centre | `anchor_base` (0, 0, 0) |
| patung | bottom centre | `anchor_ground` (0, 0, 0) |

A child is placed so that its anchor coincides exactly (position and rotation) with the
parent's anchor:

```
childWorld = parentWorld × parentAnchor × rotY(attach.rotationY) × inverse(childAnchor)
```

## 5. Key dimensions (world space)

| Part | Extent |
|---|---|
| Deck slab | x ±18.4, y 2.4 … 2.6, z -4.3 … 5.4 |
| Walls (outer) | x ±18.0, y 2.6 … 5.6, z -4.1 … 2.1, thickness 0.12 |
| Doors | 3 openings in the front wall at x = -15, 0, +15; 1.2 wide × 2.1 high |
| Veranda | z 2.1 … 5.4, railing along z ≈ 5.3, gaps 1.4 wide at x = -15, 0, +15 |
| Stairs | 1.1 wide, from deck edge z = 5.4 out to z ≈ 9.0, top at y = 2.6, foot at y = 0 |
| Roof (placeholder) | x ±20.4, y 5.6 … 9.95 (ridge), z -5.8 … 7.0; ridge ornaments may rise to y 12.3 |
| Interior (placeholder) | x ±18, y 2.6 … 5.6, z -4 … 2 |
| Statue (placeholder) | 0.7 × 5.3 × 0.7, beside the centre stair at x = ±2, z ≈ 7.8 |

## 6. Verification

`npm run check` assembles the manifest without a browser and reports:

1. **Missing anchors** — an attachment that refers to an anchor that does not exist.
2. **Ground contact** — every `anchor_ground*` must land at world y = 0 ± 0.01.
3. **Overlaps** — visible meshes from *different* instances whose bounding boxes
   interpenetrate by more than 0.01 m. Intentional overlaps go in `allowOverlap` in the
   manifest.

The viewer shows the same report in its panel.
