/**
 * CSmile Bali — Local Preview Scripts
 * Replaces Webflow IX2 interactions, Flowbase Boosters, and Swiper init.
 */

document.addEventListener('DOMContentLoaded', function () {

  /* ============================================================
     1. MARQUEE — infinite horizontal scroll for lab images
     ============================================================ */
  (function initMarquee() {
    const marquees = document.querySelectorAll('.made-marquee');
    if (!marquees.length) return;

    // CSS animation approach
    const style = document.createElement('style');
    style.textContent = `
      @keyframes marqueeScroll {
        0%   { transform: translateX(0); }
        100% { transform: translateX(-100%); }
      }
      .made-marquee {
        animation: marqueeScroll 20s linear infinite;
      }
      .made-main-marquee-block:hover .made-marquee {
        animation-play-state: paused;
      }
    `;
    document.head.appendChild(style);

    // Reset any inline transforms from Webflow
    marquees.forEach(m => {
      m.style.transform = '';
      m.style.willChange = '';
    });
  })();

  /* ============================================================
     2. SCROLL ANIMATIONS — fade-in-up on viewport enter
     ============================================================ */
  (function initScrollAnimations() {
    const animatedEls = document.querySelectorAll('[data-w-id]');
    if (!animatedEls.length) return;

    // Reset all to invisible first
    const targets = [];
    animatedEls.forEach(el => {
      // Only animate elements that had opacity/transform styles
      if (el.style.opacity !== undefined) {
        el.style.opacity = '0';
        el.style.transform = 'translateY(30px)';
        el.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        targets.push(el);
      }
    });

    const observer = new IntersectionObserver((entries) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          entry.target.style.opacity = '1';
          entry.target.style.transform = 'translateY(0)';
          observer.unobserve(entry.target);
        }
      });
    }, { threshold: 0.15, rootMargin: '0px 0px -50px 0px' });

    targets.forEach(el => observer.observe(el));
  })();

  /* ============================================================
     3. BEFORE/AFTER SLIDERS — Flowbase Boosters replacement
     ============================================================ */
  (function initBeforeAfterSliders() {
    const sliders = document.querySelectorAll('[fb-before-after="true"]');
    sliders.forEach(slider => {
      const input = slider.querySelector('[fb-before-after-input]');
      const afterImg = slider.querySelector('[fb-before-after-side="after"]');
      const handle = slider.querySelector('[fb-before-after-handle]');
      const line = slider.querySelector('[fb-before-after-line]');

      if (!input || !afterImg) return;

      // Set initial value
      const startVal = slider.getAttribute('fb-before-after-start') || '50';
      input.value = startVal;

      function updateSlider(val) {
        const pct = val + '%';
        afterImg.style.clipPath = `inset(0 0 0 ${pct})`;
        if (handle) {
          handle.style.left = pct;
        }
        if (line) {
          line.style.left = pct;
        }
        slider.style.setProperty('--fb-thumb-position', pct);
      }

      updateSlider(parseInt(startVal));

      input.addEventListener('input', function () {
        updateSlider(parseInt(this.value));
      });

      // Make input cover full area and be interactive
      input.style.width = '100%';
      input.style.height = '100%';
      input.style.cursor = 'pointer';
    });
  })();

  /* ============================================================
     4. BEFORE/AFTER TAB SWITCHING (desktop)
     ============================================================ */
  (function initBeforeAfterTabs() {
    // Desktop: tabs inside .tabs.w-tabs
    const tabLinks = document.querySelectorAll('.tabs-menu .tablink');
    const tabPanes = document.querySelectorAll('.tabs-content .w-tab-pane');

    tabLinks.forEach((link, i) => {
      link.addEventListener('click', function (e) {
        e.preventDefault();
        // Remove active from all
        tabLinks.forEach(l => l.classList.remove('w--current'));
        tabPanes.forEach(p => {
          p.classList.remove('w--tab-active');
          p.style.display = 'none';
        });
        // Activate clicked
        this.classList.add('w--current');
        if (tabPanes[i]) {
          tabPanes[i].classList.add('w--tab-active');
          tabPanes[i].style.display = 'block';
        }
      });
    });

    // Phone mode: thumbnail buttons switching .bas-wrapper.absolute
    const phoneThumbBtns = document.querySelectorAll('.before-after-button-main-block .tab_nav_block');
    const phoneSliders = document.querySelectorAll('.div-block-12 > .before-after-phone-main-block .bas-wrapper.absolute, .div-block-12 > .bas-wrapper.absolute');

    // Actually get all absolute sliders inside div-block-12
    const allAbsSliders = document.querySelectorAll('.div-block-12 .bas-wrapper.absolute');

    phoneThumbBtns.forEach((btn, i) => {
      btn.addEventListener('click', function (e) {
        e.preventDefault();
        // Reset all
        phoneThumbBtns.forEach(b => {
          b.classList.remove('tab1');
          b.style.borderColor = '#868686';
          b.style.width = '50px';
          b.style.height = '60px';
        });
        allAbsSliders.forEach(s => s.classList.add('hide'));

        // Activate
        this.classList.add('tab1');
        this.style.borderColor = '#fc5f2b';
        this.style.width = '80px';
        this.style.height = '85px';
        if (allAbsSliders[i]) {
          allAbsSliders[i].classList.remove('hide');
        }
      });
    });
  })();

  /* ============================================================
     5. PREMIUM MATERIAL HOVER — animate the bar width
     ============================================================ */
  (function initPremiumHover() {
    const hoverBlocks = document.querySelectorAll('.premium-material-hover-block');
    hoverBlocks.forEach(block => {
      const bar = block.querySelector('.premium-material-div');
      if (!bar) return;
      bar.style.transition = 'width 0.4s ease';
      block.addEventListener('mouseenter', () => { bar.style.width = '100%'; });
      block.addEventListener('mouseleave', () => { bar.style.width = '0%'; });
    });
  })();

  /* ============================================================
     6. SWIPER CAROUSEL — video testimonials
     ============================================================ */
  (function initSwiperCarousel() {
    if (typeof Swiper === 'undefined') return;

    const swiperEl = document.querySelector('.swiper-container');
    if (!swiperEl) return;

    new Swiper('.swiper-container', {
      slidesPerView: 1.4,
      centeredSlides: true,
      spaceBetween: 20,
      loop: true,
      grabCursor: true,
      navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
      },
      breakpoints: {
        640: { slidesPerView: 2 },
        992: { slidesPerView: 3, spaceBetween: 30 },
      },
      on: {
        slideChange: function () {
          // Scale center slide
          this.slides.forEach(slide => {
            slide.style.transform = 'scale(0.85)';
            slide.style.opacity = '0.6';
          });
          const activeSlide = this.slides[this.activeIndex];
          if (activeSlide) {
            activeSlide.style.transform = 'scale(1)';
            activeSlide.style.opacity = '1';
          }
        }
      }
    });
  })();

  /* ============================================================
     7. WEBFLOW SLIDER — Who We Are image slider
     ============================================================ */
  (function initWfSlider() {
    const sliders = document.querySelectorAll('.w-slider');
    sliders.forEach(slider => {
      const mask = slider.querySelector('.w-slider-mask');
      const slides = slider.querySelectorAll('.w-slide');
      const leftArrow = slider.querySelector('.w-slider-arrow-left');
      const rightArrow = slider.querySelector('.w-slider-arrow-right');
      const nav = slider.querySelector('.w-slider-nav');

      if (!mask || slides.length === 0) return;

      let current = 0;
      const total = slides.length;

      // Create dots
      if (nav) {
        nav.innerHTML = '';
        slides.forEach((_, i) => {
          const dot = document.createElement('div');
          dot.className = 'w-slider-dot' + (i === 0 ? ' w-active' : '');
          dot.setAttribute('role', 'button');
          dot.addEventListener('click', () => goTo(i));
          nav.appendChild(dot);
        });
      }

      function goTo(index) {
        current = ((index % total) + total) % total;
        mask.style.transition = 'transform 0.5s ease';
        mask.style.transform = `translateX(-${current * 100}%)`;

        // Update dots
        if (nav) {
          const dots = nav.querySelectorAll('.w-slider-dot');
          dots.forEach((d, i) => d.classList.toggle('w-active', i === current));
        }
      }

      if (leftArrow) leftArrow.addEventListener('click', () => goTo(current - 1));
      if (rightArrow) rightArrow.addEventListener('click', () => goTo(current + 1));

      // Set up slides side-by-side
      mask.style.display = 'flex';
      mask.style.whiteSpace = 'nowrap';
      slides.forEach(s => {
        s.style.flex = '0 0 100%';
        s.style.width = '100%';
      });

      // Autoplay every 4 seconds
      setInterval(() => goTo(current + 1), 4000);
    });
  })();

  /* ============================================================
     8. TESTIMONIAL MARQUEE — auto-scroll review cards
     ============================================================ */
  (function initTestimonialMarquee() {
    const rows = document.querySelectorAll('.testimonial-first-marquee-block');
    if (!rows.length) return;

    const style = document.createElement('style');
    style.textContent = `
      @keyframes testimonialScrollLeft {
        0%   { transform: translateX(0); }
        100% { transform: translateX(-50%); }
      }
      @keyframes testimonialScrollRight {
        0%   { transform: translateX(-50%); }
        100% { transform: translateX(0); }
      }
      .testimonial-first-marquee-block {
        animation: testimonialScrollLeft 40s linear infinite;
      }
      .testimonial-first-marquee-main-block.second-testimonials .testimonial-first-marquee-block {
        animation: testimonialScrollRight 40s linear infinite;
      }
      .testimonials-main-content-section:hover .testimonial-first-marquee-block {
        animation-play-state: paused;
      }
    `;
    document.head.appendChild(style);
  })();

  /* ============================================================
     9. NAVBAR — glassmorphic scroll behavior
     ============================================================ */
  (function initNavbar() {
    const navbar = document.querySelector('.navbar');
    if (!navbar) return;

    // Ensure navbar is always on top
    navbar.style.zIndex = '1000';
    navbar.style.position = 'fixed';
    navbar.style.top = '0';
    navbar.style.left = '0';
    navbar.style.right = '0';

    // Mobile menu toggle
    const menuBtn = navbar.querySelector('.navbar2_menu-button');
    const menu = navbar.querySelector('.navbar2_menu');
    const overlay = navbar.querySelector('.w-nav-overlay');

    if (menuBtn && menu) {
      menuBtn.addEventListener('click', function () {
        const isOpen = this.classList.toggle('w--open');
        if (isOpen) {
          menu.style.display = 'flex';
          menu.style.flexDirection = 'column';
          if (overlay) overlay.style.display = 'block';
        } else {
          menu.style.display = '';
          if (overlay) overlay.style.display = '';
        }
      });
    }
  })();

  /* ============================================================
     10. SMOOTH SCROLL — for anchor links
     ============================================================ */
  (function initSmoothScroll() {
    document.querySelectorAll('a[href^="#"]').forEach(link => {
      link.addEventListener('click', function (e) {
        const hash = this.getAttribute('href');
        if (hash === '#') return;
        const target = document.querySelector(hash);
        if (target) {
          e.preventDefault();
          target.scrollIntoView({ behavior: 'smooth', block: 'start' });
        }
      });
    });
  })();

  /* ============================================================
     11. CONTACT FORM — country code dropdown & validation
     ============================================================ */
  (function initContactForm() {
    const phoneInput = document.querySelector('#Phone-Number');
    if (phoneInput) {
      phoneInput.addEventListener('input', function () {
        this.value = this.value.replace(/[^0-9]/g, '');
      });
    }

    // Treatment dropdown styling
    const selectField = document.querySelector('.select-field');
    if (selectField) {
      selectField.style.fontFamily = 'Hanken Grotesk, sans-serif';
    }
  })();

  /* ============================================================
     12. VIDEO BACKGROUND — ensure autoplay works
     ============================================================ */
  (function initVideoBackground() {
    const videos = document.querySelectorAll('.w-background-video video');
    videos.forEach(video => {
      video.muted = true;
      video.setAttribute('playsinline', '');
      video.play().catch(() => {});
    });
  })();

});
