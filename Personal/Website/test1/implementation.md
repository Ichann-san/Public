# CSmile Bali — WordPress + Elementor 3.35.0 Build Guide

> **Source**: `index.html` + `style.css` (scraped from csmilebali.webflow.io)  
> **Target**: WordPress 7.0 + Elementor 3.35.0 + Elementor Pro 3.35.0  
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

1. Install WordPress 7.0
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

### S5 — In-House Lab (`made-section`)

> **HTML ref**: `<section class="made-section">` → `made-with-main-block` → heading + marquee + premium materials

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background | `#fbfbfb` |
| **Advanced** | Padding | `70px` top/bottom, `0` left/right |
| **Advanced** | CSS Classes | `made-section` |

#### Container 1 — Heading (`made-heading-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` (matches `main-container`) |
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Layout** | Gap | `20px` |
| **Advanced** | Padding | `0 50px` left/right |
| **Advanced** | CSS Classes | `made-heading-block` |

**Widget — Heading (H2)**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `In-House Lab Ensures Precise, Aesthetic Restorations` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |
| **Style** | CSS Classes | `section-heading _40px-desktop` |

> The original has a hidden sub-heading (`section-sub-heading hide` class with text "Our in-house dental laboratory ensures precision and aesthetic excellence in every restoration from design to delivery."). Skip in Elementor — it was hidden in the original.

#### Container 2 — Marquee (`made-main-marquee-block`, full width)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Advanced** | Padding | `0` all |
| **Advanced** | Margin | `60px 0` (top/bottom gap) |
| **Advanced** | CSS Classes | `lab-marquee-wrapper` |
| **Advanced** | Overflow | Hidden |

**Widget — HTML (marquee)**

Use an HTML widget with the duplicated track for infinite scrolling:

```html
<div class="made-main-marquee-block">
  <div class="made-marquee lab-marquee-track">
    <img src="[lab_image_1_url]" alt="dental treatment" class="image-marquee">
    <img src="[lab_image_2_url]" alt="Dental technician working in clinic's lab" class="image-marquee">
    <img src="[lab_image_3_url]" alt="Dental restoration being crafted" class="image-marquee">
  </div>
  <div class="made-marquee lab-marquee-track">
    <img src="[lab_image_1_url]" alt="dental treatment" class="image-marquee">
    <img src="[lab_image_2_url]" alt="Dental technician working in clinic's lab" class="image-marquee">
    <img src="[lab_image_3_url]" alt="Dental restoration being crafted" class="image-marquee">
  </div>
</div>
```

> **Images**: Upload the 3 lab images from the original (Copy of Lab 3, Copy of Lab 8, to be used lap pic). The track is duplicated for seamless infinite looping.

#### Container 3 — Premium Materials (`premium-materials-main-block`, 3 features)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` |
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Center |
| **Advanced** | Padding | `0 50px` left/right |
| **Advanced** | CSS Classes | `premium-materials-main-block` |

**Each Feature Block (×3)** — nested Container:

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Start |
| **Layout** | Gap | `0px` |
| **Advanced** | CSS Classes | `premium-material-hover-block` |

Inside each feature (matching original structure: `steps-content-main-block premium-materials-content-block`):
- **Container (icon + text)** — Direction: Row, Gap: `16px`, Align: Start, CSS Classes: `steps-content-main-block premium-materials-content-block`
  - **Container** (icon circle, CSS Classes: `steps-image-block`):
    - Image: `biotech (2).png` (⚠️ all 3 features use the SAME icon), `28px`, in circle
  - **Container** (text, CSS Classes: `steps-content-block`):
    - Heading: CSS Classes `steps-image-heading _20px`
    - Text: CSS Classes `steps-image-paragraph _18px`
- **Spacer/Divider** — An empty div for the hover progress bar, CSS Classes: `premium-material-div`

> ⚠️ **Important**: The original uses a **separate div element** (`premium-material-div`) for the gold hover bar, NOT a CSS `::after` pseudo-element. This div is animated on hover via Webflow IX2 (width 0% → 100%). In Elementor, create this as an **empty div inside an HTML widget** or a **Spacer** with custom styling.

**Feature Contents (exact from index.html):**

1. **Premium Materials** — "We use the highest quality dental materials"
2. **Precision Crafting** — "Every restoration is meticulously crafted"
3. **In-House Control** — "Complete quality control from design to delivery"

#### Section Custom CSS

```css
/* Marquee animation */
selector .lab-marquee-wrapper {
  overflow: hidden;
  width: 100%;
}
selector .made-main-marquee-block {
  display: flex;
  overflow: hidden;
}
selector .lab-marquee-track {
  display: flex;
  flex: none;
  animation: labMarquee 20s linear infinite;
}
selector .lab-marquee-track:hover {
  animation-play-state: paused;
}
selector .image-marquee {
  max-height: 400px;
  flex-shrink: 0;
}
@keyframes labMarquee {
  0%   { transform: translateX(0); }
  100% { transform: translateX(-50%); }
}
/* Premium feature hover bar — uses a real div, not pseudo-element */
selector .premium-material-hover-block {
  position: relative;
  cursor: pointer;
}
selector .premium-material-div {
  height: 3px;
  background-color: #e5b283;
  width: 0%;
  transition: width 0.4s ease;
}
selector .premium-material-hover-block:hover .premium-material-div {
  width: 100%;
}
/* Icon circle (reuse) */
selector .steps-image-block {
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
  selector .premium-materials-main-block {
    flex-direction: column;
  }
}
@media (min-width: 1920px) {
  selector .image-marquee { max-height: 548px; }
}
@media (max-width: 479px) {
  selector .image-marquee { max-height: 280px; }
}
```

