# CSmile Bali — WordPress + Elementor 3.35.0 Build Guide

> **Source**: `index.html` + `style.css` (scraped from csmilebali.webflow.io)  
> **Target**: WordPress 6.x + Elementor 3.35.0 + Elementor Pro 3.35.0  
> **Theme**: Hello Elementor (blank)  
> **Reference files**: `index.html` (structure), `style.css` (exact values), `scripts.js` (interactions)

---

## Table of Contents

1. [Step 1 — Global Settings](#step-1--global-settings)
2. [Step 2 — S0 Navbar · S1 Hero · S2 Steps · S3 Treatments](#step-2--s0-s3)
3. [Step 3 — S4 Services · S5 In-House Lab · S6 Before/After · S7 Video Testimonials](#step-3--s4-s7)
4. [Step 4 — S8 Process · S9 Reviews · S10 Contact · S11 Who We Are](#step-4--s8-s11)
5. [Step 5 — S12 Licensed · S13 Footer · Floating WA · Animations](#step-5--s12-s13--floating--animations)
6. [Step 6 — Final Check & Review](#step-6--final-check--review)

---

## Step 1 — Global Settings

### 1.1 WordPress + Theme

1. Install WordPress 6.x
2. Install **Hello Elementor** theme (activate it)
3. Install **Elementor 3.35.0** + **Elementor Pro 3.35.0**

### 1.2 Required Plugins

| Plugin | Purpose |
|--------|---------|
| Elementor Pro 3.35.0 | Header/Footer builder, Form widget, Motion Effects |
| Hello Elementor | Blank base theme |
| Before After Image Slider (by Starter Templates or BAS) | Before/After compare slider in S6 |
| Click to Chat or Starter WhatsApp Chat | Floating WhatsApp button |

### 1.3 Elementor Settings

Go to **Elementor → Settings → Style**:

| Setting | Value |
|---------|-------|
| Default Generic Fonts | Sans-serif |
| Content Width | `940` px |
| Widgets Space | `0` px |
| Stretched Section Fit To | Full Width |

### 1.4 Site Settings — Global Colors

Go to **Elementor → Site Settings → Global Colors**:

| Name | Hex | CSS Source |
|------|-----|-----------|
| Orange | `#fc5f2b` | `--orange` |
| Orange Hover | `#ff743a` | `.link-block:hover` |
| Submit Orange | `#ff4d00` | `.submit-button` |
| BG Gray | `#fbfbfb` | `--bg-gray` |
| Text Dark | `#100800` | `.page_wrapper` color |
| Text Secondary | `#4d4d4d` | `.steps-image-paragraph`, `.section-sub-heading` |
| Text Muted | `#574f48` | `.testimonial-description` |
| Card Dark | `#181818` | `.houselab-heading`, `.service-card-heading` |
| Gold Accent | `#d78e4b` | `.author-state` |
| Bar Gold | `#e5b283` | `.premium-material-div` |
| WA Green | `#23b33a` | `.lottie-animation` border |
| White | `#ffffff` | — |
| Navy Dark | `#1b2e3c` | `.footer` gradient end |
| Teal Mid | `#497ca2` | `.footer` gradient start |
| Required Red | `#ff1a1a` | `.text-span` |
| Icon BG Pink | `#ffece6` | `.steps-image-block` |

### 1.5 Site Settings — Global Fonts

Go to **Elementor → Site Settings → Global Fonts**:

| Name | Family | Weight | Fallback |
|------|--------|--------|----------|
| Heading | Cal Sans | 400 | sans-serif |
| Body | Hanken Grotesk | 400 | sans-serif |

> **Cal Sans** is NOT on Google Fonts. Download from [github.com/calcom/font](https://github.com/calcom/font). Upload `.woff2` to `/wp-content/fonts/`. Then add this `@font-face` to **Elementor → Site Settings → Custom CSS**:

```css
@font-face {
  font-family: 'Cal Sans';
  src: url('/wp-content/fonts/CalSans-SemiBold.woff2') format('woff2');
  font-weight: 400;
  font-style: normal;
  font-display: swap;
}
```

**Hanken Grotesk** — add via Google Fonts integration (already supported by Elementor).

### 1.6 Site Settings — Custom CSS (Global)

Add to **Elementor → Site Settings → Custom CSS**:

```css
/* ---- Font enforcement ---- */
body,
.elementor-widget-text-editor,
.elementor-widget-text-editor p {
  font-family: 'Hanken Grotesk', sans-serif;
  color: #100800;
  font-size: 16px;
  line-height: 100%;
}
h1, h2, h3, h4, h5, h6,
.elementor-heading-title {
  font-family: 'Cal Sans', sans-serif;
}
h2 {
  margin-top: 0;
  margin-bottom: 0;
  font-size: 35px;
  font-weight: 700;
  line-height: 160%;
}
/* ---- Responsive h2 overrides ---- */
@media screen and (min-width: 1280px) {
  h2 { font-size: 42px; }
}
@media screen and (min-width: 1440px) {
  h2 { font-size: 48px; }
}
```

### 1.7 Reusable Patterns (Reference — Do NOT create Global Widgets yet)

**CTA Button pattern** (used in Navbar, Hero, Contact):
- BG: `#fc5f2b`
- Text Color: `#fff`
- Border Radius: `50px`
- Padding: `13px` top/bottom, `25.5px` left/right
- Hover BG: `#ff743a`
- Font: inherit (Cal Sans, from parent)

**Section Heading pattern**:
- Font: Cal Sans
- Weight: 400
- Line-height: 160%
- Base size: `35px` → `40px` @1280 → `48px` @1920

---

## Step 2 — S0-S3

---

### S0 — Navbar

**Location**: Elementor → Templates → Theme Builder → Header → Add New

#### Section (outer wrapper)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Layout** | Column Gap | No Gap |
| **Layout** | Height | Min Height → `auto` |
| **Style** | Background | Transparent (`#ffffff00`) |
| **Advanced** | Padding | `20px` top, `0` others |
| **Advanced** | Z-Index | `1000` |
| **Advanced** | CSS Classes | `csmile-navbar` |

#### Container (inner — the glassmorphic pill bar)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Center |
| **Layout** | Column Gap | `16px` |
| **Layout** | Padding | `15px` top/bottom, `60px` left/right |
| **Advanced** | CSS Classes | `csmile-nav-pill` |

#### Widget 1 — Image (Logo)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Image | Upload CSmile logo SVG |
| **Content** | Link | `/` (homepage) |
| **Style** | Width | `150px` |
| **Advanced** | Width | `auto` |

#### Widget 2 — Nav Menu (Elementor Pro)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Menu | Select main menu (Home, Treatments, Services, Process, Contact Us) |
| **Content** | Layout | Horizontal |
| **Style** | Typography | Hanken Grotesk, `14px`, weight 400 |
| **Style** | Text Color | `#ffffff` |
| **Style** | Text Color (Hover) | `#fc5f2b` |
| **Style** | Text Color (Active) | `#ffffff` |
| **Style** | Pointer | Underline, color `#ffffff`, weight `2px` |
| **Style** | Spacing Between | `10px` |

#### Widget 3 — Button (CTA)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `Free Consultation` |
| **Content** | Link | `#contact` |
| **Style** | Typography | Cal Sans, `16px` |
| **Style** | Text Color | `#ffffff` |
| **Style** | Background | `#fc5f2b` |
| **Style** | Border Radius | `50px` |
| **Style** | Padding | `13px` top/bottom, `25.5px` left/right |
| **Style** | Hover BG | `#ff743a` |

#### Sticky Behavior

Select the **Section** → **Advanced** → **Motion Effects** → Sticky: **Top**, Stay In Column: No, Offset: `0`.

#### Section Custom CSS

```css
/* Glassmorphic pill shape */
selector .csmile-nav-pill {
  backdrop-filter: blur(20px);
  -webkit-backdrop-filter: blur(20px);
  background-image: linear-gradient(45deg, rgba(16,37,47,0.4), rgba(9,67,92,0.2));
  border: 1px solid rgba(255,255,255,0.2);
  border-radius: 100px;
}
/* Mobile nav - tablet and below */
@media (max-width: 991px) {
  selector .csmile-nav-pill {
    padding: 10px 35px;
  }
}
@media (max-width: 479px) {
  selector .csmile-nav-pill {
    padding-left: 24px;
    padding-right: 25px;
  }
}
```

**Display Condition**: Entire Site.

---

### S1 — Hero

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Layout** | Min Height | `100vh` |
| **Layout** | Column Position | Middle |
| **Layout** | Vertical Align | Middle |
| **Layout** | Overflow | Hidden |
| **Style** | Background Type | Video |
| **Style** | Video Link | Upload MP4 (dental clinic video) |
| **Style** | Start/End Time | `0` / blank (loop) |
| **Style** | Play On Mobile | No (set fallback image) |
| **Style** | Fallback Image | Upload poster frame |
| **Style** | Background Overlay | — none (video is dark enough) |
| **Advanced** | CSS ID | `hero` |
| **Advanced** | Padding | `0` all |
| **Advanced** | CSS Classes | `csmile-hero` |

#### Container (inner)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Layout** | Direction | Column |
| **Layout** | Justify | Center |
| **Layout** | Align | Start (left) |
| **Layout** | Min Height | `100vh` |
| **Layout** | Gap | `28px` |
| **Advanced** | Padding | `60px` top, `0` bottom, `140px` left, `245px` right |
| **Advanced** | Z-Index | `2` |

#### Widget 1 — Heading (H1)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Your life-changing smile, Now affordable in Bali` |
| **Content** | HTML Tag | H1 |
| **Style** | Typography | Cal Sans, `45px`, weight `400`, line-height `100%` |
| **Style** | Text Color | `#ffffff` |
| **Advanced** | Max Width | `500px` |
| **Advanced** | Margin | `0` all |
| **Advanced** | Motion Effects → Entrance | Fade In Up, Duration: `800ms`, Delay: `0ms` |

#### Widget 2 — Text Editor (Description)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | Two paragraphs (consultation + licensed info) with `<br><br>` between |
| **Style** | Typography | Hanken Grotesk, `14px`, line-height `100%` |
| **Style** | Text Color | `#ffffff` |
| **Advanced** | Max Width | `500px` |
| **Advanced** | Margin | `0` all |
| **Advanced** | Motion Effects → Entrance | Fade In Up, Duration: `800ms`, Delay: `200ms` |

#### Widget 3 — Button (CTA)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `Get Your Free Consultation` |
| **Content** | Link | `#contact` |
| **Style** | Typography | Cal Sans, `16px` |
| **Style** | Text Color | `#ffffff` |
| **Style** | Background | `#fc5f2b` |
| **Style** | Border Radius | `50px` |
| **Style** | Padding | `13px` top/bottom, `25.5px` left/right |
| **Style** | Hover BG | `#ff743a` |
| **Advanced** | Motion Effects → Entrance | Fade In Up, Duration: `800ms`, Delay: `400ms` |

#### Section Custom CSS

```css
/* Responsive hero container adjustments */
@media (min-width: 1440px) {
  selector .elementor-container {
    padding-left: 190px;
  }
  selector .elementor-heading-title {
    font-size: 80px;
    max-width: 900px;
  }
}
@media (min-width: 1920px) {
  selector .elementor-widget-text-editor {
    font-size: 24px;
    max-width: 880px;
  }
}
@media (max-width: 991px) {
  selector .elementor-container {
    padding-left: 100px;
    padding-right: 100px;
  }
}
@media (max-width: 767px) {
  selector .elementor-container {
    padding-left: 40px;
    padding-right: 40px;
  }
  selector .elementor-heading-title {
    font-size: 32px;
  }
}
@media (max-width: 479px) {
  selector .elementor-heading-title {
    font-size: 35px;
  }
}
```

---

### S2 — Steps

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `50px` top/bottom, `50px` left/right |

#### Container (flex row — 3 step cards)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Start |
| **Layout** | Gap | `30px` |
| **Layout** | Wrap | Wrap (for tablet stacking) |

#### Each Step Card (×3) — use nested Container

For each card (repeat 3 times with different content):

**Card Container:**

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Align | Start |
| **Layout** | Gap | `16px` |
| **Advanced** | Max Width | `424px` |

**Widget A — Image (icon in circle)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Image | Upload step icon (phone_callback / browse_gallery / price_check) |
| **Style** | Width | `28px` (icon itself) |
| **Advanced** | CSS Classes | `step-icon-circle` |

**Widget B — Heading (step title)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Tag | H3 |
| **Style** | Typography | Cal Sans, `20px`, weight `700`, line-height `160%` |
| **Style** | Text Color | `#100800` |

**Widget C — Text Editor (step description)**

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Typography | Hanken Grotesk, `15px`, weight `400`, line-height `160%` |
| **Style** | Text Color | `#4d4d4d` |
| **Advanced** | Max Width | `487px` |

**Step Card Contents:**

1. **Step by step consultation** — "Get expert guidance and a personalized treatment plan tailored to your needs. No Wait Times"
2. **No wait times** — "Start your treatment right away, no queues, no delays."
3. **Save 50% on Your Dental Treatment** — "Enjoy world-class care and advanced technology at a fraction of the cost."

#### Section Custom CSS

```css
/* Icon circle background */
selector .step-icon-circle {
  background-color: #ffece6;
  border-radius: 100px;
  min-width: 60px;
  width: 60px;
  height: 60px;
  padding: 16px;
  display: flex;
  justify-content: center;
  align-items: center;
}
/* Tablet: stack cards vertically */
@media (max-width: 991px) {
  selector .elementor-container {
    flex-direction: column;
  }
}
/* Responsive font scaling */
@media (min-width: 1280px) {
  selector .elementor-heading-title { font-size: 26px; }
  selector .elementor-widget-text-editor { font-size: 20px; }
}
@media (min-width: 1440px) {
  selector .elementor-heading-title { font-size: 28px; }
}
@media (min-width: 1920px) {
  selector { padding-top: 94px; padding-bottom: 94px; }
}
```

---

### S3 — Treatments

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Style** | Background | `#fbfbfb` (BG Gray) |
| **Advanced** | Padding | `70px` top/bottom, `50px` left/right |
| **Advanced** | CSS ID | `treatments` |

#### Container 1 — Heading Block

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Layout** | Gap | `0px` |
| **Advanced** | Margin | `0 0 80px 0` (bottom gap to card grid) |

**Widget — Heading (H2)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Our Treatments Made with High Care and Precision` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |
| **Style** | Text Color | `#100800` |

#### Container 2 — Card Grid

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Wrap | Wrap |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Center |
| **Layout** | Gap | `40px` |
| **Advanced** | CSS Classes | `treatments-grid` |

#### Each Treatment Card (×5) — nested Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Style** | Background | `#ffffff` |
| **Style** | Border Radius | `24px` |
| **Style** | Box Shadow | `0px 2px 7px rgba(180,180,180,0.24)` |
| **Advanced** | CSS Classes | `treatment-card` |
| **Advanced** | Overflow | Hidden |

**Widget A — Image**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Image | Upload treatment photo |
| **Style** | Width | `100%` |
| **Style** | Border Radius | `24px 24px 0 0` (only if image widget supports it, else handled by parent overflow:hidden) |

**Widget B — Heading**

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Typography | Cal Sans, `14px`, line-height `144%` |
| **Style** | Text Color | `#181818` |
| **Advanced** | Padding | `0 15px` left/right |

**Widget C — Text Editor**

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Typography | Hanken Grotesk, `12px`, line-height `160%` |
| **Style** | Text Color | `#4d4d4d` |
| **Advanced** | Padding | `0 15px 20px 15px` |

**Cards content:**
1. Dental Implants
2. Dental Crowns
3. Hollywood Smile
4. Veneers
5. Invisalign

#### Section Custom CSS

```css
/* 5-column grid on desktop */
selector .treatments-grid {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr 1fr 1fr;
  gap: 40px;
}
selector .treatment-card {
  overflow: hidden;
}
/* Tablet: 2 columns */
@media (max-width: 991px) {
  selector .treatments-grid {
    grid-template-columns: 1fr 1fr;
    gap: 20px;
  }
}
/* Mobile: 1 column */
@media (max-width: 479px) {
  selector .treatments-grid {
    grid-template-columns: 1fr;
  }
}
/* 1440px+ font scale */
@media (min-width: 1440px) {
  selector .treatment-card .elementor-heading-title {
    font-size: 18px;
  }
  selector .treatment-card .elementor-widget-text-editor {
    font-size: 14px;
    padding-bottom: 34px;
    padding-left: 27px;
    padding-right: 27px;
  }
}
@media (min-width: 1920px) {
  selector .treatment-card .elementor-heading-title {
    font-size: 24px;
  }
}
```

---

## Step 3 — S4-S7

---

### S4 — Services

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `70px` top/bottom, `50px` left/right |
| **Advanced** | CSS ID | `services` |

#### Container (flex row — left + right)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Center |
| **Layout** | Gap | `24px` |

#### Left Column — nested Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Start |
| **Layout** | Gap | `20px` |
| **Advanced** | Width | `50%` |

**Widget 1 — HTML (badge)**

```html
<div class="services-badge-el">
  <img src="[globe_icon_url]" alt="earth" style="width:20px;height:20px;">
  <span>Services</span>
</div>
```

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `services-badge-wrapper` |

**Widget 2 — Heading (H2)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Our International Guest Services` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Left |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |

**Widget 3 — Text Editor (subheading)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `Personalized support all in one seamless journey.` |
| **Style** | Typography | Hanken Grotesk, `18px`, weight `400`, line-height `160%` |
| **Style** | Text Color | `#4d4d4d` |

**Widget 4 — Container (Service Card 1: Airport & Clinic Transfers)**

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Start |
| **Layout** | Gap | `4px` |
| **Style** | Border Radius | `24px` |
| **Style** | Box Shadow | `0 2px 7px rgba(180,180,180,0.24)` |
| **Advanced** | Padding | `15px 30px` |

Inside: Image (transport icon) + Heading (Cal Sans, `20px`, `#181818`, line-height `144%`) + Text Editor (Hanken Grotesk, `16px`, line-height `160%`)

**Widget 5 — Container (Service Card 2: Luxury Accommodation)** — same structure

#### Right Column — nested Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Style** | Border Radius | `24px` |
| **Style** | Overflow | Hidden |
| **Advanced** | Width | `50%` |
| **Advanced** | Position | Relative |

**Widget — Image (front service photo)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Image | Airport transfer photo |
| **Style** | Width | `100%` |

> The original has two layered images (front + back). In Elementor, you can use one image or stack two with absolute positioning via custom CSS.

#### Section Custom CSS

```css
/* Services badge */
selector .services-badge-el {
  display: inline-flex;
  gap: 5px;
  align-items: center;
  border: 1px solid #fc5f2b;
  border-radius: 20px;
  padding: 4px 20px 4px 14px;
}
selector .services-badge-el span {
  color: #fc5f2b;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 18px;
  line-height: 100%;
}
/* Tablet: stack columns */
@media (max-width: 991px) {
  selector > .elementor-container > .elementor-column {
    width: 100%;
  }
}
@media (min-width: 1920px) {
  selector { padding-top: 100px; padding-bottom: 100px; }
}
```

---

### S5 — In-House Lab

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background | `#fbfbfb` |
| **Advanced** | Padding | `70px` top/bottom, `0` left/right |

#### Container 1 — Heading

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Layout** | Gap | `20px` |
| **Advanced** | Padding | `0 50px` left/right |

**Widget — Heading (H2)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `In-House Lab Ensures Precise, Aesthetic Restorations` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |

#### Container 2 — Marquee (full width)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Advanced** | Padding | `0` all |
| **Advanced** | Margin | `60px 0` (top/bottom gap) |
| **Advanced** | CSS Classes | `lab-marquee-wrapper` |
| **Advanced** | Overflow | Hidden |

**Widget — HTML (marquee)**

```html
<div class="lab-marquee-track">
  <img src="[lab_image_1_url]" alt="Lab 1" class="marquee-img">
  <img src="[lab_image_2_url]" alt="Lab 2" class="marquee-img">
  <img src="[lab_image_3_url]" alt="Lab 3" class="marquee-img">
  <img src="[lab_image_1_url]" alt="Lab 1" class="marquee-img">
  <img src="[lab_image_2_url]" alt="Lab 2" class="marquee-img">
  <img src="[lab_image_3_url]" alt="Lab 3" class="marquee-img">
</div>
```

#### Container 3 — Premium Materials (3 features)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Center |
| **Advanced** | Padding | `0 50px` left/right |

**Each Feature Block (×3)** — nested Container:

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Start |
| **Layout** | Gap | `30px` |
| **Advanced** | CSS Classes | `premium-feature-block` |

Inside each feature:
- **Container (icon + text)** — Direction: Row, Gap: `16px`, Align: Start
  - Image (icon, `28px`, in `step-icon-circle` class reuse)
  - Container (text) — Direction: Column
    - Heading: Cal Sans, `20px`, line-height `160%`
    - Text: Hanken Grotesk, `18px`, `#4d4d4d`, line-height `160%`
- **Spacer or Divider** — for hover bar (handled by CSS)

#### Section Custom CSS

```css
/* Marquee animation */
selector .lab-marquee-wrapper {
  overflow: hidden;
  max-width: 1920px;
  margin-left: auto;
  margin-right: auto;
}
selector .lab-marquee-track {
  display: flex;
  flex: none;
  animation: labMarquee 20s linear infinite;
}
selector .lab-marquee-track:hover {
  animation-play-state: paused;
}
selector .marquee-img {
  max-height: 400px;
  flex-shrink: 0;
}
@keyframes labMarquee {
  0%   { transform: translateX(0); }
  100% { transform: translateX(-50%); }
}
/* Premium feature hover bar */
selector .premium-feature-block {
  position: relative;
  padding-bottom: 10px;
}
selector .premium-feature-block::after {
  content: '';
  position: absolute;
  bottom: 0;
  left: 0;
  width: 0%;
  height: 3px;
  background-color: #e5b283;
  transition: width 0.4s ease;
}
selector .premium-feature-block:hover::after {
  width: 100%;
}
/* Icon circle (reuse) */
selector .step-icon-circle {
  background-color: #ffece6;
  border-radius: 100px;
  min-width: 60px;
  width: 60px;
  height: 60px;
  padding: 16px;
  display: flex;
  justify-content: center;
  align-items: center;
}
/* Responsive */
@media (max-width: 991px) {
  selector .elementor-container:last-child {
    flex-direction: column;
  }
}
@media (min-width: 1920px) {
  selector .marquee-img { max-height: 548px; }
}
@media (max-width: 479px) {
  selector .marquee-img { max-height: 280px; }
}
```

---

### S6 — Before/After

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Style** | Background Type | Image |
| **Style** | Image URL | Upload `Frame 5653.avif` background |
| **Style** | Position | Center Center |
| **Style** | Size | Auto |
| **Advanced** | Padding | `168px` top/bottom, `50px` left/right |

#### Container (flex row)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Justify | Center |
| **Layout** | Align | Center |
| **Layout** | Gap | `30px` |

#### Left Column — Before/After Slider

This requires a plugin. Use **Before After Image Slider for Elementor** or implement with custom HTML.

**Plugin Widget Configuration:**

| Setting | Value |
|---------|-------|
| Before Image | Upload "before" dental photo |
| After Image | Upload "after" dental photo |
| Handle Color | `#ffffff` |
| Handle Width | `42px` |
| Handle Style | Circle / Rounded (`border-radius: 8px`) |
| Line Color | `#ffffff` |
| Line Width | `2px` |
| Border | `5px solid #cdcdcd` |
| Border Radius | `12px` |
| Width | `100%` |
| Max Width | `771px` |
| Height | `536px` |

**Below slider** — thumbnail navigation (use Image Gallery or manual Image widgets):
- 6 thumbnail images in a row
- Default size: `50px` × `60px`, border: `2px solid #848484`, border-radius: `5px`
- Active: `90px` × `100px`, border-color: `#fc5f2b`

> For tab-switching behavior: use **Elementor Pro Tabs widget** with each tab containing a different before/after pair, or handle via custom JS.

#### Right Column — Text

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | Max Width | `500px` |

**Widget 1 — Heading**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Stop Dreaming, Start Smiling!` |
| **Content** | Tag | H2 |
| **Style** | Typography | Cal Sans, `40px`, weight `400`, line-height `120%` |
| **Style** | Text Color | `#ffffff` |

**Widget 2 — Heading**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Real-Life Transformations.` |
| **Content** | Tag | H2 |
| **Style** | Same as above |

**Widget 3 — Text Editor**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `See the life-changing results from our patients...` |
| **Style** | Typography | Hanken Grotesk, `18px`, line-height `150%` |
| **Style** | Text Color | `#ffffff` |

#### Section Custom CSS

```css
/* Tablet: stack vertically */
@media (max-width: 991px) {
  selector > .elementor-container {
    flex-direction: column;
    padding-top: 60px;
    padding-bottom: 220px;
  }
}
@media (min-width: 1920px) {
  selector > .elementor-container { gap: 64px; }
  selector .elementor-heading-title { font-size: 52px; line-height: 160%; }
  selector .elementor-widget-text-editor { font-size: 24px; }
}
/* Tab thumbnails */
selector .ba-thumb {
  width: 50px;
  height: 60px;
  border: 2px solid #848484;
  border-radius: 5px;
  overflow: hidden;
  cursor: pointer;
  object-fit: cover;
}
selector .ba-thumb.active {
  width: 90px;
  height: 100px;
  border-color: #fc5f2b;
}
```

---

### S7 — Video Testimonials

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `133px` top/bottom, `0` left/right |

#### Container 1 — Heading

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Align | Center |
| **Layout** | Gap | `60px` |

**Widget — Heading (H2)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Real Transformations, Real Confidence.` |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |

#### Container 2 — Video Carousel

Use **Elementor Pro Media Carousel** or a custom HTML embed with Swiper.js:

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | Max Width | `960px` |
| **Advanced** | Min Height | `500px` |
| **Advanced** | Margin | `0 auto` (centered) |
| **Advanced** | CSS Classes | `video-carousel-wrapper` |

**Carousel Settings** (if using Elementor Media Carousel):
- Slides to Show: `3` (desktop), `2` (tablet), `1` (mobile)
- Slides to Scroll: `1`
- Navigation: Arrows
- Autoplay: Yes
- Loop: Yes
- Effect: Coverflow or Slide

**Each Slide** — Video Background widget or Video embed:

| Property | Value |
|----------|-------|
| Width | `388px` max |
| Height | `450px` |
| Border Radius | `10px` |

#### Section Custom CSS

```css
/* Center slide emphasis */
selector .swiper-slide-active {
  transform: scale(1);
  opacity: 1;
}
selector .swiper-slide:not(.swiper-slide-active) {
  transform: scale(0.85);
  opacity: 0.6;
  transition: transform 0.3s, opacity 0.3s;
}
/* Mobile slide size */
@media (max-width: 479px) {
  selector .swiper-slide {
    width: 320px;
  }
}
@media (max-width: 991px) {
  selector { padding-top: 20px; }
}
```

---

## Step 4 — S8-S11

---

### S8 — Process (Smile Journey)

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background Type | Image |
| **Style** | Image URL | Upload `Carousel - 6.avif` |
| **Style** | Position | Center Center |
| **Style** | Size | Cover (`100% 100%`) |
| **Advanced** | Padding | `70px` top/bottom |
| **Advanced** | CSS ID | `process` |

#### Container (inner)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1746px` |
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Layout** | Gap | `60px` |

#### Widget — Heading

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Steps of Your Smile Journey` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |
| **Style** | Text Color | `#ffffff` |

#### Cards Grid Container

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `smile-grid` |

#### Each Process Card (×5) — nested Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Start |
| **Layout** | Gap | `4px` |
| **Style** | Background | `#ffffff` |
| **Style** | Border Radius | `24px` |
| **Advanced** | Padding | `20px 30px` |

Inside each card:
- **Heading** (step number+title): Cal Sans, `24px`, line-height `144%`, color `#181818`
  - For the step number portion, use `<span style="color:#fc5f2b">01.</span>` inside the heading
- **Text Editor** (description): Hanken Grotesk, `14.5px`, line-height `160%`, color `#4d4d4d`

**Cards:**
1. Start Your Online Consultation.
2. Receive Your Treatment Plan & Quote
3. First Day at the Clinic
4. Begin Your Treatment Journey
5. Follow-Up & Aftercare

#### Section Custom CSS

```css
/* Grid layout: 4 columns, cards 1-4 span 2, card 5 spans middle */
selector .smile-grid {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr 1fr;
  grid-template-rows: auto auto;
  gap: 24px;
}
selector .smile-grid > :nth-child(1),
selector .smile-grid > :nth-child(2),
selector .smile-grid > :nth-child(3),
selector .smile-grid > :nth-child(4) {
  grid-column: span 2;
}
selector .smile-grid > :nth-child(5) {
  grid-column: 2 / 4;
}
/* Mobile: single column */
@media (max-width: 479px) {
  selector .smile-grid {
    grid-template-columns: 1fr;
  }
  selector .smile-grid > :nth-child(n) {
    grid-column: span 1;
  }
}
@media (min-width: 1920px) {
  selector { padding-top: 100px; padding-bottom: 177px; }
}
```

---

### S9 — Reviews (Testimonials)

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `70px` top/bottom |

#### Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width, `1920px` max |
| **Layout** | Direction | Column |
| **Layout** | Gap | `60px` |

#### Widget — Heading

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `What Our Patients Say` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |

#### Testimonial Rows — use HTML widget or Elementor Testimonial Carousel

The original uses two scrolling marquee rows (row 1 scrolls left, row 2 scrolls right). Best approach: **Custom HTML widget** with CSS animation.

**Each Review Card HTML structure** (repeated, with data for each patient):

```html
<div class="review-card">
  <div class="review-header">
    <div class="review-author">
      <img src="[avatar]" class="review-avatar" alt="[name]">
      <div>
        <div class="review-name">[Name]</div>
        <div class="review-country">[Country]</div>
      </div>
    </div>
    <img src="[stars_image]" class="review-stars" alt="5 stars">
  </div>
  <div class="review-text">[Review text...]</div>
</div>
```

#### Section Custom CSS

```css
/* Review card */
selector .review-card {
  border: 1px solid #d9d9d9;
  border-radius: 12px;
  max-width: 730px;
  height: 325px;
  margin-right: 24px;
  padding: 20px;
  display: flex;
  flex-direction: column;
  gap: 16px;
  flex-shrink: 0;
}
selector .review-header {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  width: 100%;
}
selector .review-author {
  display: flex;
  gap: 12px;
  align-items: center;
}
selector .review-avatar {
  width: 42px;
  border-radius: 50%;
}
selector .review-name {
  font-family: 'Cal Sans', sans-serif;
  font-size: 32px;
  line-height: 160%;
}
selector .review-country {
  color: #d78e4b;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 18px;
  line-height: 160%;
}
selector .review-text {
  color: #574f48;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 16px;
  line-height: 160%;
  overflow: auto;
}
/* Marquee rows */
selector .testimonial-row {
  display: flex;
  overflow: hidden;
}
selector .testimonial-track {
  display: flex;
  flex: none;
  animation: reviewScrollLeft 40s linear infinite;
}
selector .testimonial-row.reverse .testimonial-track {
  animation: reviewScrollRight 40s linear infinite;
}
selector .testimonial-row:hover .testimonial-track {
  animation-play-state: paused;
}
@keyframes reviewScrollLeft {
  0% { transform: translateX(0); }
  100% { transform: translateX(-50%); }
}
@keyframes reviewScrollRight {
  0% { transform: translateX(-50%); }
  100% { transform: translateX(0); }
}
/* Mobile card sizing */
@media (max-width: 479px) {
  selector .review-card {
    max-width: 360px;
    padding: 15px;
    border-radius: 8px;
  }
  selector .review-name { font-size: 22px; }
  selector .review-country, selector .review-text { font-size: 14px; }
}
@media (min-width: 1920px) {
  selector { padding-top: 120px; padding-bottom: 120px; }
}
```

---

### S10 — Contact Form

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background Type | Image |
| **Style** | Image URL | Upload `Frame 4744.avif` |
| **Style** | Position | Center Center |
| **Style** | Size | Cover (`100% 100%`) |
| **Advanced** | Padding | `70px` top/bottom, `20px` left/right |
| **Advanced** | CSS ID | `contact` |

#### Container (flex row)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1480px` |
| **Layout** | Direction | Row |
| **Layout** | Justify | Center |
| **Layout** | Align | Center |
| **Layout** | Gap | `70px` |

#### Left Column — nested Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Gap | `38px` |
| **Advanced** | Max Width | `646px` |

**Widget 1 — Heading**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Start Your Smile Journey Today` |
| **Content** | Tag | H2 |
| **Style** | Typography | Cal Sans, `40px`, line-height `160%` |
| **Style** | Text Color | `#ffffff` |

**Widget 2 — Text Editor**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `Fill out the form below and our team will get back to you within 24 hours...` |
| **Style** | Typography | Hanken Grotesk, `20px`, line-height `160%` |
| **Style** | Text Color | `#ffffff` |

**Widget 3 — Form (Elementor Pro)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Fields | First Name (text, required), Last Name (text, req), Email (email, req), WhatsApp Number (tel, req), Treatment (select, req: Dental Implants/Crowns/Hollywood Smile/Veneers/Invisalign/Other), Dental Needs (textarea, optional) |
| **Content** | Submit Text | `Get Your Free Consultation` |
| **Style** | Label Color | `#ffffff` |
| **Style** | Label Typography | Hanken Grotesk, `16px`, weight `400` |
| **Style** | Input BG | `#ffffff` |
| **Style** | Input Border Radius | `8px` |
| **Style** | Input Typography | Hanken Grotesk, `14px`, line-height `160%` |
| **Style** | Button BG | `#ff4d00` |
| **Style** | Button Border Radius | `10px` |
| **Style** | Button Typography | Cal Sans, `20px`, line-height `160%` |
| **Style** | Button Color | `#ffffff` |
| **Style** | Button Padding | `6px 0` |
| **Advanced** | CSS Classes | `glassmorphic-form` |

#### Right Column — nested Container

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | Max Width | `726px` |

**Widget — Image**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Image | Smiling woman photo |
| **Style** | Width | `100%` |
| **Style** | Border Radius | `20px` |

#### Section Custom CSS

```css
/* Glassmorphic form container */
selector .glassmorphic-form {
  filter: drop-shadow(0 2px 8px rgba(0,0,0,0.05));
  backdrop-filter: blur(100px);
  -webkit-backdrop-filter: blur(100px);
  background-color: rgba(255,255,255,0.35);
  border: 1px solid rgba(255,255,255,0.5);
  border-radius: 20px;
  padding: 40px;
}
/* Required asterisk color */
selector .elementor-mark-required .elementor-field-label:after {
  color: #ff1a1a !important;
}
/* Textarea */
selector textarea.elementor-field-textual {
  border-radius: 8px;
  min-height: 110px;
  padding: 15px 16px;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 14px;
}
/* Tablet: stack */
@media (max-width: 991px) {
  selector > .elementor-container {
    flex-direction: column;
  }
}
@media (max-width: 479px) {
  selector .glassmorphic-form {
    padding: 20px;
  }
}
@media (min-width: 1920px) {
  selector { padding: 144px 20px; }
}
```

---

### S11 — Who We Are

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1476px` |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `60px` top/bottom, `20px` left/right |

#### Container 1 — Heading

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Style** | Border Type | Solid |
| **Style** | Border Width | `0 0 1px 0` (bottom only) |
| **Style** | Border Color | `rgba(183,183,183,0.5)` |
| **Advanced** | Padding | `16px` top/bottom |

**Widget — Heading**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Who We Are` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `60px`, weight `400` |

#### Container 2 — Bento Grid

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `who-grid` |
| **Advanced** | Margin | `40px 0 0 0` (top gap) |

**Grid Cell 1 (Row 1 Left) — Our Story** — Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Gap | `4px` |
| **Style** | Background Type | Image |
| **Style** | Image URL | Upload `Frame 4718.avif` (subtle watermark bg) |
| **Style** | Size | Cover |
| **Style** | Border Radius | `20px` |
| **Advanced** | Padding | `29.5px 48px` |

Inside:
- Heading: `Our Story`, Cal Sans, `35px`, line-height `160%`
- Text: Hanken Grotesk, `16px`, line-height `160%`, max-width `450px`, gap `16px` between paragraphs

**Grid Cell 2 (Row 1 Right) — Clinic Photo** — Container

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Border Radius | `20px` |
| **Advanced** | Overflow | Hidden |

Inside: Image widget — 100% width, object-fit cover, 100% height

**Grid Cell 3 (Row 2 Left) — Image Slider** — Container

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Border Radius | `20px` |
| **Advanced** | Overflow | Hidden |

Inside: **Image Carousel** (Elementor Pro) — autoplay, loop, max-height `440px`, dots visible

**Grid Cell 4 (Row 2 Right) — Our Vision** — Same structure as Our Story cell

#### Section Custom CSS

```css
/* 2-column bento grid */
selector .who-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  grid-template-rows: auto auto;
  gap: 24px;
}
/* Tablet: 1 column */
@media (max-width: 991px) {
  selector .who-grid {
    grid-template-columns: 1fr;
  }
}
@media (min-width: 1920px) {
  selector { padding: 98px 20px; }
  selector .elementor-heading-title { font-size: 60px; }
}
@media (max-width: 479px) {
  selector { padding: 40px 0; }
  selector .who-grid > * { padding: 20px; }
}
```

---

## Step 5 — S12-S13 + Floating + Animations

---

### S12 — Licensed

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1920px` |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `80px` top/bottom, `50px` left/right |

#### Container 1 — Heading Block

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Layout** | Gap | `12px` |

**Widget 1 — Heading (H2)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Officially Licensed By` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |

**Widget 2 — Text Editor**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `Government Authorities and Recognized Institutions — Indonesia` |
| **Content** | Alignment | Center |
| **Style** | Typography | Hanken Grotesk, `20px`, line-height `160%` |
| **Style** | Text Color | `#574f48` |

#### Container 2 — Card Grid

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `licensed-grid` |
| **Advanced** | Margin | `40px 0 0 0` |

#### Each Licensed Card (×4) — Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Justify | Center |
| **Layout** | Align | Center |
| **Layout** | Gap | `30px` |
| **Style** | Background Type | Image |
| **Style** | Image URL | Upload `Frame 4747.avif` (card BG) |
| **Style** | Size | Cover |
| **Advanced** | Padding | `40px 0` top/bottom |

Inside:
- **Image**: institution logo, max-height `150px`, centered
- **Text**: institution name, Hanken Grotesk, `11px`, line-height `160%`, center, max-width `253px`

**Cards:**
1. PDGI
2. Kementerian Kesehatan Republik Indonesia
3. Kemenparekraf
4. Dinas Kesehatan Provinsi Bali

#### Section Custom CSS

```css
selector .licensed-grid {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr 1fr;
  gap: 16px;
}
@media (max-width: 991px) {
  selector .licensed-grid { grid-template-columns: 1fr 1fr; }
}
@media (max-width: 479px) {
  selector .licensed-grid { grid-template-columns: 1fr; }
  selector { padding-left: 20px; padding-right: 20px; }
}
@media (min-width: 1920px) {
  selector { padding-left: 96px; padding-right: 96px; }
  selector .licensed-grid { gap: 24px; }
  selector .licensed-grid > * { padding-top: 75px; padding-bottom: 75px; }
  selector .licensed-grid .elementor-image img { max-height: none; }
  selector .licensed-grid .elementor-widget-text-editor {
    max-width: 380px;
    font-size: 16px;
  }
}
```

---

### S13 — Footer

**Location**: Elementor → Templates → Theme Builder → Footer → Add New

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background Type | Gradient |
| **Style** | Gradient | `#497ca2` (top) → `#1b2e3c` (bottom), Linear, 0° (bottom-to-top) |
| **Advanced** | Padding | `0` all |

#### Container 1 — Footer Content

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1360px` |
| **Layout** | Direction | Column |
| **Layout** | Gap | `48px` |
| **Advanced** | Padding | `50px` top, `26px` bottom, `20px` left/right |

#### Top Row — Container (3 columns)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Start |

**Left Column** (Container, max-width `300px`, direction: column, gap: `16px`, padding: `10px`):

- Image: Logo, max-width `220px`
- Text: Tagline, Hanken Grotesk, `16px`, white, line-height `150%`
- Text: "Follow us on:", Cal Sans, line-height `162%`, white
- Container (social icons): Direction: Row, Gap: `16px`
  - Image ×2: Facebook + Instagram icons

**Middle Column** (Container, direction: column, gap: `8px`, padding: `10px`):

- Heading: `Quick Links`, Cal Sans, `18px`, white, line-height `155%`, padding-bottom `8px`
- Text links ×4: Hanken Grotesk, `16px`, white, line-height `150%`, no underline

**Right Column** (Container, direction: column, gap: `8px`, padding: `10px`):

- Heading: `Contact`, Cal Sans, `18px`, white, line-height `155%`, padding-bottom `8px`
- Container ×3 (each contact item): Direction: Row, Gap: `12px`, Align: Start
  - Image: icon (phone/email/location), padding `4px`
  - Text: contact info, Hanken Grotesk, white, line-height `150%`

#### Bottom Bar — Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Align | Center |
| **Style** | Border Type | Solid |
| **Style** | Border Width | `1px 0 0 0` (top only) |
| **Style** | Border Color | `#ffffff` |
| **Advanced** | Padding | `18px` top/bottom |

- Text: `© 2025 CSmile Bali. All rights reserved.`, center, Hanken Grotesk, `16px`, white

#### Section Custom CSS

```css
/* All footer text white */
selector, selector * {
  color: #ffffff;
}
selector a {
  color: #ffffff;
  text-decoration: none;
}
selector a:hover {
  color: #fc5f2b;
}
/* Tablet: stack columns */
@media (max-width: 991px) {
  selector .footer-top-row {
    flex-direction: column;
  }
}
@media (max-width: 479px) {
  selector .elementor-container { padding-top: 40px; padding-bottom: 0; }
  selector .footer-bottom { padding-top: 10px; padding-bottom: 10px; }
  selector .footer-text, selector .footer-link { font-size: 14px; }
  selector .footer-heading { font-size: 16px; padding-bottom: 4px; }
}
@media (min-width: 1920px) {
  selector .elementor-container { padding-top: 40px; }
  selector .footer-bottom { padding-top: 12px; padding-bottom: 12px; }
}
```

**Display Condition**: Entire Site.

---

### Floating — WhatsApp Button

**Method**: Install **Click to Chat** plugin.

| Setting | Value |
|---------|-------|
| Phone Number | `628133786031` |
| Pre-filled Message | `Hi CSmile Bali, I'm interested in a free consultation!` |
| Position | Bottom Right |
| Bottom Offset | `20px` |
| Right Offset | `50px` |
| Size | `60px` |
| Border | `1px solid #23b33a` |
| Border Radius | `100px` |
| Z-Index | `99` |
| Icon Color | `#23b33a` |

**Alternative — Custom HTML** (add as Elementor HTML widget on page):

```html
<a href="https://wa.me/628133786031?text=Hi%20CSmile%20Bali%2C%20I%27m%20interested%20in%20a%20free%20consultation!" 
   class="wa-fab" target="_blank" rel="noopener">
  <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="#23b33a" width="30" height="30">
    <path d="M17.472 14.382c-.297-.149-1.758-.867-2.03-.967-.273-.099-.471-.148-.67.15-.197.297-.767.966-.94 1.164-.173.199-.347.223-.644.075-.297-.15-1.255-.463-2.39-1.475-.883-.788-1.48-1.761-1.653-2.059-.173-.297-.018-.458.13-.606.134-.133.298-.347.446-.52.149-.174.198-.298.298-.497.099-.198.05-.371-.025-.52-.075-.149-.669-1.612-.916-2.207-.242-.579-.487-.5-.669-.51-.173-.008-.371-.01-.57-.01-.198 0-.52.074-.792.372-.272.297-1.04 1.016-1.04 2.479 0 1.462 1.065 2.875 1.213 3.074.149.198 2.096 3.2 5.077 4.487.709.306 1.262.489 1.694.625.712.227 1.36.195 1.871.118.571-.085 1.758-.719 2.006-1.413.248-.694.248-1.289.173-1.413-.074-.124-.272-.198-.57-.347m-5.421 7.403h-.004a9.87 9.87 0 01-5.031-1.378l-.361-.214-3.741.982.998-3.648-.235-.374a9.86 9.86 0 01-1.51-5.26c.001-5.45 4.436-9.884 9.888-9.884 2.64 0 5.122 1.03 6.988 2.898a9.825 9.825 0 012.893 6.994c-.003 5.45-4.437 9.884-9.885 9.884m8.413-18.297A11.815 11.815 0 0012.05 0C5.495 0 .16 5.335.157 11.892c0 2.096.547 4.142 1.588 5.945L.057 24l6.305-1.654a11.882 11.882 0 005.683 1.448h.005c6.554 0 11.89-5.335 11.893-11.893a11.821 11.821 0 00-3.48-8.413z"/>
  </svg>
</a>
```

Add CSS to **Site Settings → Custom CSS**:

```css
.wa-fab {
  position: fixed;
  bottom: 20px;
  right: 50px;
  width: 60px;
  height: 60px;
  border: 1px solid #23b33a;
  border-radius: 100px;
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 99;
  background: #fff;
  transition: transform 0.2s ease;
}
.wa-fab:hover {
  transform: scale(1.1);
}
@media (min-width: 1920px) {
  .wa-fab { right: 100px; }
}
@media (max-width: 479px) {
  .wa-fab { right: 20px; z-index: 999; }
}
```

---

### Animation Recreation (from scripts.js)

These animations were handled by Webflow IX2. Here's how to recreate each in Elementor:

| # | Original Effect | Elementor Setup | Applied To |
|---|----------------|----------------|------------|
| 1 | **Fade In Up on load** | Widget → Advanced → Motion Effects → Entrance Animation: `Fade In Up`, Duration `800ms` | Hero heading, description, CTA button (stagger delays: 0/200/400ms) |
| 2 | **Fade In Up on scroll** | Widget → Advanced → Motion Effects → Entrance Animation: `Fade In Up` | Step cards, treatment cards, service elements, process cards |
| 3 | **Marquee scroll** | CSS `@keyframes` animation on HTML widget | Lab images (S5), Testimonial rows (S9) |
| 4 | **Premium bar hover** | CSS `::after` pseudo-element with `width: 0→100%` transition | Lab feature blocks (S5) |
| 5 | **Before/After slider** | Plugin handles this — range input driving clip-path | Before/After section (S6) |
| 6 | **Tab switching** | Elementor Pro Tabs widget OR custom JS for thumbnail→slider switching | Before/After thumbnails (S6) |
| 7 | **Swiper carousel** | Elementor Media Carousel with coverflow effect OR Swiper CDN embed | Video testimonials (S7) |
| 8 | **Webflow Slider** | Elementor Image Carousel widget with autoplay + nav | Who We Are clinic photos (S11) |
| 9 | **Sticky header** | Section → Advanced → Motion Effects → Sticky: Top | Navbar (S0) |
| 10 | **Smooth scroll** | Built into Elementor (enable: Settings → General → Smooth Scroll) or use anchor links | Navbar links |
| 11 | **Video autoplay** | Elementor Video Background widget handles this natively | Hero section (S1) |

**How to set Entrance Animation in Elementor 3.35.0:**
1. Select widget
2. Go to **Advanced** tab
3. Expand **Motion Effects**
4. Under **Entrance Animation**: choose `Fade In Up`
5. Set **Animation Duration**: Normal (or custom via CSS)
6. For staggered delays: set different **Animation Delay** values (`0ms`, `200ms`, `400ms`)

---

## Step 6 — Final Check & Review

### Fonts & Design Checklist

- [ ] Cal Sans loaded via `@font-face` (woff2 self-hosted in `/wp-content/fonts/`)
- [ ] Hanken Grotesk loaded from Google Fonts
- [ ] Global Colors defined in Elementor Site Settings (all 16 colors)
- [ ] Global Fonts defined (Heading + Body)
- [ ] Global Custom CSS added (font enforcement + h2 responsive)

### Structure Checklist

- [ ] Header template created → Display: Entire Site
- [ ] Footer template created → Display: Entire Site
- [ ] All 13 sections on main page in correct order
- [ ] CSS IDs set: `hero`, `treatments`, `services`, `process`, `contact`
- [ ] All navbar anchor links work (#hero, #treatments, #services, #process, #contact)

### Interactive Features Checklist

- [ ] Contact form submits → email action configured
- [ ] Before/After slider plugin installed and working with 6 image pairs
- [ ] Video carousel showing 3 slides on desktop
- [ ] Lab marquee scrolling smoothly (no gap/flicker on loop)
- [ ] Image carousel in Who We Are section autoplay working
- [ ] WhatsApp FAB visible and links to correct number

### Animation Checklist

- [ ] Hero entrance animations (fade in up, staggered)
- [ ] Scroll-triggered fade-in on Steps, Treatments, Services
- [ ] Lab feature hover bar animates (width 0→100%)
- [ ] Navbar sticky on scroll
- [ ] Treatment card hover (optional lift effect)
- [ ] Testimonial rows scrolling (left + right)

### Responsive Checklist

Test each breakpoint in Elementor responsive mode:

| Breakpoint | Key Checks |
|------------|------------|
| **Desktop XL (1920px+)** | Larger paddings, bigger fonts, wider containers |
| **Desktop (1280-1440px)** | h2: `42-48px`, hero heading: `45-80px` |
| **Tablet (991px)** | Navbar hamburger, columns stack, grids reduce to 2-col |
| **Mobile L (767px)** | Hero heading: `32px`, reduced paddings |
| **Mobile (479px)** | All grids → 1-col, minimal padding, compact cards |

- [ ] Navbar collapses to hamburger ≤991px
- [ ] 5-col Treatments → 2-col tablet → 1-col mobile
- [ ] Services 2-col → stacked on tablet
- [ ] Process 4-col grid → 1-col mobile
- [ ] Licensed 4-col → 2-col tablet → 1-col mobile
- [ ] Contact form stacks on tablet
- [ ] Who We Are grid → 1-col tablet
- [ ] Footer 3-col → stacked tablet
- [ ] WhatsApp FAB visible on all screens

### Performance Checklist

- [ ] All images compressed (WebP/AVIF format)
- [ ] Video hosted externally or YouTube embed (not large MP4 in WP media)
- [ ] Elementor CSS loading: External File (not inline)
- [ ] Lazy loading enabled for below-fold images
- [ ] Unused Elementor features disabled in Experiments

### SEO & Tracking

- [ ] Page title and meta description set (via Yoast or RankMath)
- [ ] Open Graph image uploaded
- [ ] Google Tag Manager / GA4 code added (Site Settings → Custom Code → Head)
- [ ] Facebook Pixel added if required
- [ ] Schema.org JSON-LD from original HTML added to Custom Code → Head

---

> **Build order**: Desktop first → then switch to tablet/mobile responsive modes in Elementor to adjust padding, fonts, and column stacking. Always test on a real device before launching.
