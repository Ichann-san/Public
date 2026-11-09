@extends('adminlte::page')

@section('title', 'Beranda')

@section('content_header')
    <h1>Beranda</h1>
@stop

@section('content')
    <div class="callout callout-info mb-4">
        <h5>Halo, {{ auth()->user()->name }}!</h5>
        <p class="mb-0">
            Anda login sebagai pengguna biasa. Halaman ini adalah beranda publik portal akademik.
            Panel admin hanya dapat diakses oleh peran <strong>Admin</strong> dan <strong>Staf</strong>.
        </p>
    </div>

    <div class="card">
        <div class="card-header"><h3 class="card-title">Tugas Aktif Terdekat</h3></div>
        <div class="card-body p-0">
            <table class="table table-striped mb-0">
                <thead><tr><th>Judul</th><th>Dosen</th><th>Departemen</th><th>Tenggat</th></tr></thead>
                <tbody>
                    @forelse ($tugasAktif as $item)
                        <tr>
                            <td>{{ $item->judul }}</td>
                            <td>{{ $item->dosen->nama }}</td>
                            <td>{{ $item->departemen->nama }}</td>
                            <td>{{ $item->deadline->format('d M Y H:i') }}</td>
                        </tr>
                    @empty
                        <tr><td colspan="4" class="text-center text-body-secondary">Tidak ada tugas aktif.</td></tr>
                    @endforelse
                </tbody>
            </table>
        </div>
    </div>
@stop