---

### S6 — Before/After (`before-after-section`)

> **HTML ref**: `<section class="before-after-section">` — This is the most complex section. The original has TWO layouts:
> 1. A **mobile layout** (`before-after-phone-main-block`) with stacked `bas-wrapper absolute` sliders + thumbnail navigation
> 2. A **desktop layout** (`before-after-left-block`) using Webflow Tabs (`w-tabs`) with 6 tab panes, each containing a before/after slider
>
> Each slider uses **two systems**: Flowbase `fb-before-after` (clip-path based) AND `udesly-before-after-slider` (BeerSlider JS). For WordPress, we simplify to ONE before/after approach.

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` |
| **Style** | Background Type | Image |
| **Style** | Image URL | Upload `Frame 5653.avif` background |
| **Style** | Position | Center Center |
| **Style** | Size | Auto |
| **Advanced** | Padding | `168px` top/bottom, `50px` left/right |
| **Advanced** | CSS Classes | `before-after-section` |

#### Container (flex row — `before-after-main-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Justify | Center |
| **Layout** | Align | Center |
| **Layout** | Gap | `30px` |
| **Advanced** | CSS Classes | `before-after-main-block` |

#### Left Column — Before/After Slider + Thumbnails (`div-block-12`)

> **WordPress approach**: Use an **HTML widget** with custom before/after slider code (BeerSlider pattern from the original). The original has **6 before/after pairs** switchable via tab thumbnails.

**Option A — Use "Before After Image Slider" plugin for Elementor:**

Install a before/after slider plugin. Set up 6 image pairs. Use thumbnails below to switch between pairs via custom JS.

**Option B — Custom HTML widget (closer to original):**

Use an HTML widget to embed the BeerSlider code from the original `index.html`. Each tab pane contains a slider. The thumbnails switch visibility.

**The 6 Before/After image pairs (from index.html):**

| # | Before Image | After Image |
|---|-------------|-------------|
| 1 | `WhatsApp Image 2025-11-04 at 09.24.03.avif` | `WhatsApp Image 2025-11-04 at 09.24.06.avif` |
| 2 | `IMG_3812.avif` | `IMG_38112.avif` (After) / `IMG_3811 (1).avif` (BeerSlider right) |
| 3 | `gh.avif` (BeerSlider left) / `5B17FF65...` (fb slider) | `jkl.avif` (BeerSlider right) / `4B85E361...` (fb slider) |
| 4 | `IMG_3794 (1).avif` | `IMG_3795.avif` |
| 5 | Composite pair (reused images from pair 1) | Composite pair |
| 6 | `WhatsApp Image 2025-10-20 at 04.48.15 (1).avif` | `WhatsApp Image 2025-10-20 at 04.48.18 - Copy (2).avif` |

**Thumbnail navigation** — 6 thumbnail images in a row below the slider:

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `before-after-button-main-block` |

Each thumbnail: `tab_nav_block width` class, contains an image (`tab_nav_image`).
- Default: small size, `border: 2px solid #848484`, `border-radius: 5px`
- Active (`.tab1` or selected): larger size, `border-color: #fc5f2b`

#### Right Column — Text (`before-after-left-block` text side)

> Note: In the original HTML, the text heading is **not visible** in the main `before-after-main-block`. The heading "Stop Dreaming, Start Smiling!" and "Real-Life Transformations." appear to be hidden or positioned differently. Check the style.css for visibility. If visible, include:

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
selector .tab_nav_block {
  display: inline-block;
  overflow: hidden;
  cursor: pointer;
}
selector .tab_nav_block .tab_nav_image {
  width: 50px;
  height: 60px;
  border: 2px solid #848484;
  border-radius: 5px;
  object-fit: cover;
}
selector .tab_nav_block.tab1 .tab_nav_image,
selector .tab_nav_block.active .tab_nav_image {
  width: 90px;
  height: 100px;
  border-color: #fc5f2b;
}
/* BeerSlider (if using custom HTML approach) */
selector .bas-wrapper {
  position: relative;
  overflow: hidden;
  border: 5px solid #cdcdcd;
  border-radius: 12px;
}
```

---

### S7 — Video Testimonials (`slider-section-main`)

> **HTML ref**: `<section class="slider-section-main">` → uses Swiper.js (NOT Elementor Media Carousel). 6 slides (3 unique videos × 2 for looping). Each slide is a `background-video-3` (Webflow background video).

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `133px` top/bottom, `0` left/right |
| **Advanced** | CSS Classes | `slider-section-main` |

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

#### Container 2 — Video Carousel (Swiper.js)

> **Approach**: Use an **HTML widget** to embed Swiper.js directly (same as original). The original loads Swiper from CDN: `https://cdn.jsdelivr.net/npm/swiper@11/swiper-bundle.min.js` and CSS: `https://cdn.jsdelivr.net/npm/swiper@11/swiper-bundle.min.css`

**Widget — HTML (Swiper embed)**

