@extends('layouts.app')

@section('content')
    @if ($userName !== '')
        <x-status-banner class="welcome-banner">Selamat datang, <strong>{{ $userName }}</strong>! Semoga harimu produktif.</x-status-banner>
    @endif

    <section class="hero text-center">
        <span class="eyebrow">Institut Teknologi Sepuluh Nopember</span>
        <h1>Selamat datang, <span class="gradient-text">Arek ITS!</span></h1>
        <p class="hero-copy">Ruang kecil untuk mengenal profil akademik, perjalanan belajar, dan rancangan platform Agentic AI kelompok.</p>
        <div class="actions">
            <a class="button button-primary" href="{{ route('profile') }}">Lihat Profil <span aria-hidden="true">↗</span></a>
            <a class="button button-outline" href="{{ route('ideas') }}">Jelajahi Ide AI</a>
        </div>
    </section>

    <section class="section-block" aria-labelledby="overview-title">
        <div class="section-heading">
            <div>
                <span class="section-kicker">Sekilas tentang saya</span>
                <h2 id="overview-title">Belajar, membangun, berkembang.</h2>
            </div>
            <p>Hal yang sedang ditekuni selama perjalanan akademik di ITS.</p>
        </div>
        <div class="feature-grid">
            <article class="feature-card">
                <span class="feature-icon" aria-hidden="true">01</span>
                <h3>Mahasiswa Informatika</h3>
                <p>Aktif mempelajari pengembangan perangkat lunak, cloud, dan kecerdasan buatan.</p>
            </article>
            <article class="feature-card">
                <span class="feature-icon" aria-hidden="true">02</span>
                <h3>Target Semester</h3>
                <p>Membangun proyek yang sederhana, berguna, terukur, dan mudah dipahami.</p>
            </article>
            <article class="feature-card">
                <span class="feature-icon" aria-hidden="true">03</span>
                <h3>Minat Utama</h3>
                <p>Agentic AI, rekayasa perangkat lunak, serta sistem cloud dan jaringan.</p>
            </article>
        </div>
    </section>
@endsection
