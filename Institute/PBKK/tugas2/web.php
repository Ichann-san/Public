<?php

use Illuminate\Http\Response;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Tampilan bersama
|--------------------------------------------------------------------------
| Satu helper dipakai agar tugas tetap sederhana dan tidak memerlukan
| controller atau file Blade tambahan.
*/
if (! function_exists('halaman')) {
    function halaman(string $judul, string $isi, int $status = 200): Response
    {
        $homeUrl = route('home');
        $profileUrl = route('dashboard.mahasiswa', ['nrp' => '5025241001']);
        $agentUrl = route('dashboard.agent');
        $ipkUrl = route('dashboard.hitung-ipk', ['ip1' => '3.75', 'ip2' => '3.90']);

        $html = <<<HTML
<!doctype html>
<html lang="id">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>{$judul} | Profil Akademis ITS</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700;800&display=swap" rel="stylesheet">
    <style>
        :root { --primary: #4f46e5; --primary-dark: #4338ca; --surface: #f9fafb; }
        body { min-height: 100vh; display: flex; flex-direction: column; font-family: Inter, sans-serif; background: var(--surface); color: #1f2937; }
        .navbar { background: #fff; box-shadow: 0 1px 3px rgb(0 0 0 / .08); }
        .navbar-brand { color: var(--primary); font-weight: 800; }
        .nav-link { color: #4b5563; font-weight: 500; }
        .nav-link:hover { color: var(--primary); }
        main { flex: 1; }
        .hero { padding: 5rem 0 3rem; }
        .hero h1 { font-weight: 800; font-size: clamp(2.25rem, 7vw, 4rem); }
        .gradient { background: linear-gradient(90deg, var(--primary), #8b5cf6); -webkit-background-clip: text; color: transparent; }
        .card { border: 0; border-radius: 1rem; box-shadow: 0 10px 25px rgb(0 0 0 / .08); transition: transform .15s ease; }
        .card:hover { transform: translateY(-4px); }
        .btn-primary { background: var(--primary); border-color: var(--primary); }
        .btn-primary:hover { background: var(--primary-dark); border-color: var(--primary-dark); }
        .badge-soft { display: inline-block; padding: .45rem .75rem; border-radius: 999px; background: #e0e7ff; color: #4338ca; font-weight: 600; }
        footer { margin-top: 4rem; padding: 1.75rem 0; color: #9ca3af; background: #1f2937; }
    </style>
</head>
<body>
    <nav class="navbar navbar-expand-lg sticky-top">
        <div class="container py-2">
            <a class="navbar-brand" href="{$homeUrl}">🎓 Profil ITS</a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#menu" aria-label="Buka navigasi">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="menu">
                <div class="navbar-nav ms-auto gap-lg-3">
                    <a class="nav-link" href="{$homeUrl}">Home</a>
                    <a class="nav-link" href="{$profileUrl}">Profil</a>
                    <a class="nav-link" href="{$agentUrl}">Agent AI</a>
                    <a class="nav-link" href="{$ipkUrl}">Kalkulator IPK</a>
                </div>
            </div>
        </div>
    </nav>
    <main>{$isi}</main>
    <footer><div class="container text-center">PBKK · Institut Teknologi Sepuluh Nopember</div></footer>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
HTML;

        return response($html, $status);
    }
}

// Rute 1: halaman utama.
Route::get('/', function () {
    $profileUrl = route('dashboard.mahasiswa', ['nrp' => '5025241001']);
    $agentUrl = route('dashboard.agent', ['tema' => 'Education']);

    $isi = <<<HTML
<section class="hero text-center">
    <div class="container">
        <span class="badge-soft mb-3">Institut Teknologi Sepuluh Nopember</span>
        <h1>Selamat datang, <span class="gradient">Arek ITS!</span></h1>
        <p class="lead text-secondary mx-auto mt-3" style="max-width: 680px">
            Ini adalah sandbox Laravel sederhana untuk mengenal profil mahasiswa,
            riwayat studi, dan proyeksi platform Agentic AI.
        </p>
        <div class="d-flex gap-2 justify-content-center mt-4 flex-wrap">
            <a class="btn btn-primary px-4" href="{$profileUrl}">Lihat Profil</a>
            <a class="btn btn-outline-primary px-4" href="{$agentUrl}">Lihat Ide AI</a>
        </div>
    </div>
</section>
<section class="container pb-5">
    <div class="row g-4">
        <div class="col-md-4"><div class="card h-100 p-4"><h2 class="h5">Mahasiswa Informatika</h2><p class="text-secondary mb-0">Aktif belajar pengembangan perangkat lunak, cloud, dan kecerdasan buatan.</p></div></div>
        <div class="col-md-4"><div class="card h-100 p-4"><h2 class="h5">Target Semester</h2><p class="text-secondary mb-0">Membangun proyek yang sederhana, berguna, terukur, dan mudah dipahami.</p></div></div>
        <div class="col-md-4"><div class="card h-100 p-4"><h2 class="h5">Minat Utama</h2><p class="text-secondary mb-0">Agentic AI, rekayasa perangkat lunak, serta sistem cloud dan jaringan.</p></div></div>
    </div>
</section>
HTML;

    return halaman('Home', $isi);
})->name('home');

/* Tantangan 3: seluruh rute profil akademis berada di prefix /dashboard. */
Route::prefix('dashboard')->name('dashboard.')->group(function () {
    // Rute 2 + Tantangan 1: NRP wajib berupa tepat 10 digit.
    Route::get('/mahasiswa/{nrp}', function (string $nrp) {
        $nrpAman = e($nrp);

        $isi = <<<HTML
<section class="container py-5">
    <div class="card mx-auto p-4 p-md-5" style="max-width: 760px">
        <div class="d-flex align-items-center gap-3 mb-4">
            <div class="rounded-circle bg-primary text-white d-grid place-items-center fs-3 fw-bold" style="width:72px;height:72px">M</div>
            <div><span class="badge-soft">Mahasiswa Aktif</span><h1 class="h2 mt-2 mb-0">Maulana</h1></div>
        </div>
        <div class="row g-4">
            <div class="col-sm-6"><small class="text-secondary">NRP</small><div class="fw-semibold">{$nrpAman}</div></div>
            <div class="col-sm-6"><small class="text-secondary">Perguruan Tinggi</small><div class="fw-semibold">Institut Teknologi Sepuluh Nopember</div></div>
            <div class="col-sm-6"><small class="text-secondary">Program Studi</small><div class="fw-semibold">Teknik Informatika</div></div>
            <div class="col-sm-6"><small class="text-secondary">Status</small><div class="fw-semibold">Aktif</div></div>
        </div>
        <hr class="my-4">
        <h2 class="h5">Riwayat dan Minat Studi</h2>
        <p class="text-secondary mb-0">Mempelajari pemrograman web, algoritma, jaringan komputer, cloud computing, dan kecerdasan buatan.</p>
    </div>
</section>
HTML;

        return halaman('Detail Profil', $isi);
    })->where('nrp', '[0-9]{10}')->name('mahasiswa');

    // Rute 3: tema bersifat opsional dan memiliki nilai default.
    Route::get('/agent/{tema?}', function (?string $tema = null) {
        $tema = $tema ?: 'General Assistant Agent';
        $temaAman = e(str_replace('-', ' ', $tema));

        $isi = <<<HTML
<section class="container py-5">
    <div class="card mx-auto p-4 p-md-5" style="max-width: 760px">
        <span class="badge-soft align-self-start mb-3">Proyeksi Akhir Semester</span>
        <h1 class="gradient fw-bold">{$temaAman}</h1>
        <p class="lead text-secondary mt-3">Platform Agentic AI yang membantu pengguna memahami tujuan, menyusun langkah kerja, mencari informasi relevan, dan mengevaluasi hasil secara mandiri.</p>
        <h2 class="h5 mt-3">Fitur inti</h2>
        <ul class="text-secondary mb-0"><li>Perencanaan tugas otomatis</li><li>Rekomendasi berdasarkan konteks</li><li>Ringkasan progres yang mudah dipahami</li></ul>
    </div>
</section>
HTML;

        return halaman('Ide Agentic AI', $isi);
    })->name('agent');

    // Tantangan 2: menjumlahkan dan menghitung rata-rata IP dua semester.
    Route::get('/hitung-ipk/{ip1}/{ip2}', function (string $ip1, string $ip2) {
        $semester1 = (float) $ip1;
        $semester2 = (float) $ip2;

        abort_if($semester1 < 0 || $semester1 > 4 || $semester2 < 0 || $semester2 > 4, 422, 'Nilai IP harus berada di antara 0.00 dan 4.00.');

        $jumlah = $semester1 + $semester2;
        $rataRata = $jumlah / 2;

        $isi = sprintf(<<<'HTML'
<section class="container py-5">
    <div class="card mx-auto p-4 p-md-5 text-center" style="max-width: 680px">
        <span class="badge-soft mx-auto mb-3">Kalkulator Akademis</span>
        <h1 class="h2 fw-bold">Hasil Perhitungan IPK</h1>
        <div class="row g-3 my-3">
            <div class="col-6"><div class="bg-light rounded-3 p-3"><small>Semester 1</small><div class="fs-3 fw-bold">%.2f</div></div></div>
            <div class="col-6"><div class="bg-light rounded-3 p-3"><small>Semester 2</small><div class="fs-3 fw-bold">%.2f</div></div></div>
        </div>
        <p class="text-secondary mb-1">Jumlah IP: <strong>%.2f</strong></p>
        <p class="fs-5 mb-0">Rata-rata IPK: <strong class="text-primary">%.2f</strong></p>
    </div>
</section>
HTML, $semester1, $semester2, $jumlah, $rataRata);

        return halaman('Kalkulator IPK', $isi);
    })->where(['ip1' => '[0-4](?:\\.[0-9]{1,2})?', 'ip2' => '[0-4](?:\\.[0-9]{1,2})?'])->name('hitung-ipk');
});

// Tantangan 3: halaman rapi untuk semua URL yang tidak dikenali.
Route::fallback(function () {
    $homeUrl = route('home');
    $isi = <<<HTML
<section class="container py-5 text-center">
    <div class="card mx-auto p-5" style="max-width: 620px">
        <div class="display-1 fw-bold gradient">404</div>
        <h1 class="h3">Halaman tidak ditemukan</h1>
        <p class="text-secondary">Alamat yang Anda buka tidak tersedia atau parameter rutenya tidak valid.</p>
        <a class="btn btn-primary mx-auto" href="{$homeUrl}">Kembali ke Home</a>
    </div>
</section>
HTML;

    return halaman('404', $isi, 404);
})->name('fallback');
