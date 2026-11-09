@extends('layouts.panel')

@section('title', 'Dashboard Admin')

@section('content_header')
    <div class="d-flex justify-content-between align-items-center">
        <div><h1 class="mb-0">Dashboard Akademik</h1><p class="page-description">Ringkasan mahasiswa, dosen, dan tugas dalam satu tampilan.</p></div>
        <span class="badge text-bg-primary">
            {{ ucfirst(auth()->user()->getRoleNames()->first()) }}
        </span>
    </div>
@stop

@section('content')
    @include('partials.flash')

    <p class="text-body-secondary">Selamat datang, <strong>{{ auth()->user()->name }}</strong>!</p>

    {{-- Widget statistik agregat --}}
    <div class="row">
        <div class="col-lg-3 col-6">
            <x-adminlte-small-box title="{{ $statistik['mahasiswa'] }}" text="Total Mahasiswa"
                icon="bi bi-mortarboard-fill" theme="primary"
                url="{{ route('admin.mahasiswa.index') }}" url-text="Lihat data" />
        </div>
        <div class="col-lg-3 col-6">
            <x-adminlte-small-box title="{{ $statistik['dosen'] }}" text="Total Dosen"
                icon="bi bi-briefcase-fill" theme="success"
                url="{{ route('admin.dosen.index') }}" url-text="Lihat data" />
        </div>
        <div class="col-lg-3 col-6">
            <x-adminlte-small-box title="{{ $statistik['tugas_aktif'] }}" text="Total Tugas Aktif"
                icon="bi bi-journal-check" theme="warning"
                url="{{ route('admin.tugas.index', ['status' => 'aktif']) }}" url-text="Lihat data" />
        </div>
        <div class="col-lg-3 col-6">
            <x-adminlte-small-box title="{{ $statistik['pengguna'] }}" text="Total Pengguna"
                icon="bi bi-people-fill" theme="danger"
                :url="auth()->user()->can('kelola-pengguna') ? route('admin.users.index') : null"
                url-text="Kelola pengguna" />
        </div>
    </div>

    @role('staf')
        <div class="alert alert-info">
            <i class="bi bi-info-circle me-1"></i>
            Anda login sebagai <strong>Staf</strong>: dapat melihat, menambah, dan mengedit data,
            tetapi tidak dapat menghapus data atau mengelola pengguna.
        </div>
    @endrole

    <div class="row">
        <div class="col-lg-6">
            <div class="card mb-4">
                <div class="card-header"><h3 class="card-title">Mahasiswa per Departemen</h3></div>
                <div class="card-body p-0 table-responsive">
                    <table class="table table-striped mb-0">
                        <thead>
                            <tr><th>Departemen</th><th class="text-end">Aktif</th><th class="text-end">Total</th></tr>
                        </thead>
                        <tbody>
                            @foreach ($mahasiswaPerDepartemen as $dept)
                                <tr>
                                    <td>
                                        <a href="{{ route('admin.mahasiswa.index', ['departemen_id' => $dept->id]) }}">
                                            {{ $dept->nama }}
                                        </a>
                                    </td>
                                    <td class="text-end">{{ $dept->mahasiswa_aktif_count }}</td>
                                    <td class="text-end">{{ $dept->mahasiswa_count }}</td>
                                </tr>
                            @endforeach
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
        <div class="col-lg-6">
            <div class="card mb-4">
                <div class="card-header"><h3 class="card-title">Tenggat Tugas Terdekat</h3></div>
                <div class="card-body p-0">
                    <ul class="list-group list-group-flush">
                        @forelse ($tugasTerdekat as $item)
                            <li class="list-group-item d-flex justify-content-between align-items-start">
                                <div>
                                    <div class="fw-semibold">{{ $item->judul }}</div>
                                    <small class="text-body-secondary">{{ $item->dosen->nama }} &middot; {{ $item->departemen->kode }}</small>
                                </div>
                                <span class="badge text-bg-warning">{{ $item->deadline->diffForHumans() }}</span>
                            </li>
                        @empty
                            <li class="list-group-item text-body-secondary">Tidak ada tugas aktif.</li>
                        @endforelse
                    </ul>
                </div>
            </div>
        </div>
    </div>
@stop
