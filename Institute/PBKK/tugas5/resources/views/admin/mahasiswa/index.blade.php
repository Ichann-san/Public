@extends('layouts.panel')

@section('title', 'Data Mahasiswa')

@section('content_header')
    <h1>Data Mahasiswa</h1>
    <p class="page-description">Cari, tambah, dan perbarui data mahasiswa.</p>
@stop

@section('content')
    @include('partials.flash')

    <div class="card">
        <div class="card-header">
            {{-- Form filter multi-variabel: keyword, departemen, status --}}
            <form method="GET" action="{{ route('admin.mahasiswa.index') }}" class="row g-2 align-items-center">
                <div class="col-md">
                    <input type="search" aria-label="Cari data" name="search" value="{{ request('search') }}" class="form-control"
                        placeholder="Cari nama atau NRP...">
                </div>
                <div class="col-md-3">
                    <select aria-label="Departemen" name="departemen_id" class="form-select">
                        <option value="">Semua departemen</option>
                        @foreach ($departemen as $dept)
                            <option value="{{ $dept->id }}" @selected(request('departemen_id') == $dept->id)>{{ $dept->nama }}</option>
                        @endforeach
                    </select>
                </div>
                <div class="col-md-2">
                    <select aria-label="Status" name="status" class="form-select">
                        <option value="">Semua status</option>
                        <option value="aktif" @selected(request('status') === 'aktif')>Aktif</option>
                        <option value="cuti" @selected(request('status') === 'cuti')>Cuti</option>
                    </select>
                </div>
                <div class="col-auto d-flex gap-2 text-nowrap">
                    <button type="submit" class="btn btn-primary"><i class="bi bi-funnel"></i> Filter</button>
                    <a href="{{ route('admin.mahasiswa.index') }}" class="btn btn-outline-secondary">Reset</a>
                    @can('tambah-mahasiswa')
                        <a href="{{ route('admin.mahasiswa.create') }}" class="btn btn-success ms-auto"><i class="bi bi-plus-lg"></i> Tambah</a>
                    @endcan
                </div>
            </form>
        </div>

        <div class="card-body p-0 table-responsive">
            <table class="table table-hover table-striped mb-0 align-middle">
                <thead>
                    <tr>
                        <th>NRP</th>
                        <th>Nama</th>
                        <th>Departemen</th>
                        <th>Angkatan</th>
                        <th>Status</th>
                        <th class="text-end">Aksi</th>
                    </tr>
                </thead>
                <tbody>
                    @forelse ($mahasiswa as $mhs)
                        <tr>
                            <td>{{ $mhs->nrp }}</td>
                            <td>{{ $mhs->nama }}<br><small class="text-body-secondary">{{ $mhs->email }}</small></td>
                            <td>{{ $mhs->departemen->nama }}</td>
                            <td>{{ $mhs->angkatan }}</td>
                            <td>
                                <span class="badge text-bg-{{ $mhs->is_active ? 'success' : 'secondary' }}">
                                    {{ $mhs->is_active ? 'Aktif' : 'Cuti' }}
                                </span>
                            </td>
                            <td class="text-end text-nowrap">
                                @can('edit-mahasiswa')
                                    <a href="{{ route('admin.mahasiswa.edit', $mhs) }}" class="btn btn-sm btn-primary"><i class="bi bi-pencil"></i> Edit</a>
                                @endcan
                                @include('partials.delete-button', [
                                    'permission' => 'hapus-mahasiswa',
                                    'action' => route('admin.mahasiswa.destroy', $mhs),
                                    'label' => $mhs->nama,
                                ])
                            </td>
                        </tr>
                    @empty
                        <tr><td colspan="6" class="text-center text-body-secondary py-4">Data tidak ditemukan.</td></tr>
                    @endforelse
                </tbody>
            </table>
        </div>

        <div class="card-footer">
            {{ $mahasiswa->links() }}
        </div>
    </div>
@stop
