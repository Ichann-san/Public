# CSmile Bali — Website Analysis & Slicing Guide

> **Source**: [csmilebali.webflow.io](https://csmilebali.webflow.io/)
> **Target**: WordPress + Elementor replication
> **Sections identified**: 12 (Navbar + 10 body sections + Footer) + 1 floating element

---

## Table of Contents

1. [Global Design System](#global-design-system)
2. [Task 1 — ASCII Wireframe & Architecture](#task-1--ascii-wireframe--architecture)
3. [Task 2 — Component & Container Breakdown](#task-2--component--container-breakdown)
4. [Task 3 — Screenshot ↔ HTML Matching & Animation Notes](#task-3--screenshot--html-matching--animation-notes)

---

## Global Design System

### Typography

| Role | Font Family | Weights Used |
|------|------------|-------------|
| Headings | **Cal Sans** | 300–700 |
| Body / UI | **Hanken Grotesk** | 300–700 |

### Color Palette

| Token | Hex | Usage |
|-------|-----|-------|
| Dark BG (hero/gradient) | `#1a2a3a` → `#2a4a5a` | Hero, Before/After, Process, Contact, Footer |
| White BG | `#ffffff` | Steps, Treatments, Reviews, Licensed, Who We Are |
| Light Gray BG | `#f5f5f5` – `#f9f9f9` | Card backgrounds |
| Orange (CTA) | `#ff5a1f` / `#ff6b35` | Buttons, step numbers, badges |
| Text White | `#ffffff` | On dark backgrounds |
| Text Dark | `#1a1a1a` / `#282735` | On light backgrounds |
| Text Muted | `#666` / `#888` | Subheadings, descriptions |
| Gold | `#c4a35a` | Licensed section logos |
| Green (WhatsApp) | `#23b33a` | WhatsApp floating button |
| Star Yellow | `#f5a623` | Review stars |

### Global Reusable Elements

| Element | Description | Elementor Equivalent |
|---------|-------------|---------------------|
| **Sticky Navbar** | Glassmorphic, fixed top | Header (Elementor Pro) or sticky section |
| **CTA Button** | Orange pill, white text, hover glow | Button widget |
| **Section Heading** | Cal Sans, centered or left, ~36–48px | Heading widget |
| **Section Sub-heading** | Hanken Grotesk, muted, ~18px | Text Editor widget |
| **WhatsApp FAB** | Fixed bottom-right, green circle + WA icon | Floating button (plugin/custom) |
| **Container** | Max-width ~940px (Webflow `w-container`) | Boxed content width in Elementor |

---

## Task 1 — ASCII Wireframe & Architecture

### Full Page Structure (top → bottom)

```
┌─────────────────────────────────────────────────────────────────┐
│ SECTION 0: NAVBAR (sticky, glassmorphic)                        │
│ ┌─────────────────────────────────────────────────────────────┐ │
│ │ [Logo]     Home  Treatments  Services  Process  Contact     │ │
│ │                                          [Free Consultation]│ │
│ └─────────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 1: HERO (full viewport, dark gradient + video BG)       │
│ ┌─────────────────────────────────────────────────────────────┐ │
│ │                                          ┌──────────────┐  │ │
│ │  Your life-changing smile,               │              │  │ │
│ │  Now affordable in Bali                  │  3D Dental   │  │ │
│ │                                          │  Implant     │  │ │
│ │  Start your all-inclusive smile...       │  (from video │  │ │
│ │  Licensed by Ministry of Health...       │   BG)        │  │ │
│ │                                          │              │  │ │
│ │  [Get Your Free Consultation]            └──────────────┘  │ │
│ └─────────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 2: STEPS (white BG, 3 columns)                          │
│ ┌──────────────┐  ┌──────────────┐  ┌──────────────┐           │
│ │ 🦷 icon      │  │ ⏱ icon       │  │ 💲 icon      │           │
│ │ Step by step │  │ No wait      │  │ Save 50%     │           │
│ │ consultation │  │ times        │  │ on Your      │           │
│ │              │  │              │  │ Dental       │           │
│ │ description  │  │ description  │  │ Treatment    │           │
│ └──────────────┘  └──────────────┘  └──────────────┘           │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 3: TREATMENTS (white BG, centered heading + 5-col grid) │
│                                                                  │
│   "Our Treatments Made with High Care and Precision"            │
│                                                                  │
│ ┌────┐  ┌────┐  ┌────┐  ┌────┐  ┌────┐                        │
│ │img │  │img │  │img │  │img │  │img │                        │
│ │    │  │    │  │    │  │    │  │    │                        │
│ ├────┤  ├────┤  ├────┤  ├────┤  ├────┤                        │
│ │name│  │name│  │name│  │name│  │name│                        │
│ │desc│  │desc│  │desc│  │desc│  │desc│                        │
│ └────┘  └────┘  └────┘  └────┘  └────┘                        │
│ Implant  Crown  Hollywood Veneer  Invisalign                    │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 4: SERVICES (white BG, 2-column layout)                 │
│ ┌──────────────────────┬──────────────────────────┐             │
│ │ 🌍 Services badge    │                          │             │
│ │                      │   ┌──────────────────┐   │             │
│ │ Our International    │   │                  │   │             │
│ │ Guest Services       │   │  Airport photo   │   │             │
│ │                      │   │  (stacked imgs)  │   │             │
│ │ Personalized support │   │                  │   │             │
│ │                      │   └──────────────────┘   │             │
│ │ ┌──────────────────┐ │                          │             │
│ │ │🚗 Airport &      │ │                          │             │
│ │ │  Clinic Transfer │ │                          │             │
│ │ │  description     │ │                          │             │
│ │ └──────────────────┘ │                          │             │
│ │ ┌──────────────────┐ │                          │             │
│ │ │🏨 Luxury         │ │                          │             │
│ │ │  accommodation   │ │                          │             │
│ │ │  description     │ │                          │             │
│ │ └──────────────────┘ │                          │             │
│ └──────────────────────┴──────────────────────────┘             │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 5: IN-HOUSE LAB (light gray → white BG)                 │
│                                                                  │
│   "In-House Lab Ensures Precise, Aesthetic Restorations"        │
│                                                                  │
│ ┌─────────────────────────────────────────────────────┐         │
│ │  [MARQUEE: 3 lab images scrolling left ← ← ← ]    │         │
│ │  (duplicated for infinite loop)                     │         │
│ └─────────────────────────────────────────────────────┘         │
│                                                                  │
│ ┌──────────────┐  ┌──────────────┐  ┌──────────────┐           │
│ │ 🔬 icon      │  │ 🔬 icon      │  │ 🔬 icon      │           │
│ │ Premium      │  │ Precision    │  │ In-House     │           │
│ │ Materials    │  │ Crafting     │  │ Control      │           │
│ │ desc         │  │ desc         │  │ desc         │           │
│ │ [hover bar]  │  │ [hover bar]  │  │ [hover bar]  │           │
│ └──────────────┘  └──────────────┘  └──────────────┘           │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 6: BEFORE/AFTER (dark gradient BG, 2-column)            │
│ ┌──────────────────────┬──────────────────────────┐             │
│ │ ┌──────────────────┐ │                          │             │
│ │ │ BEFORE | AFTER   │ │  Stop Dreaming, Start    │             │
│ │ │ ←──┤handle├──→   │ │  Smiling!                │             │
│ │ │ (slider compare) │ │  Real-Life               │             │
│ │ └──────────────────┘ │  Transformations.        │             │
│ │                      │                          │             │
│ │ [thumb][thumb][thumb] │  See the life-changing   │             │
│ │ [thumb][thumb][thumb] │  results achieved...     │             │
│ └──────────────────────┴──────────────────────────┘             │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 7: VIDEO TESTIMONIALS (white BG, Swiper carousel)       │
│                                                                  │
│   "Real Transformations, Real Confidence."                      │
│                                                                  │
│  ┌────────┐  ┌──────────┐  ┌────────┐                          │
│  │ video  │  │  video   │  │ video  │   ← swipeable            │
│  │ thumb  │  │  thumb   │  │ thumb  │                           │
│  │ (small)│  │ (center) │  │(small) │                           │
│  └────────┘  └──────────┘  └────────┘                           │
│              ◀           ▶                                      │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 8: PROCESS (gradient BG: dark teal → blue → salmon)     │
│                                                                  │
│   "Steps of Your Smile Journey"                                 │
│                                                                  │
│ ┌────────────────────────┐  ┌────────────────────────┐          │
│ │ 1 Start Your Online    │  │ 2 Receive Your         │          │
│ │   Consultation.        │  │   Treatment Plan       │          │
│ │   description          │  │   & Quote              │          │
│ └────────────────────────┘  └────────────────────────┘          │
│ ┌────────────────────────┐  ┌────────────────────────┐          │
│ │ 3 First Day at the     │  │ 4 Begin Your           │          │
│ │   Clinic               │  │   Treatment Journey    │          │
│ │   description          │  │   description          │          │
│ └────────────────────────┘  └────────────────────────┘          │
│        ┌────────────────────────┐                               │
│        │ 5 Follow-Up &          │                               │
│        │   Aftercare            │                               │
│        │   description          │                               │
│        └────────────────────────┘                               │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 9: REVIEWS (white BG, scrolling testimonial cards)      │
│                                                                  │
│   "What Our Patients Say"                                       │
│                                                                  │
│ ┌──────────┐  ┌──────────┐  ┌──────────┐  ← carousel           │
│ │ ★★★★★   │  │ ★★★★★   │  │ ★★★★    │                         │
│ │ avatar   │  │ avatar   │  │ avatar   │                         │
│ │ name     │  │ name     │  │ name     │                         │
│ │ country  │  │ country  │  │ country  │                         │
│ │ review   │  │ review   │  │ review   │                         │
│ └──────────┘  └──────────┘  └──────────┘                         │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 10: CONTACT FORM (dark gradient BG, 2-column)           │
│ ┌──────────────────────┬──────────────────────────┐             │
│ │ Start Your Smile     │  ┌──────────────────┐    │             │
│ │ Journey Today        │  │                  │    │             │
│ │                      │  │  Smiling woman   │    │             │
│ │ Fill out the form... │  │  photo           │    │             │
│ │                      │  │  (rounded)       │    │             │
│ │ ┌──────────────────┐ │  └──────────────────┘    │             │
│ │ │ glassmorphic form│ │                          │             │
│ │ │ First Name *     │ │                          │             │
│ │ │ Last Name *      │ │                          │             │
│ │ │ Email *          │ │                          │             │
│ │ │ WhatsApp * [🇦🇺] │ │                          │             │
│ │ │ Treatment * ▼    │ │                          │             │
│ │ │ Dental needs     │ │                          │             │
│ │ │ [Get Free Consult]│ │                          │             │
│ │ │ privacy note     │ │                          │             │
│ │ └──────────────────┘ │                          │             │
│ └──────────────────────┴──────────────────────────┘             │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 11: WHO WE ARE (white BG, 2x2 bento grid)              │
│                                                                  │
│   "Who We Are"                                                  │
│ ─────────────────────────────────────────                       │
│ ┌──────────────────┬──────────────────────┐                     │
│ │ Our Story        │  [Clinic photo]      │                     │
│ │ Founded by...    │  Dr. Cindy image     │                     │
│ │ description      │                      │                     │
│ └──────────────────┴──────────────────────┘                     │
│ ┌──────────────────┬──────────────────────┐                     │
│ │ [Image Slider]   │  Our Vision          │                     │
│ │  ◀ clinic ▶      │  At CSmile Bali...   │                     │
│ │  1 2 3 4 5       │  description         │                     │
│ └──────────────────┴──────────────────────┘                     │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 12: LICENSED (white BG → soft gradient bottom)          │
│                                                                  │
│   "Officially Licensed By"                                      │
│   Government Authorities...                                     │
│                                                                  │
│ ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐           │
│ │ [PDGI    │ │ [Kemenkes│ │ [Kemen-  │ │ [Dinkes  │           │
│ │  logo]   │ │  logo]   │ │ parekraf]│ │  Bali]   │           │
│ │  text    │ │  text    │ │  text    │ │  text    │           │
│ └──────────┘ └──────────┘ └──────────┘ └──────────┘           │
├─────────────────────────────────────────────────────────────────┤
│ SECTION 13: FOOTER (dark navy BG)                               │
│ ┌──────────────┬──────────────┬──────────────┐                  │
│ │ [Logo]       │ Quick Links  │ Contact      │                  │
│ │ tagline      │ Treatments   │ 📞 phone     │                  │
│ │ Follow us on │ Consultation │ ✉ email      │                  │
│ │ [FB] [IG]    │ Reviews      │ 📍 address   │                  │
│ │              │ Contact      │              │                  │
│ └──────────────┴──────────────┴──────────────┘                  │
│ ─────────────────────────────────────────────                   │
│   2025 CSmile Bali. All rights reserved.                        │
└─────────────────────────────────────────────────────────────────┘

FLOATING: [WhatsApp Button] — fixed bottom-right on every viewport
```

### Architecture Summary

```
page_wrapper
├── navbar (sticky, w-nav)
├── section#hero (hero-section)
│     └── background-video + overlay content
├── section.steps-section
│     └── 3× steps-content-main-block
├── section#treatments (houselab-section)
│     └── heading + 5× houselab-contents
├── section#services (services-section)
│     └── 2-col: left (heading + 2 service cards) | right (2 stacked images)
├── section.made-section (In-House Lab)
│     └── heading + marquee(3 images ×2) + 3× premium-material blocks
├── section.before-after-section
│     └── 2-col: left (slider + tab thumbnails) | right (heading + description)
│     └── also: tabs with udesly before-after slider fallback
├── section.video-section (Swiper carousel)
│     └── heading + swiper-container (3 video slides)
├── section#process (process-section)
│     └── heading + 5× process-card (2-2-1 grid)
├── section.review-section
│     └── heading + scrolling review cards (Swiper or marquee)
├── section#contact (contact-section)
│     └── 2-col: left (heading + glassmorphic form) | right (image)
├── section.who-section
│     └── heading + 2×2 bento grid (text/image alternating)
├── section.licensed-section
│     └── heading + 4× licensed-card
├── section.footer
│     └── 3-col: brand | links | contact + bottom bar
└── WhatsApp floating link (fixed)
```

---

## Task 2 — Component & Container Breakdown

### Reusable Components Inventory

Before diving per-section, here are the **reusable patterns** to create as Elementor **Global Widgets** or **templates**:

| # | Component Name | Used In | Elementor Implementation |
|---|----------------|---------|--------------------------|
| R1 | **Section Heading** | Sections 3,4,5,6,7,8,9,10,11,12 | Heading widget (Cal Sans, 36–48px) |
| R2 | **Section Sub-heading** | Sections 4,6,7,10 | Text Editor (Hanken Grotesk, muted) |
| R3 | **Orange CTA Button** | Hero, Navbar, Contact form | Button widget (pill shape, #ff5a1f) |
| R4 | **Icon + Title + Description Card** | Steps(3), Lab(3) | Icon Box widget |
| R5 | **Image + Text Card** | Treatments(5) | Inner Section: Image + Heading + Text |
| R6 | **Service Card** | Services(2) | Inner Section with Icon + Heading + Text |
| R7 | **Review Card** | Reviews(~6) | Testimonial widget or custom Inner Section |
| R8 | **Process Card** | Process(5) | Inner Section (number + heading + text) |
| R9 | **Licensed Card** | Licensed(4) | Image Box widget (image + text) |
| R10 | **Before/After Slider** | Before/After(6 pairs) | Plugin: "Before After Image Slider" |

---

### Section-by-Section Container Analysis

---

#### Section 0 — Navbar
**Class**: `.navbar.w-nav` (sticky)
**Background**: Semi-transparent dark with blur (glassmorphism)
**Container**: Max-width ~1200px, centered

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Logo | Image (SVG) | Links to `/`, left-aligned |
| 2 | Nav Links (×5) | Text Links | Home, Treatments, Services, Process, Contact Us |
| 3 | CTA Button | Button (R3) | "Free Consultation", orange pill, right-aligned |
| 4 | Hamburger Menu | Icon (mobile) | 3-line animated menu, hidden on desktop |

**Elementor**: Use **Header template** (Elementor Pro) → Nav Menu widget + Button widget. Apply custom CSS for glassmorphic effect (`backdrop-filter: blur()`).

---

#### Section 1 — Hero
**Class**: `.hero-section`
**Background**: Looping background video (dental implant 3D) with dark overlay
**Container**: `hero-container` (max-width ~940px)

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | H1 Heading | Heading | "Your life-changing smile, Now affordable in Bali" (Cal Sans, white, ~48–56px) |
| 2 | Description | Text | Two paragraphs (Hanken Grotesk, white, ~16px) |
| 3 | CTA Button | Button (R3) | "Get Your Free Consultation" |
| 4 | Background Video | Video BG | MP4 + WebM, autoplay, loop, muted |

**Elementor**: Section → Video background. Inner Container with Heading + Text Editor + Button. **4 elements**.

---

#### Section 2 — Steps
**Class**: `.steps-section`
**Background**: White (`#ffffff`)
**Container**: `main-container` (max-width ~940px)

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Step Card ×3 | Icon Box (R4) | Each has: circular icon (pink bg) + bold heading + paragraph |

Each card internally:
- Icon image (circular, light pink background)
- Heading (Cal Sans, bold, ~20px)
- Description (Hanken Grotesk, ~16px)

**Elementor**: Section → 3-column layout → 3× Icon Box widgets. **3 elements**.

---

#### Section 3 — Treatments
**Class**: `.houselab-section` (id=`treatments`)
**Background**: White → very subtle light gray gradient
**Container**: `main-container._95-container` (wider, ~95%)

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading (R1) | "Our Treatments Made with High Care and Precision" |
| 2 | Treatment Card ×5 | Image Card (R5) | Each: image + heading + description |

Each treatment card:
- Image (rounded top, ~260px tall)
- Heading (Cal Sans, ~18px)
- Description (Hanken Grotesk, ~14px)

Cards: Dental Implants, Dental Crowns, Hollywood Smile, Veneers, Invisalign

**Elementor**: Section → Heading + 5-column inner section → 5× Image Box widgets. **6 elements** (1 heading + 5 cards).

---

#### Section 4 — Services
**Class**: `.services-section` (id=`services`)
**Background**: White
**Container**: `main-container` (max-width ~940px)

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Services Badge | Badge | Globe icon + "Services" text (orange border, pill shape) |
| 2 | Section Heading | Heading (R1) | "Our International Guest Services" |
| 3 | Sub-heading | Text (R2) | "Personalized support all in one seamless journey." |
| 4 | Service Card ×2 | Card (R6) | Airport & Clinic Transfers, Luxury Accommodation |
| 5 | Right Image (top) | Image | Airport transfer photo |
| 6 | Right Image (bottom) | Image | Hotel/luxury photo |

Layout: 2-column (left ~45%, right ~55%)
Left: badge + heading + subheading + 2 stacked cards
Right: 2 stacked images (rounded corners, slight rotation/overlap)

**Elementor**: Section → 2 columns. Left: Badge (Image + Text inline) + Heading + Text + 2× Inner Sections. Right: 2× Image widgets with custom CSS positioning. **8 elements**.

---

#### Section 5 — In-House Lab
**Class**: `.made-section`
**Background**: Light gray/white
**Container**: Full-width marquee + contained bottom section

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading (R1) | "In-House Lab Ensures Precise, Aesthetic Restorations" |
| 2 | Image Marquee | Scrolling strip | 3 lab photos × 2 (duplicated for infinite scroll), auto-scroll left |
| 3 | Feature Card ×3 | Icon Box (R4) | Premium Materials, Precision Crafting, In-House Control |

Each feature card:
- Icon (pink circle, microscope/biotech icon)
- Heading (Cal Sans, ~20px)
- Description text
- Bottom border bar (animated on hover, orange)

**Elementor**: Section (heading) + Full-width section (marquee - use "Unlimited Elements" or custom HTML for marquee) + Section (3 columns with Icon Boxes). **5 elements** (1 heading + 1 marquee + 3 icon boxes). Marquee may need a plugin or custom CSS animation.

---

#### Section 6 — Before/After
**Class**: `.before-after-section`
**Background**: Dark teal/blue gradient (same palette as hero)
**Container**: `main-container.margin`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Before/After Slider | Custom Widget (R10) | Drag-to-compare slider with handle |
| 2 | Thumbnail Nav ×6 | Image buttons | Small portrait thumbnails to switch slider |
| 3 | Section Heading | Heading (R1) | "Stop Dreaming, Start Smiling!" |
| 4 | Sub-heading | Heading | "Real-Life Transformations." |
| 5 | Description | Text (R2) | "See the life-changing results..." |

Layout: 2-column
- Left (~50%): Main before/after slider + thumbnail row below
- Right (~50%): Heading + sub-heading + description text

Also includes a **tab-based fallback** (udesly before-after-slider) with 6 tabs, each containing its own slider widget.

**Elementor**: Section → 2 columns. Left: Before/After plugin widget + Image Gallery (thumbs). Right: 2× Headings + Text. **~6 elements + plugin**. Recommended plugin: "Before After Image Slider & Gallery" by developer.

---

#### Section 7 — Video Testimonials
**Class**: `.video-section`
**Background**: White
**Container**: `main-container`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading (R1) | "Real Transformations, Real Confidence." |
| 2 | Swiper Carousel | Slider | 3 video thumbnails visible, center enlarged, draggable |
| 3 | Nav Arrows | Buttons | ◀ ▶ navigation |

Swiper config: `slidesPerView: 3`, `centeredSlides: true`, `loop: true`, breakpoints for mobile.

**Elementor**: Section → Heading + Carousel/Slider widget. **2 elements**. Use Elementor's Image Carousel or a video carousel plugin. Centered slide effect needs custom CSS.

---

#### Section 8 — Process
**Class**: `.process-section` (id=`process`)
**Background**: Multi-color gradient (dark teal → blue → salmon/coral)
**Container**: `main-container`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading (R1) | "Steps of Your Smile Journey" (white, Cal Sans, italic) |
| 2 | Process Card ×5 | Card (R8) | 2-2-1 grid layout |

Each process card:
- Step number (orange, Cal Sans, ~28px)
- Heading (Cal Sans, bold, ~22px, dark)
- Description (Hanken Grotesk, ~15px, dark)
- White card background, rounded corners ~16px

Grid: Row 1 = cards 1-2, Row 2 = cards 3-4, Row 3 = card 5 (centered)

**Elementor**: Section (gradient BG) → Heading + 3 rows of Inner Sections (2-2-1 columns) → 5× Text Editor combos. **6 elements** (1 heading + 5 cards in 3 inner sections).

---

#### Section 9 — Reviews
**Class**: `.review-section`
**Background**: White
**Container**: wide/full-width

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading (R1) | "What Our Patients Say" |
| 2 | Review Card ×6+ | Card (R7) | Scrolling/carousel of testimonial cards |

Each review card:
- Star rating (★★★★★ yellow icons)
- Avatar image (circular)
- Name (Cal Sans, bold, ~20px)
- Country (orange text, ~14px)
- Review text (Hanken Grotesk, ~14–15px)
- White card, border, rounded corners

**Elementor**: Section → Heading + Testimonial Carousel widget. **2 elements** (heading + carousel). Use Elementor Pro Testimonial Carousel or "Reviews" plugin.

---

#### Section 10 — Contact Form
**Class**: `.contact-section` (id=`contact`)
**Background**: Dark gradient (teal/navy, same as hero)
**Container**: `main-container`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading | "Start Your Smile Journey Today" (white) |
| 2 | Sub-heading | Text | "Fill out the form below..." (white, muted) |
| 3 | Form Container | Form | Glassmorphic card (blur bg, semi-transparent border) |
| 4 | First Name field | Input | Required (*) |
| 5 | Last Name field | Input | Required (*) |
| 6 | Email field | Input | Required (*) |
| 7 | WhatsApp field | Phone Input | Country code dropdown (🇦🇺+61) + phone number |
| 8 | Treatment dropdown | Select | "Select treatment" options |
| 9 | Dental needs | Textarea | Multi-line text area |
| 10 | Submit button | Button (R3) | "Get Your Free Consultation" (orange, full-width) |
| 11 | Privacy note | Text | "We reply within 24 hours..." |
| 12 | Right Image | Image | Smiling woman photo (rounded) |
| 13 | Hidden UTM fields | Hidden Inputs | utm_source, utm_medium, etc. |

Layout: 2-column (left ~55% form, right ~45% image)

**Elementor**: Section → 2 columns. Left: 2× Headings + Form widget (WPForms/Elementor Pro Form with custom styling). Right: Image widget. **~14 elements**. Form glassmorphic style needs custom CSS.

---

#### Section 11 — Who We Are
**Class**: `.who-section`
**Background**: White
**Container**: `main-container`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading | "Who We Are" (centered, Cal Sans) |
| 2 | Divider | HR line | Thin horizontal rule |
| 3 | Our Story block | Text card | Heading + 2 paragraphs |
| 4 | Story Image | Image | Dr. Cindy in clinic |
| 5 | Vision Slider | Image Carousel | 5 clinic photos with ◀▶ and dots |
| 6 | Our Vision block | Text card | Heading + 3 paragraphs |

Layout: 2×2 bento grid
- Row 1: [Text: Our Story] [Image: clinic]
- Row 2: [Image Slider] [Text: Our Vision]

**Elementor**: Section → Heading + Divider + 2 rows of 2-column Inner Sections. Row 1: Text Editor + Image. Row 2: Image Carousel + Text Editor. **7 elements**.

---

#### Section 12 — Licensed
**Class**: `.licensed-section`
**Background**: White → very subtle gradient at bottom
**Container**: `licensed-container`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Section Heading | Heading (R1) | "Officially Licensed By" |
| 2 | Sub-heading | Text | "Government Authorities and Recognized Institutions - Indonesia" |
| 3 | License Card ×4 | Image Box (R9) | Each: gold-tinted logo + institution name |

Cards: PDGI, Kementerian Kesehatan, Kemenparekraf, Dinas Kesehatan Bali
Each card: light bg with subtle gradient, centered logo + centered text below

**Elementor**: Section → Heading + Text + 4-column inner section → 4× Image Box widgets. **6 elements**.

---

#### Section 13 — Footer
**Class**: `.footer`
**Background**: Dark navy (#1a2533)
**Container**: `footer-container`

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | Logo | Image | CSmile Bali logo (light version) |
| 2 | Tagline | Text | "Your trusted partner..." |
| 3 | Social heading | Text | "Follow us on:" |
| 4 | Social Icons ×2 | Icon links | Facebook, Instagram |
| 5 | Quick Links heading | Heading | "Quick Links" |
| 6 | Quick Links ×4 | Text links | Treatments, Consultation, Reviews, Contact |
| 7 | Contact heading | Heading | "Contact" |
| 8 | Phone | Icon + Link | 📞 +62 813 3786 031 |
| 9 | Email | Icon + Link | ✉ info@csmilebali.com |
| 10 | Address | Icon + Link | 📍 Jl. Bypass Ngurah Rai... |
| 11 | Divider | HR line | |
| 12 | Copyright | Text | "2025 CSmile Bali. All rights reserved." |

Layout: 3-column top (brand | links | contact) + full-width bottom bar

**Elementor**: Footer template → 3-column section + full-width bottom section. **~12 elements**.

---

#### Floating — WhatsApp Button
**Class**: `.lottie-animation.whp`
**Position**: Fixed, bottom-right

| # | Element | Type | Notes |
|---|---------|------|-------|
| 1 | WhatsApp Link | Button/Icon | Green circle with WhatsApp SVG icon, links to `wa.me/628133786031` with pre-filled message |

**Elementor**: Use "Starter Templates" floating button or WP plugin (e.g., "Click to Chat" for WhatsApp). Alternatively: custom HTML widget with fixed positioning. **1 element**.

---

## Task 3 — Screenshot ↔ HTML Matching & Animation Notes

### Screenshot Mapping

| Screenshot | Section | Match Quality | Notes |
|------------|---------|---------------|-------|
| ss1.png | S1: Hero | ✅ Perfect | Video BG shows dental implant 3D render. Glassmorphic navbar visible. |
| ss2.png | S2: Steps + S3: Treatments (top) | ✅ Good | Steps show icon circles (pink bg). Treatments 5-col grid with images. |
| ss3.png | S4: Services | ✅ Good | 2-column layout. Services badge (pill shape). Airport transfer photo. |
| ss4.png | S5: In-House Lab | ✅ Good | Marquee shows 3 side-by-side lab images. Bottom: 3 feature cards. |
| ss5.png | S6: Before/After | ✅ Good | Dark bg, slider with handle, 6 portrait thumbnails at bottom. |
| ss6.png | S7: Video Testimonials | ⚠️ Partial | Images appear blurry — likely video thumbnail loading issue. 3-slide carousel visible. |
| ss7.png | S8: Process | ✅ Perfect | Gradient background (teal→blue→salmon). 5 white cards, 2-2-1 layout. |
| ss8.png | S9: Reviews | ✅ Good | Review cards with stars, avatars, names, countries. Scrolling layout. |
| ss9part1 + ss9part2 | S10: Contact Form | ✅ Perfect | Dark bg, glassmorphic form, country code dropdown, smiling woman photo on right. |
| ss10.png | S11: Who We Are | ✅ Good | Bento 2×2 grid. Our Story + clinic photo top. Slider + Our Vision bottom. |
| ss11.png | S12: Licensed | ✅ Perfect | 4 gold logos with institution names. Subtle gradient background. |
| ss12.png | S13: Footer | ✅ Perfect | Dark navy, 3-col layout, social icons, copyright bar. |

### Animations Identified (from Webflow `data-w-id` attributes)

> [!IMPORTANT]
> These are Webflow Interactions (IX2) animations that won't carry over from the HTML. You'll need to recreate them in Elementor using **Entrance Animations** and **Motion Effects**.

| Animation | Section | Webflow Trigger | Elementor Equivalent |
|-----------|---------|-----------------|---------------------|
| Fade-in + slide up | Hero heading & description | On viewport enter | Entrance Animation: Fade In Up |
| Fade-in + slide up | Steps cards (×3) | Scroll into view | Entrance Animation: Fade In Up (staggered delay) |
| Fade-in | Treatments heading + grid | Scroll into view | Entrance Animation: Fade In |
| Fade-in + slide up | Services badge, heading, sub-heading | Scroll into view | Entrance Animation: Fade In Up (staggered) |
| Fade-in | Services right images | Scroll into view | Entrance Animation: Fade In |
| Fade-in + slide up | Lab heading, features | Scroll into view | Entrance Animation: Fade In Up |
| **Marquee scroll** | Lab image strip | CSS transform loop | Custom CSS: `@keyframes marquee` |
| **Hover bar animation** | Lab feature cards | Hover → width 0%→100% | Custom CSS: `.premium-material-div` on hover |
| Fade-in | Before/After content | Scroll into view | Entrance Animation: Fade In |
| **Tab switching** | Before/After thumbnails | Click → show/hide slider | Use Elementor Tabs or custom JS |
| Fade-in | Who We Are blocks | Scroll into view | Entrance Animation: Fade In |
| **Image slider** | Who We Are vision | Autoplay/manual | Elementor Image Carousel widget |
| **Swiper carousel** | Video testimonials | Drag/swipe | Plugin or custom Swiper init |
| Navbar animation | Navbar | Scroll → compact | Elementor sticky header shrink effect |

### Key Observations from Screenshots vs HTML

> [!NOTE]
> The HTML alone won't render correctly because:
> 1. **CSS is external** — loaded from `csmilebali.webflow.shared.*.css` on Webflow CDN
> 2. **Webflow Interactions (IX2)** — JavaScript-driven animations need Webflow runtime
> 3. **Before/After slider** — Uses both Flowbase Boosters plugin AND Udesly BeerSlider fallback
> 4. **Swiper.js** — Loaded externally for the video carousel
> 5. **Custom form logic** — Country code dropdown, UTM parameter handling, GTM/FB Pixel events

### Recommended WordPress Plugins for Feature Parity

| Feature | Recommended Plugin |
|---------|-------------------|
| Before/After Slider | **TwentyTwenty** or **Before After Image Slider** |
| Video Carousel | **Elementor Pro** Slides widget or **Unlimited Elements** |
| Testimonial Carousel | **Elementor Pro** Testimonial Carousel |
| Marquee/Infinite Scroll | **Unlimited Elements** or custom CSS |
| WhatsApp Button | **Click to Chat** or **Social Chat** |
| Contact Form | **WPForms** or **Elementor Pro Form** |
| Sticky Header | **Elementor Pro** sticky header feature |
| UTM Tracking | **MonsterInsights** or custom JS in header |

---

> [!TIP]
> **Next Steps**: When you're ready, provide the screenshots or confirm the sections and I'll help you with:
> - Task 4+: Elementor section-by-section build instructions
> - Exact spacing/padding values
> - Color/gradient CSS values for custom styling
> - WordPress theme recommendations
