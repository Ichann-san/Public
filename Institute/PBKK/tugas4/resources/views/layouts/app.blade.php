<!doctype html>
<html lang="id">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="Profil akademik dan rancangan platform Agentic AI mahasiswa ITS.">
    <title>{{ $title }} | Profil Akademik ITS</title>
    @vite(['resources/css/app.css', 'resources/js/app.js'])
</head>
<body class="{{ $isDarkMode ? 'theme-dark bg-slate-950 text-slate-100' : 'bg-slate-50 text-slate-900' }}">
    <header class="site-header">
        <nav class="page-container nav-inner" aria-label="Navigasi utama">
            <a class="brand" href="{{ route('home') }}" aria-label="Profil ITS, kembali ke beranda">
                <span class="brand-mark" aria-hidden="true">ITS</span>
                <span>Profil <strong>Akademik</strong></span>
            </a>
            <div class="nav-links">
                <a href="{{ route('home') }}" @class(['active' => request()->routeIs('home', 'beranda')])>Beranda</a>
                <a href="{{ route('profile') }}" @class(['active' => request()->routeIs('profile')])>Profil</a>
                <a href="{{ route('ideas') }}" @class(['active' => request()->routeIs('ideas', 'ideas.store')])>Ide Agent</a>
            </div>
        </nav>
    </header>

    <main class="page-container page-main">
        @yield('content')
    </main>

    <footer class="site-footer">
        <div class="page-container footer-inner">
            <span>PBKK · Institut Teknologi Sepuluh Nopember</span>
            <span>Tugas 4 · Profil Akademik</span>
        </div>
    </footer>
</body>
</html>
