document.addEventListener('DOMContentLoaded', () => {

    const navLinks = [
        { name: 'Home', href: '#home-section' },
        { name: 'Courses', href: '#course-section' },
        { name: 'Dashboard', href: '#' },
        { name: 'Forum', href: '#' }
    ];

    const courses = [
        {
            title: "HTML Front end",
            desc: "Create the frame for web programming using HTML as the base",
            img: "https://placehold.co/600x400/8b5cf6/ffffff?text=HTML",
            badgeClasses: "bg-violet-100 text-violet-700 hover:bg-violet-200",
            link: "../html/course/html.html"
        },
        {
            title: "Javascript",
            desc: "Utilize the javascript functionality to load logical function into the design of the web",
            img: "https://placehold.co/600x400/facc15/000000?text=JavaScript",
            badgeClasses: "bg-yellow-100 text-yellow-700 hover:bg-yellow-200",
            link: "../html/course/javascript.html"
        },
        {
            title: "CSS layout",
            desc: "interactiovely customize the web design using CSS on your own",
            img: "https://placehold.co/600x400/22c55e/ffffff?text=CSS",
            badgeClasses: "bg-green-100 text-green-700 hover:bg-green-200",
            link: "../html/course/css.html"
        },
        {
            title: "Competitive Programming",
            desc: "Master algorithms and data structures to excel in programming contests.",
            img: "https://placehold.co/600x400/636f1/ffffff?text=Algorithms",
            badgeClasses: "bg-indigo-100 text-indigo-700 hover:bg-indigo-200",
            link: "../html/course/cp.html"
        },
        {
            title: "Intro to Quantum Computing",
            desc: "Explore the fascinating world of quantum mechanics and its computational power.",
            img: "https://placehold.co/600x400/ec4899/ffffff?text=Quantum",
            badgeClasses: "bg-pink-100 text-pink-700 hover:bg-pink-200",
            link: "../html/course/quantum.html"
        },
        {
            title: "UI/UX Design Fundamentals",
            desc: "Create beautiful and intuitive user interfaces that users will love.",
            img: "https://placehold.co/600x400/f97316/ffffff?text=UI/UX",
            badgeClasses: "bg-orange-100 text-orange-700 hover:bg-orange-200",
            link: "../html/course/uiux.html"
        },
        {
            title: "Data Science with Python",
            desc: "Analyze data, create visualizations, and build predictive models.",
            img: "https://placehold.co/600x400/0ea5e9/ffffff?text=Data",
            badgeClasses: "bg-sky-100 text-sky-700 hover:bg-sky-200",
            link: "../html/course/datascience.html"
        }
    ];

    const desktopNavContainer = document.getElementById('desktop-nav-links');
    const mobileNavContainer = document.getElementById('mobile-nav-links');
    const courseCarousel = document.getElementById('course-carousel');
    const themeToggleButton = document.getElementById('theme-toggle');
    const darkIcon = document.getElementById('theme-toggle-dark-icon');
    const lightIcon = document.getElementById('theme-toggle-light-icon');

    function renderNavLinks() {
        if (!desktopNavContainer || !mobileNavContainer) return;

        desktopNavContainer.innerHTML = '';
        mobileNavContainer.innerHTML = '';

        navLinks.forEach(link => {
            desktopNavContainer.innerHTML += `<a href="${link.href}" class="text-gray-600 dark:text-gray-300 hover:text-indigo-600 dark:hover:text-indigo-400 transition-colors">${link.name}</a>`;
            mobileNavContainer.innerHTML += `<a href="${link.href}" class="text-gray-700 dark:text-gray-300 hover:text-indigo-600 dark:hover:text-indigo-400">${link.name}</a>`;
        });
        mobileNavContainer.innerHTML += `<button class="w-full mt-6 bg-indigo-600 text-white px-4 py-2 rounded-lg hover:bg-indigo-700">Login</button>`;
    }

    function renderCourseCards() {
        if (!courseCarousel) return;
        
        courseCarousel.innerHTML = courses.map(course => `
            <div class="snap-center flex-shrink-0 w-80 bg-white dark:bg-gray-800 rounded-xl shadow-lg overflow-hidden transform hover:-translate-y-2 transition-transform duration-300">
                <img src="${course.img}" alt="${course.title} Course" class="w-full h-40 object-cover">
                <div class="p-6">
                    <h3 class="text-xl font-semibold mb-2 text-gray-900 dark:text-white">${course.title}</h3>
                    <p class="text-gray-600 dark:text-gray-400 text-sm mb-4">${course.desc}</p>
                    <a href="${course.link || '#'}" class="inline-block ${course.badgeClasses} font-medium px-4 py-2 rounded-full text-sm transition-colors">View Course</a>
                </div>
            </div>
        `).join('');
    }
    const applyTheme = () => {
        const isDarkMode = localStorage.getItem('theme') === 'dark' || 
                           (!('theme' in localStorage) && window.matchMedia('(prefers-color-scheme: dark)').matches);

        if (isDarkMode) {
            document.documentElement.classList.add('dark');
            darkIcon.classList.remove('hidden');
            lightIcon.classList.add('hidden');
        } else {
            document.documentElement.classList.remove('dark');
            darkIcon.classList.add('hidden');
            lightIcon.classList.remove('hidden');
        }
    };
    
    if(themeToggleButton) {
        themeToggleButton.addEventListener('click', () => {
            const isDark = document.documentElement.classList.toggle('dark');
            localStorage.setItem('theme', isDark ? 'dark' : 'light');
            applyTheme();
        });
    }

    applyTheme();
    renderNavLinks();
    renderCourseCards();

    const hamburgerBtn = document.getElementById('hamburger-btn');
    const mobileMenu = document.getElementById('mobile-menu');
    const closeMenuBtn = document.getElementById('close-menu-btn');

    if (hamburgerBtn && mobileMenu && closeMenuBtn) {
        hamburgerBtn.addEventListener('click', () => mobileMenu.classList.remove('translate-x-full'));
        closeMenuBtn.addEventListener('click', () => mobileMenu.classList.add('translate-x-full'));
        mobileMenu.addEventListener('click', (e) => {
            if (e.target === mobileMenu) mobileMenu.classList.add('translate-x-full');
        });
    }

    const prevBtn = document.getElementById('prev-btn');
    const nextBtn = document.getElementById('next-btn');

    if (courseCarousel && prevBtn && nextBtn) {
        const updateButtons = () => {
            if (courseCarousel.children.length === 0) return;
            prevBtn.disabled = courseCarousel.scrollLeft <= 0;
            nextBtn.disabled = courseCarousel.scrollLeft + courseCarousel.clientWidth >= courseCarousel.scrollWidth - 1;
        };

        const scrollCarousel = (direction) => {
            if (courseCarousel.children.length === 0) return;
            const scrollAmount = courseCarousel.firstElementChild.clientWidth + 24;
            courseCarousel.scrollBy({ left: scrollAmount * direction, behavior: 'smooth' });
        }

        prevBtn.addEventListener('click', () => scrollCarousel(-1));
        nextBtn.addEventListener('click', () => scrollCarousel(1));
        
        courseCarousel.addEventListener('scroll', updateButtons);
        new ResizeObserver(updateButtons).observe(courseCarousel);
        setTimeout(updateButtons, 100); 
    }
});

