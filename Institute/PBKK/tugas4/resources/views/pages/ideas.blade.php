@extends('layouts.app')

@section('content')
    <section class="page-intro">
        <div class="intro-topline">
            <span class="eyebrow">Rancangan Agentic AI Kelompok</span>
            <a class="mode-link" href="{{ route('ideas', $isDarkMode ? [] : ['mode' => 'dark']) }}">
                {{ $isDarkMode ? '☀ Mode terang' : '☾ Mode gelap' }}
            </a>
        </div>
        <h1>Ide yang membantu belajar <span class="gradient-text">lebih terarah.</span></h1>
        <p>Konsep awal platform yang dapat dirancang dan dikembangkan bersama kelompok.</p>
    </section>

    <section class="idea-grid" aria-label="Rancangan platform">
        <article class="concept-card">
            <span class="eyebrow">Konsep Platform</span>
            <h2>StudyFlow <span class="gradient-text">Agent</span></h2>
            <p>Asisten belajar berbasis Agentic AI yang memahami tujuan mahasiswa, memecah target menjadi langkah kecil, lalu membantu meninjau progres belajar.</p>
            <div class="concept-flow" aria-label="Alur kerja platform">
                <div><span>01</span><strong>Tentukan tujuan</strong><small>Mahasiswa menuliskan target belajar.</small></div>
                <div><span>02</span><strong>Susun rencana</strong><small>Agent membuat urutan tugas yang realistis.</small></div>
                <div><span>03</span><strong>Evaluasi progres</strong><small>Agent merangkum hasil dan langkah berikutnya.</small></div>
            </div>
        </article>

        <aside class="idea-aside">
            <h2>Fitur inti</h2>
            <ul class="feature-list">
                <li><span>✓</span> Perencanaan tugas otomatis</li>
                <li><span>✓</span> Rekomendasi berdasarkan konteks</li>
                <li><span>✓</span> Ringkasan progres yang mudah dipahami</li>
            </ul>
            <p>Visualisasi ini adalah rancangan awal, belum berupa aplikasi AI yang aktif.</p>
        </aside>
    </section>

    <section class="form-section" aria-labelledby="idea-form-title">
        <div class="form-intro">
            <span class="section-kicker">Punya gagasan?</span>
            <h2 id="idea-form-title">Kirim ide risetmu.</h2>
            <p>Bagikan masukan untuk konsep Agentic AI. Formulir ini menampilkan konfirmasi; penyimpanan database belum digunakan pada tugas ini.</p>
        </div>
        <div class="form-panel">
            @if (session('status'))
                <x-status-banner tone="success" class="form-alert">{{ session('status') }}</x-status-banner>
            @endif

            <form action="{{ route('ideas.store') }}" method="POST">
                @csrf
                @if ($isDarkMode)
                    <input type="hidden" name="mode" value="dark">
                @endif
                <div class="field-row">
                    <div class="field">
                        <label for="name">Nama</label>
                        <input id="name" name="name" type="text" value="{{ old('name') }}" maxlength="80" required autocomplete="name" placeholder="Nama kamu">
                        @error('name') <span class="field-error">{{ $message }}</span> @enderror
                    </div>
                    <div class="field">
                        <label for="idea">Judul ide</label>
                        <input id="idea" name="idea" type="text" value="{{ old('idea') }}" maxlength="120" required placeholder="Contoh: Asisten belajar adaptif">
                        @error('idea') <span class="field-error">{{ $message }}</span> @enderror
                    </div>
                </div>
                <div class="field">
                    <label for="description">Deskripsi singkat</label>
                    <textarea id="description" name="description" rows="4" maxlength="1000" required placeholder="Ceritakan masalah yang ingin diselesaikan dan cara agent membantu.">{{ old('description') }}</textarea>
                    @error('description') <span class="field-error">{{ $message }}</span> @enderror
                </div>
                <button class="button button-primary" type="submit">Kirim Ide <span aria-hidden="true">→</span></button>
            </form>
        </div>
    </section>
@endsection
