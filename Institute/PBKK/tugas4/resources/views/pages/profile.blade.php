@extends('layouts.app')

@section('content')
    <section class="page-intro">
        <span class="eyebrow">Profil Mahasiswa</span>
        <h1>Kenali mahasiswa di balik <span class="gradient-text">proyek ini.</span></h1>
        <p>Identitas akademik dan bidang yang sedang dipelajari.</p>
    </section>

    <section class="profile-panel" aria-label="Data mahasiswa">
        <div class="profile-heading">
            <div class="avatar" aria-hidden="true">M</div>
            <div>
                <span class="eyebrow">{{ $student['status'] }}</span>
                <h2>{{ $student['name'] }}</h2>
                <p>Mahasiswa Teknik Informatika · ITS</p>
            </div>
        </div>

        <div class="info-grid">
            <x-info-card label="NRP">{{ $student['nrp'] }}</x-info-card>
            <x-info-card label="Perguruan Tinggi">{{ $student['university'] }}</x-info-card>
            <x-info-card label="Program Studi">{{ $student['program'] }}</x-info-card>
            <x-info-card label="Status Akademik"><span class="status-dot"></span>{{ $student['status'] }}</x-info-card>
        </div>

        <div class="profile-note">
            <h3>Riwayat dan minat studi</h3>
            <p>Mempelajari pemrograman web, algoritma, jaringan komputer, cloud computing, dan kecerdasan buatan. Tugas ini menjadi latihan membangun antarmuka Laravel yang rapi dan reusable.</p>
        </div>
    </section>
@endsection