```html
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/swiper@11/swiper-bundle.min.css">
<div class="swrper_component">
  <div class="slider_slider-wrapper">
    <div class="swiper-container">
      <div class="swiper-wrapper">
        <!-- Slide 1 -->
        <div class="swiper-slide">
          <video autoplay loop muted playsinline style="width:100%;height:100%;object-fit:cover;border-radius:10px;">
            <source src="[video_1_mp4_url]" type="video/mp4">
          </video>
        </div>
        <!-- Slide 2 -->
        <div class="swiper-slide">
          <video autoplay loop muted playsinline style="width:100%;height:100%;object-fit:cover;border-radius:10px;">
            <source src="[video_2_mp4_url]" type="video/mp4">
          </video>
        </div>
        <!-- Slide 3 -->
        <div class="swiper-slide">
          <video autoplay loop muted playsinline style="width:100%;height:100%;object-fit:cover;border-radius:10px;">
            <source src="[video_3_mp4_url]" type="video/mp4">
          </video>
        </div>
        <!-- Slides 4-6: duplicates of 1-3 for seamless loop -->
        <div class="swiper-slide">
          <video autoplay loop muted playsinline style="width:100%;height:100%;object-fit:cover;border-radius:10px;">
            <source src="[video_1_mp4_url]" type="video/mp4">
          </video>
        </div>
        <div class="swiper-slide">
          <video autoplay loop muted playsinline style="width:100%;height:100%;object-fit:cover;border-radius:10px;">
            <source src="[video_2_mp4_url]" type="video/mp4">
          </video>
        </div>
        <div class="swiper-slide">
          <video autoplay loop muted playsinline style="width:100%;height:100%;object-fit:cover;border-radius:10px;">
            <source src="[video_3_mp4_url]" type="video/mp4">
          </video>
        </div>
      </div>
    </div>
  </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/swiper@11/swiper-bundle.min.js"></script>
<script>
new Swiper(".swiper-container", {
  loop: true,
  speed: 800,
  slidesPerView: 3,
  spaceBetween: 0,
  grabCursor: true,
  simulateTouch: true,
  threshold: 5,
  touchAngle: 45,
  breakpoints: {
    0:   { slidesPerView: 1, centeredSlides: false },
    480: { slidesPerView: 2, centeredSlides: false },
    768: { slidesPerView: 3, centeredSlides: true },
  },
});
</script>
```

> **Video files (3 unique)**: Upload the 3 MP4 videos from the original to WordPress Media Library. The original has `the first video`, `for the middle`, and `the last one` videos.

#### Section Custom CSS

```css
/* Swiper slide styling */
selector .swiper-slide {
  width: 320px;
  height: 450px;
  border-radius: 10px;
  overflow: hidden;
  transition: transform 0.5s ease, opacity 0.5s ease;
}
selector .swiper-slide video {
  width: 100%;
  height: 100%;
  object-fit: cover;
}
selector .swiper-slide:not(.swiper-slide-active) {
  transform: scale(0.85);
  opacity: 0.6;
}
selector .swiper-slide-active {
  transform: scale(1);
  opacity: 1;
}
@media (max-width: 479px) {
  selector .swiper-slide { width: 320px; }
}
@media (max-width: 991px) {
  selector { padding-top: 20px; }
}
```

---

## Step 4 — S8-S11

---

### S8 — Process / Smile Journey (`smile-section`)

> **HTML ref**: `<section id="process" class="smile-section">` → uses numbered timer images (timer_1.png through timer_5.png), NOT colored `<span>` text for numbering.

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
| **Advanced** | CSS Classes | `smile-section` |

#### Container (inner — `smile-main-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` |
| **Layout** | Direction | Column |
| **Layout** | Align | Center |
| **Layout** | Gap | `60px` |

#### Widget — Heading (`smile-heading-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `Steps of Your Smile Journey` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |
| **Style** | Text Color | `#ffffff` |
| **Advanced** | CSS Classes | `section-heading normal` |

#### Cards Grid Container (`smile-contents-main-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `smile-grid` |

#### Each Process Card (×5) — nested Container (`smile-content-block`)

> ⚠️ **Key difference from previous implementation**: Each card does NOT use `<span style="color:#fc5f2b">01.</span>` inside the heading. Instead, each card has a **numbered timer image** (`timer_1.png` through `timer_5.png`) displayed next to the heading text.

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Column |
| **Layout** | Align | Start |
| **Layout** | Gap | `4px` |
| **Style** | Background | `#ffffff` |
| **Style** | Border Radius | `24px` |
| **Advanced** | Padding | `20px 30px` |
| **Advanced** | CSS Classes | `smile-content-block` |

Inside each card:
- **Container** (`div-block-5`) — Direction: Row, Align: Center, Gap: `8px`
  - **Image** (`image-4`): numbered timer icon, width `auto`
  - **Heading** (`smile-heading`): Cal Sans, `24px`, line-height `144%`, color `#181818`
- **Text Editor** (`smile-subheading`): Hanken Grotesk, `14.5px`, line-height `160%`, color `#4d4d4d`

**Cards (exact content from index.html):**

| # | Timer Image | Title | Description |
|---|------------|-------|-------------|
| 1 | `timer_1.png` | Start Your Online Consultation. | Share your dental concerns and smile goals through our simple online form or WhatsApp. |
| 2 | `timer_2.png` | Receive Your Treatment Plan & Quote | Get a personalised treatment plan and an all-inclusive package options tailored to your needs. |
| 3 | `timer_3.png` | First Day at the Clinic | Meet our expert team, tour our modern facility, complete your scans, and finalise your treatment plan. |
| 4 | `4g_mobiledata.png` | Begin Your Treatment Journey | Experience world-class dental care with advanced technology and premium materials. |
| 5 | `timer_5_shutter.png` | Follow-Up & Aftercare | We stay connected after your treatment to ensure smooth recovery and long-lasting results. |

#### Section Custom CSS

