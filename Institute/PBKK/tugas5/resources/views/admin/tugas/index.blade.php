@extends('layouts.panel')

@section('title', 'Data Tugas')

@section('content_header')
    <h1>Kelola Tugas</h1>
    <p class="page-description">Atur tugas akademik dan pantau tenggatnya.</p>
@stop

@section('content')
    @include('partials.flash')

    <div class="card">
        <div class="card-header">
            <form method="GET" action="{{ route('admin.tugas.index') }}" class="row g-2 align-items-center">
                <div class="col-md">
                    <input type="search" aria-label="Cari data" name="search" value="{{ request('search') }}" class="form-control" placeholder="Cari judul tugas...">
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
                        <option value="lewat" @selected(request('status') === 'lewat')>Lewat tenggat</option>
                    </select>
                </div>
                <div class="col-auto d-flex gap-2 text-nowrap">
                    <button type="submit" class="btn btn-primary"><i class="bi bi-funnel"></i> Filter</button>
                    <a href="{{ route('admin.tugas.index') }}" class="btn btn-outline-secondary">Reset</a>
                    @can('tambah-tugas')
                        <a href="{{ route('admin.tugas.create') }}" class="btn btn-success ms-auto"><i class="bi bi-plus-lg"></i> Tambah</a>
                    @endcan
                </div>
            </form>
        </div>

        <div class="card-body p-0 table-responsive">
            <table class="table table-hover table-striped mb-0 align-middle">
                <thead>
                    <tr><th>Judul</th><th>Dosen</th><th>Departemen</th><th>Tenggat</th><th class="text-end">Aksi</th></tr>
                </thead>
                <tbody>
                    @forelse ($tugas as $item)
                        @php($aktif = $item->deadline->isFuture())
                        <tr>
                            <td>{{ $item->judul }}</td>
                            <td>{{ $item->dosen->nama }}</td>
                            <td>{{ $item->departemen->nama }}</td>
                            <td>
                                {{ $item->deadline->format('d M Y H:i') }}
                                <span class="badge text-bg-{{ $aktif ? 'success' : 'secondary' }}">{{ $aktif ? 'Aktif' : 'Lewat' }}</span>
                            </td>
                            <td class="text-end text-nowrap">
                                @can('edit-tugas')
                                    <a href="{{ route('admin.tugas.edit', $item) }}" class="btn btn-sm btn-primary"><i class="bi bi-pencil"></i> Edit</a>
                                @endcan
                                @include('partials.delete-button', [
                                    'permission' => 'hapus-tugas',
                                    'action' => route('admin.tugas.destroy', $item),
                                    'label' => $item->judul,
                                ])
                            </td>
                        </tr>
                    @empty
                        <tr><td colspan="5" class="text-center text-body-secondary py-4">Data tidak ditemukan.</td></tr>
                    @endforelse
                </tbody>
            </table>
        </div>

        <div class="card-footer">
            {{ $tugas->links() }}
        </div>
    </div>
@stop
