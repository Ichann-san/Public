@extends('adminlte::master')

@section('title', 'Beranda')
@section('classes_body', 'welcome-page')

@section('body')
    <header class="welcome-nav">
        <a class="portal-brand" href="{{ route('welcome') }}">
            <img src="{{ asset('images/its-mark.svg') }}" alt="ITS">
            <span>Portal <strong>Akademik</strong></span>
        </a>
        <span class="text-body-secondary small">Pemrograman Berbasis Kerangka Kerja</span>
    </header>
    <main class="welcome-main">
        <h1>Urusan akademik,<br><span>lebih teratur.</span></h1>
        <p>Kelola data mahasiswa, dosen, dan tugas dalam satu tempat. Masuk dengan akun Anda untuk mengakses layanan sesuai peran.</p>
        <div class="welcome-actions">
            @auth
                <a href="{{ route('dashboard') }}" class="btn btn-primary">Buka Dashboard <i class="bi bi-arrow-right ms-2" aria-hidden="true"></i></a>
            @else
                <a href="{{ route('login') }}" class="btn btn-primary">Masuk ke Portal <i class="bi bi-arrow-right ms-2" aria-hidden="true"></i></a>
                <a href="{{ route('register') }}" class="btn btn-outline-secondary">Daftar Akun</a>
            @endauth
        </div>
        <div class="welcome-details">
            <section><h2>Data akademik</h2><p>Cari mahasiswa dan dosen berdasarkan nama atau departemen.</p></section>
            <section><h2>Tugas &amp; tenggat</h2><p>Lihat tugas aktif dan pantau tenggat yang paling dekat.</p></section>
            <section><h2>Akses sesuai peran</h2><p>Ruang kerja untuk admin, staf, dan mahasiswa sesuai kebutuhan.</p></section>
        </div>
    </main>
    <footer class="welcome-footer portal-footer">
        <span>PBKK &middot; Institut Teknologi Sepuluh Nopember</span>
        <span>Maulana &middot; 5025241001 &middot; Tugas 5</span>
    </footer>
@stop