```css
/* Grid layout: first 4 cards span 2 columns each (2 per row), card 5 spans middle */
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

### S9 — Reviews / Testimonials (`testimonials-sections`)

> **HTML ref**: `<section id="reviews" class="testimonials-sections">` — Uses TWO scrolling marquee rows. Row 1 scrolls left, Row 2 (`.second-testimonials`) scrolls right. Each row contains **13 review cards** duplicated (26 total per row for seamless loop). All reviewer data is real Google review data.

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `70px` top/bottom |
| **Advanced** | CSS ID | `reviews` |
| **Advanced** | CSS Classes | `testimonials-sections` |

#### Container

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Layout** | Direction | Column |
| **Layout** | Gap | `60px` |

#### Widget — Heading

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Title | `What Our Patients Say` |
| **Content** | Tag | H2 |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `35px`, weight `400`, line-height `160%` |

#### Testimonial Rows — Custom HTML widget

> **Approach**: Use a single **HTML widget** containing the full marquee markup. This matches the original which uses Webflow IX2 `transform: translate3d()` animation. In Elementor, we drive this via CSS `@keyframes`.

**Each Review Card HTML structure** (matching original class names):

```html
<div class="testimonial-main-content-block">
  <div class="testimonial-heading-blocks">
    <div class="author-info-block">
      <img src="[avatar_url]" class="author-image" alt="reviewer image">
      <div class="author-info">
        <div class="author-name">[Name]</div>
        <div class="author-state">[Country/Level]</div>
      </div>
    </div>
    <img src="[stars_image_url]" class="rating" alt="rating">
  </div>
  <div class="testimonial-description">[Review text...]</div>
</div>
```

**Reviewer data (13 reviewers, exact from index.html):**

| # | Name | Country/Level | Review (abbreviated) |
|---|------|--------------|---------------------|
| 1 | **jmmy B.** | Local Guide Level 5 | I'm so happy I found this place! Living abroad... best dental experience I've ever had. |
| 2 | Jazmyn Tursina | Local Guide Level 3 | I had such a great experience here for my dental spa treatment!... |
| 3 | Masna Sidabuta | Local Guide Level 2 | We had a wonderful experience at CS Dental with Dr. Theresa... |
| 4 | Josie Dillon | United States | Couldn't not remember this place more! amazing for English speaking visitors... |
| 5 | Devi Satyarani | United States | Got my braces here, every staff was so wonderful and kind. |
| 6 | Alice Copeland | United States | The team at CS Dental were amazing! The office is welcoming... |
| 7 | Avril W | United States | Best dentist in the island! Staff is very welcoming... |
| 8 | Ryan Jusuf | United States | The dentist is very friendly and professional... |
| 9 | Anna Rall | United States | The best dental service all over Bali. Super friendly doctors... |
| 10 | Vanessa Alessandro | United States | I had a great experience at CS Dental Bali... |
| 11 | nick theo | United States | Been in Bali for 2 years now and CS Dental Bali is by far the best... |
| 12 | elly Wagener | United States | Best service eva! They even squeezed me in on the tight schedule... |
| 13 | Cinnamon Dorn | United States | Fantastic dental clinic. Highly recommended, gentle and caring. |

> Embed the **full review text** from `index.html` — do NOT abbreviate. Each reviewer has an avatar image to upload.

**Row structure:**

```html
<!-- Row 1: scrolls LEFT -->
<div class="testimonial-first-marquee-main-block">
  <div class="testimonial-first-marquee-block">
    <!-- All 13 review cards here -->
  </div>
  <div class="testimonial-first-marquee-block">
    <!-- Duplicate of all 13 review cards for seamless loop -->
  </div>
</div>

<!-- Row 2: scrolls RIGHT -->
<div class="testimonial-first-marquee-main-block second-testimonials">
  <div class="testimonial-first-marquee-block testimonial-second-marquee-block">
    <!-- All 13 review cards here -->
  </div>
  <div class="testimonial-first-marquee-block testimonial-second-marquee-block">
    <!-- Duplicate of all 13 review cards -->
  </div>
