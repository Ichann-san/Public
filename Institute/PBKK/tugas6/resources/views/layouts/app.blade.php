<!doctype html>
<html lang="id">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="csrf-token" content="{{ csrf_token() }}">
    <title>@yield('title', 'Workspace') | Chat Hub ITS</title>
    <script>try { document.documentElement.dataset.theme = localStorage.getItem('pbkk-theme') || 'light'; } catch (_) {}</script>
    <link rel="icon" href="{{ asset('images/its-mark.svg') }}" type="image/svg+xml">
    <link rel="stylesheet" href="{{ asset('vendor/bootstrap-icons/font/bootstrap-icons.min.css') }}">
    <link rel="stylesheet" href="{{ asset('css/workspace.css') }}">
    @livewireStyles
</head>
<body>
    <a class="skip-link" href="#main">Langsung ke percakapan</a>
    <header class="site-header">
        <a class="brand" href="{{ route('chat') }}"><img src="{{ asset('images/its-mark.svg') }}" alt="ITS"><span>Chat <strong>Hub</strong></span></a>
        <div class="header-actions">
            <span class="user-name">{{ auth()->user()->name }}</span>
            <a href="{{ route('profile.edit') }}" class="icon-button" aria-label="Profil"><i class="bi bi-person" aria-hidden="true"></i></a>
            <button type="button" class="icon-button" onclick="toggleTheme()" aria-label="Ganti tema terang atau gelap"><i class="bi bi-circle-half" aria-hidden="true"></i></button>
            <form method="POST" action="{{ route('logout') }}">@csrf<button class="icon-button" aria-label="Keluar"><i class="bi bi-box-arrow-right" aria-hidden="true"></i></button></form>
        </div>
    </header>
    @yield('content')
    <script src="{{ asset('js/workspace.js') }}" defer></script>
    @livewireScripts
</body>
</html>