</div>
```

#### Section Custom CSS

```css
/* Review card */
selector .testimonial-main-content-block {
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
selector .testimonial-heading-blocks {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  width: 100%;
}
selector .author-info-block {
  display: flex;
  gap: 12px;
  align-items: center;
}
selector .author-image {
  width: 42px;
  border-radius: 50%;
}
selector .author-name {
  font-family: 'Cal Sans', sans-serif;
  font-size: 32px;
  line-height: 160%;
}
selector .author-state {
  color: #d78e4b;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 18px;
  line-height: 160%;
}
selector .testimonial-description {
  color: #574f48;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 16px;
  line-height: 160%;
  overflow: auto;
}
/* Marquee rows */
selector .testimonial-first-marquee-main-block {
  display: flex;
  overflow: hidden;
}
selector .testimonial-first-marquee-block {
  display: flex;
  flex: none;
  animation: reviewScrollLeft 40s linear infinite;
}
selector .testimonial-first-marquee-main-block.second-testimonials .testimonial-first-marquee-block {
  animation: reviewScrollRight 40s linear infinite;
}
selector .testimonial-first-marquee-main-block:hover .testimonial-first-marquee-block {
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
  selector .testimonial-main-content-block {
    max-width: 360px;
    padding: 15px;
    border-radius: 8px;
  }
  selector .author-name { font-size: 22px; }
  selector .author-state, selector .testimonial-description { font-size: 14px; }
}
@media (min-width: 1920px) {
  selector { padding-top: 120px; padding-bottom: 120px; }
}
```

---

### S10 — Contact Form (`contact-section`)

> **HTML ref**: `<section id="contact" class="contact-section">` — The form is a **custom Webflow form** (NOT Elementor Pro Form widget). It has a custom country code dropdown with flag icons, phone input with digits-only restriction, and UTM tracking hidden fields. The form's glassmorphic styling is embedded inline.

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
| **Advanced** | CSS Classes | `contact-section` |

#### Container (flex row — `contact-main-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `1480px` |
| **Layout** | Direction | Row |
| **Layout** | Justify | Center |
| **Layout** | Align | Center |
| **Layout** | Gap | `70px` |

#### Left Column — Form side (`contact-left-block`)

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

**Widget 3 — Form**

> ⚠️ **Two options depending on how close you want to match:**

**Option A — Use Elementor Pro Form widget (simpler, some differences):**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Fields | Full Name (text, required), Email Address (email, req), WhatsApp Number (tel, req), Tell us about your dental needs (textarea, optional) |
| **Content** | Submit Text | `Get Your Free Consultation` |
| **Style** | Label Color | `#ffffff` |
| **Style** | Label Typography | Cal Sans, `16px`, weight `400` |
| **Style** | Input BG | `#ffffff` |
| **Style** | Input Border | `1px solid #d1d1d1` |
| **Style** | Input Border Radius | `12px` |
| **Style** | Input Typography | Hanken Grotesk, `14px`, line-height `160%` |
| **Style** | Button BG | `#ff5a1f` |
| **Style** | Button Hover BG | `#ff743a` |
| **Style** | Button Border Radius | `14px` |
| **Style** | Button Typography | Cal Sans, `16px`, weight `600` |
| **Style** | Button Color | `#ffffff` |
| **Style** | Button Padding | `16px` |
| **Advanced** | CSS Classes | `consult-form` |

> Note: The original has a **Treatment select dropdown** field but it has `class="hide"` — it's hidden in the live version. Skip this field or add and hide via CSS.

**Option B — Custom HTML form (closer to original):**

Use an HTML widget and paste the form markup from the original, including the country code dropdown with flag images and the custom JS. This requires the `consult-form` CSS (already in the original's inline styles). Add the form CSS to the section's Custom CSS.

**Below the form (footnote):**
- Text: "We reply within 24 hours. Your information is private and secure." — Hanken Grotesk, `12px`, white, centered, opacity `0.9`

#### Right Column — Image (`contact-right-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | Max Width | `726px` |

**Widget — Image**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Image | Upload `Frame 5605.avif` (smiling person) |
| **Style** | Width | `100%` |
| **Style** | Border Radius | `20px` |
| **Advanced** | CSS Classes | `contact-image` |

#### Section Custom CSS

```css
/* Glassmorphic form container */
selector .consult-form {
  background: linear-gradient(135deg, #7fb2c6, #9fb5bf);
  border-radius: 20px;
  padding: 32px;
  max-width: 600px;
}
/* Form labels */
selector .field-label {
  font-family: 'Cal Sans', sans-serif;
  font-weight: 400;
  font-size: 16px;
  line-height: 14px;
  color: #ffffff;
  display: block;
  margin: 14px 0 6px;
}
selector .text-span, selector .text-span-2 {
  color: #ff1a1a;
}
/* Form inputs */
selector .text-field,
selector .textarea {
  border: 1px solid #d1d1d1;
  border-radius: 12px;
  padding: 14px 16px;
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 14px;
  line-height: 1.4;
  background-color: #ffffff;
  color: #000;
  width: 100%;
}
selector .text-field:focus,
selector .textarea:focus {
  border-color: #ff5a1f;
  box-shadow: 0 0 0 2px rgba(255, 90, 31, 0.2);
  outline: none;
}
selector .textarea {
  min-height: 120px;
  resize: none;
}
/* Submit button */
selector .submit-button {
  background: #ff5a1f;
  border-radius: 14px;
  padding: 16px;
  font-size: 16px;
  font-weight: 600;
  width: 100%;
  margin-top: 18px;
  color: #ffffff;
  border: none;
  cursor: pointer;
}
selector .submit-button:hover {
  background: #ff743a;
}
/* Footnote */
selector .text-block-39 {
  font-family: 'Hanken Grotesk', sans-serif;
  font-size: 12px;
  opacity: 0.9;
  margin-top: 12px;
  color: #ffffff;
  text-align: center;
}
/* Required asterisk color (if using Elementor Pro Form) */
selector .elementor-mark-required .elementor-field-label:after {
  color: #ff1a1a !important;
}
/* Tablet: stack */
@media (max-width: 991px) {
  selector > .elementor-container {
    flex-direction: column;
  }
}
@media (max-width: 479px) {
  selector .consult-form {
    padding: 24px;
    border-radius: 16px;
  }
}
@media (min-width: 1920px) {
  selector { padding: 144px 20px; }
}
```

---

### S11 — Who We Are (`who-section`)

> **HTML ref**: `<section class="who-section">` → `who-main-block` → heading + 4-cell bento grid (Our Story, clinic photo, image slider with **5 slides**, Our Vision).

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `60px` top/bottom, `20px` left/right |
| **Advanced** | CSS Classes | `who-section` |

#### Container 1 — Heading (`who-heading-block`)

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
| **Content** | Tag | DIV (the original uses `<div class="who-heading">`, not `<h2>`) |
| **Content** | Alignment | Center |
| **Style** | Typography | Cal Sans, `60px`, weight `400` |
| **Advanced** | CSS Classes | `who-heading` |

#### Container 2 — Bento Grid (`who-main-content-section`)

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `who-grid` |
| **Advanced** | Margin | `40px 0 0 0` (top gap) |

**Grid Cell 1 (Row 1 Left) — Our Story** (`who-content-block`)

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
- **Heading** (`who-content-heading`): `Our Story`, Cal Sans, `35px`, line-height `160%`
- **Container** (`who-subtext-block`): Direction: Column, Gap: `16px`
  - **Text 1**: "Founded by the visionary Drg. Cindy Saconk in 2008, CSmile Dental Clinic was born from a commitment to blend unparalleled craftsmanship with patient centered care."
  - **Text 2**: "From its very inception, CSmile has aimed to elevate the standards of dental excellence in Bali, combining cutting edge technology with the warmth and hospitality that the island is known for."
  - Style: Hanken Grotesk, `16px`, line-height `160%`

**Grid Cell 2 (Row 1 Right) — Clinic Photo** (`who-image-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Border Radius | `20px` |
| **Advanced** | Overflow | Hidden |

Inside: Image widget — `Untitled design (1) 1.avif`, 100% width, object-fit cover

**Grid Cell 3 (Row 2 Left) — Image Slider** (`who-image-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Style** | Border Radius | `20px` |
| **Advanced** | Overflow | Hidden |

Inside: **Image Carousel** (Elementor Pro) — **5 slides**, numbered dots, arrow navigation

**5 slider images (from index.html):**
1. `DSC00128 (1).avif`
2. `DSC00137 (2) (1).avif`
3. `566284635_2173452333486445_6345457196528964642_n.avif`
4. `WhatsApp Image 2025-10-21 at 17.11.20.avif`
5. `WhatsApp Image 2025-09-16 at 19.15.15_d1ceef67.avif`

Carousel settings: autoplay off (original has `data-autoplay="false"`), arrows visible, dot navigation (numbered), duration `500ms`, infinite loop.

**Grid Cell 4 (Row 2 Right) — Our Vision** (`who-content-block`)

Same structure as Our Story cell.

Inside:
- **Heading**: `Our Vision`, Cal Sans, `35px`, line-height `160%`
- **Container** (`who-subtext-block`): Direction: Column, Gap: `16px`
  - **Text 1**: "At CSmile Bali Clinics, our vision is to shape the future of modern dentistry by combining innovation, precision, and trust."
  - **Text 2**: "We aspire to be the first choice for patients worldwide who seek excellence in both health and aesthetics."
  - **Text 3**: "By uniting advanced technology with personalized care, we create smiles that go beyond treatment to inspire confidence and joy."

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
  selector .who-heading { font-size: 60px; }
}
@media (max-width: 479px) {
  selector { padding: 40px 0; }
  selector .who-grid > * { padding: 20px; }
}
```

---

## Step 5 — S12-S13 + Floating + Animations

---

### S12 — Licensed (`licensed-section`)

> **HTML ref**: `<section class="licensed-section">` → `licensed-container` → `licensed-main-block` → heading + 4 card grid

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` |
| **Style** | Background | `#ffffff` |
| **Advanced** | Padding | `80px` top/bottom, `50px` left/right |
| **Advanced** | CSS Classes | `licensed-section` |

#### Container 1 — Heading Block (`licensed-heading-block`)

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
| **Advanced** | CSS Classes | `section-heading _40px-desktop` |

**Widget 2 — Text Editor**

| Tab | Property | Value |
|-----|----------|-------|
| **Content** | Text | `Government Authorities and Recognized Institutions - Indonesia` |
| **Content** | Alignment | Center |
| **Style** | Typography | Hanken Grotesk, `20px`, line-height `160%` |
| **Style** | Text Color | `#574f48` |
| **Advanced** | CSS Classes | `text-block-33` |

> ⚠️ Note: The original uses a dash `-` not an em-dash `—`. Match exactly.

#### Container 2 — Card Grid (`licensed-card-main-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Advanced** | CSS Classes | `licensed-grid` |
| **Advanced** | Margin | `40px 0 0 0` |

#### Each Licensed Card (×4) — Container (`licensed-card-block`)

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
- **Image** (`licensed-image`): institution logo, max-height `150px`, centered
- **Text** (`licensed-card-text`): Hanken Grotesk, `11px`, line-height `160%`, center, max-width `253px`

**Cards (exact from index.html):**

| # | Logo File | Text |
|---|----------|------|
| 1 | `Copy of Certificates 1.avif` | Persatuan DokterGigi Indonesia(PDGI) Indonesian Dental Association |
| 2 | `Layer_1.avif` | KementerianKesehatan RepublikIndonesis(RI) Ministry of HealthRepublic Indonesia |
| 3 | `Copy of Certificates 3.avif` | Kementerian Pariwisatadan Ekonomi Kreatif (Kemenparekraf) Ministry of Tourism and Creative Economy |
| 4 | `Copy of Certificates 4.avif` | Dinas KesehatanProvinsi Bali Ball ProvincialHealth Office |

> ⚠️ The text has odd line breaks/spacing from the original HTML. Keep as-is for accuracy or clean up the spacing while preserving the same content.

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

### S13 — Footer (`footer`)

> **HTML ref**: `<section class="footer">` → `footer-container` → `footer-main-block` → top 3-col row + bottom bar

**Location**: Elementor → Templates → Theme Builder → Footer → Add New

#### Section

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Full Width |
| **Style** | Background Type | Gradient |
| **Style** | Gradient | `#497ca2` (top) → `#1b2e3c` (bottom), Linear, 0° (bottom-to-top) |
| **Advanced** | Padding | `0` all |
| **Advanced** | CSS Classes | `footer` |

#### Container 1 — Footer Content (`footer-main-block`)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Content Width | Boxed, `940px` |
| **Layout** | Direction | Column |
| **Layout** | Gap | `48px` |
| **Advanced** | Padding | `50px` top, `26px` bottom, `20px` left/right |

#### Top Row — Container `footer-top` (3 columns)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Direction | Row |
| **Layout** | Justify | Space Between |
| **Layout** | Align | Start |
| **Advanced** | CSS Classes | `footer-top` |

**Left Column** (`footer-top-left`, max-width `300px`, direction: column, gap: `16px`, padding: `10px`):

- **Image** (Logo): `image 21 1 (1)-Picsart-AiImageEnhancer.avif`, max-width `220px`, link to `/`
- **Text** (`footer-text`): "Your trusted partner for world-class dental care in the heart of Bali.", Hanken Grotesk, `16px`, white, line-height `150%`
- **Text** (`footer-social-heading`): "Follow us on :", Cal Sans, line-height `162%`, white
- **Container** (`footer-social-div`, direction: Row, gap: `16px`):
  - Image link: Facebook icon → `https://www.facebook.com/profile.php?id=61582604070021`
  - Image link: Instagram icon → `https://www.instagram.com/csmilebali/`

**Middle Column** (`footer-top-middle`, direction: column, gap: `8px`, padding: `10px`):

- **Heading** (`footer-link-heading`): `Quick Links`, Cal Sans, `18px`, white, line-height `155%`, padding-bottom `8px`
- **Link**: Treatments → `/#treatments`
- **Link**: Consultation → `#`
- **Link**: Reviews → `/#reviews`
- **Link**: Contact → `/contact`
- Style: Hanken Grotesk, `16px`, white, line-height `150%`, no underline

**Right Column** (`footer-top-right`, direction: column, gap: `8px`, padding: `10px`):

- **Heading** (`footer-link-heading`): `Contact`, Cal Sans, `18px`, white, line-height `155%`, padding-bottom `8px`
- **Container** (`footer-div`, direction: Row, gap: `12px`, align: Start):
  - Image: phone icon (`Icon (2).png`)
  - Link: `+62 813 3786 031` → `tel:+628133786031`
- **Container** (`footer-div`):
  - Image: email icon (`Icon (3).png`)
  - Link: `info@csmilebali.com` → `mailto:info@csmilebali.com`
- **Container** (`footer-div`):
  - Image: location icon (`Icon (4).png`)
  - Link: `Jl. Bypass Ngurah Rai, Kuta, Kec. Kuta, Kabupaten Badung, Bali 80361, Indonesia` → `https://maps.app.goo.gl/Gshvb1CQnD3N3RHn7` (target: `_blank`)

#### Bottom Bar — Container (`footer-bottom`)

| Tab | Property | Value |
|-----|----------|-------|
| **Layout** | Align | Center |
| **Style** | Border Type | Solid |
| **Style** | Border Width | `1px 0 0 0` (top only) |
| **Style** | Border Color | `#ffffff` |
| **Advanced** | Padding | `18px` top/bottom |

- **Text** (`text-block-36`): `2025 CSmile Bali. All rights reserved.`, center, Hanken Grotesk, `16px`, white

> Note: The original uses "2025" not "© 2025".

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
  selector .footer-top {
    flex-direction: column;
  }
}
@media (max-width: 479px) {
  selector .elementor-container { padding-top: 40px; padding-bottom: 0; }
  selector .footer-bottom { padding-top: 10px; padding-bottom: 10px; }
  selector .footer-text { font-size: 14px; }
  selector .footer-link-heading { font-size: 16px; padding-bottom: 4px; }
}
@media (min-width: 1920px) {
  selector .elementor-container { padding-top: 40px; }
  selector .footer-bottom { padding-top: 12px; padding-bottom: 12px; }
}
```

**Display Condition**: Entire Site.

---

### Floating — WhatsApp Button

> **HTML ref**: `<a class="lottie-animation whp w-inline-block">` — positioned fixed, bottom-right, with WhatsApp SVG icon. Background: `rgba(35, 179, 58, 0.3)` (semi-transparent green).

**Method 1**: Install **Click to Chat** plugin.

| Setting | Value |
|---------|-------|
| Phone Number | `628133786031` |
| Pre-filled Message | `Hi CSmile Bali! I'd love to get information about my possible dental/smile treatment. I am looking for ` |
| Position | Bottom Right |
| Bottom Offset | `20px` |
| Right Offset | `50px` |
| Size | `60px` |
| Border | `1px solid #23b33a` |
| Border Radius | `100px` |
| Z-Index | `99` |
| Icon Color | `#23b33a` |

> Note the pre-filled message includes UTM parameters in the original: `&utm_source=website&utm_medium=whatsapp_button&utm_campaign=main_cta`

**Method 2 — Custom HTML** (closer to original, add as Elementor HTML widget on page):

```html
<a href="https://wa.me/628133786031?text=Hi%20CSmile%20Bali!%20I%E2%80%99d%20love%20to%20get%20information%20about%20my%20possible%20dental%2Fsmile%20treatment.%20I%20am%20looking%20for%20&utm_source=website&utm_medium=whatsapp_button&utm_campaign=main_cta"
   class="wa-fab" target="_blank" rel="noopener">
  <svg style="color:rgb(34,235,65)" xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none">
    <g>
      <path d="M17.496 14.3828C17.1952 14.2305 15.7305 13.5158 15.4567 13.4138C15.183 13.3163 14.9842 13.2652 14.7847 13.566C14.5897 13.8592 14.0152 14.5305 13.8397 14.7263C13.6642 14.922 13.4917 14.937 13.1955 14.8043C12.8947 14.652 11.934 14.3392 10.7932 13.3162C9.90225 12.5235 9.309 11.547 9.13275 11.2462C8.95725 10.9492 9.11325 10.7813 9.26175 10.6328C9.39825 10.4963 9.5625 10.2893 9.71475 10.1093C9.8595 9.92925 9.906 9.8085 10.0117 9.6135C10.1092 9.40275 10.059 9.2385 9.98475 9.09C9.9105 8.9415 9.31275 7.46925 9.063 6.88275C8.8245 6.30075 8.57475 6.375 8.391 6.375C8.21925 6.35925 8.01975 6.35925 7.821 6.35925C7.62225 6.35925 7.2975 6.4335 7.02375 6.7185C6.75 7.01925 5.97675 7.73775 5.97675 9.19125C5.97675 10.6485 7.047 12.0585 7.1955 12.2692C7.34775 12.4642 9.30075 15.4642 12.297 16.7535C13.0117 17.0542 13.5667 17.2343 14.0002 17.3828C14.715 17.6093 15.3675 17.5777 15.8828 17.5035C16.4528 17.4097 17.6482 16.7805 17.8987 16.0778C18.153 15.3705 18.153 14.7847 18.0787 14.652C18.0045 14.5155 17.8095 14.4412 17.5087 14.3085L17.496 14.3828ZM12.0623 21.75H12.0465C10.2728 21.75 8.51925 21.2692 6.98775 20.3707L6.6285 20.1562L2.8785 21.1328L3.8865 17.484L3.64425 17.109C2.65575 15.5348 2.1285 13.7183 2.1285 11.8515C2.1285 6.4065 6.58575 1.965 12.0698 1.965C14.7263 1.965 17.2185 3 19.0935 4.875C20.9685 6.73425 22.0035 9.2265 22.0035 11.8672C21.996 17.3085 17.5425 21.75 12.066 21.75H12.0623ZM20.5192 3.44925C18.2377 1.24575 15.2378 0 12.0465 0C5.4645 0 .105 5.33625.10125 11.8943C.10125 13.9883.648 16.0312 1.695 17.8395L0 24L6.336 22.3478C8.082 23.289 10.047 23.793 12.0472 23.7968H12.051C18.6368 23.7968 23.9963 18.4605 24 11.898C24 8.7225 22.7618 5.73375 20.5043 3.4875L20.5192 3.44925Z" fill="currentColor"></path>
    </g>
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
  background-color: rgba(35, 179, 58, 0.3);
  border: 1px solid #23b33a;
  border-radius: 100px;
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 99;
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

> ⚠️ Note: The original has `background-color: rgba(35, 179, 58, 0.3)` (semi-transparent green), NOT white background like the previous implementation stated.

---

### Animation Recreation (from scripts.js)

These animations were handled by Webflow IX2. Here's how to recreate each in Elementor 3.35.0:

| # | Original Effect | Elementor Setup | Applied To |
|---|----------------|----------------|------------|
| 1 | **Fade In Up on load** | Widget → Advanced → Motion Effects → Entrance Animation: `Fade In Up`, Duration `800ms` | Hero heading, description, CTA button (stagger delays: 0/200/400ms) |
| 2 | **Fade In Up on scroll** | Widget → Advanced → Motion Effects → Entrance Animation: `Fade In Up` | Step cards, treatment cards, service elements, process cards |
| 3 | **Marquee scroll** | CSS `@keyframes` animation on HTML widget | Lab images (S5), Testimonial rows (S9) |
| 4 | **Premium bar hover** | CSS transition on `.premium-material-div` (width 0→100%), triggered by hovering `.premium-material-hover-block` | Lab feature blocks (S5) |
| 5 | **Before/After slider** | Plugin or custom HTML (BeerSlider) — range input driving clip-path or reveal width | Before/After section (S6) |
| 6 | **Tab switching** | Custom JS toggling `.hide` class on `bas-wrapper` elements, or use Elementor Pro Tabs | Before/After thumbnails (S6) |
| 7 | **Swiper carousel** | Custom HTML embed with Swiper.js CDN (v11) | Video testimonials (S7) |
| 8 | **Webflow Slider** | Elementor Image Carousel widget with **5 slides**, arrows, numbered dots, no autoplay | Who We Are clinic photos (S11) |
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
- [ ] CSS IDs set: `hero`, `treatments`, `services`, `process`, `contact`, `reviews`
- [ ] All navbar anchor links work (#hero, #treatments, #services, #process, #contact)

### Interactive Features Checklist

- [ ] Contact form submits (with country code dropdown if using custom HTML approach)
- [ ] Before/After slider working with 6 image pairs + thumbnail switching
- [ ] Video carousel showing 3 slides on desktop (Swiper.js)
- [ ] Lab marquee scrolling smoothly (no gap/flicker on loop)
- [ ] Image carousel in Who We Are section — 5 slides, arrows, numbered dots
- [ ] WhatsApp FAB visible and links to correct number with UTM params

### Animation Checklist

- [ ] Hero entrance animations (fade in up, staggered)
- [ ] Scroll-triggered fade-in on Steps, Treatments, Services
- [ ] Lab feature hover bar animates (width 0→100% on `.premium-material-div`)
- [ ] Navbar sticky on scroll
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
- [ ] Video hosted in WP Media or externally (keep file sizes reasonable)
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

