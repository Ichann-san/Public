@extends('layouts.panel')

@section('title', 'Data Dosen')

@section('content_header')
    <h1>Data Dosen</h1>
    <p class="page-description">Kelola informasi dosen dan departemennya.</p>
@stop

@section('content')
    @include('partials.flash')

    <div class="card">
        <div class="card-header">
            <form method="GET" action="{{ route('admin.dosen.index') }}" class="row g-2 align-items-center">
                <div class="col-md">
                    <input type="search" aria-label="Cari data" name="search" value="{{ request('search') }}" class="form-control" placeholder="Cari nama atau NIP...">
                </div>
                <div class="col-md-4">
                    <select aria-label="Departemen" name="departemen_id" class="form-select">
                        <option value="">Semua departemen</option>
                        @foreach ($departemen as $dept)
                            <option value="{{ $dept->id }}" @selected(request('departemen_id') == $dept->id)>{{ $dept->nama }}</option>
                        @endforeach
                    </select>
                </div>
                <div class="col-auto d-flex gap-2 text-nowrap">
                    <button type="submit" class="btn btn-primary"><i class="bi bi-funnel"></i> Filter</button>
                    <a href="{{ route('admin.dosen.index') }}" class="btn btn-outline-secondary">Reset</a>
                    @can('tambah-dosen')
                        <a href="{{ route('admin.dosen.create') }}" class="btn btn-success ms-auto"><i class="bi bi-plus-lg"></i> Tambah</a>
                    @endcan
                </div>
            </form>
        </div>

        <div class="card-body p-0 table-responsive">
            <table class="table table-hover table-striped mb-0 align-middle">
                <thead>
                    <tr><th>NIP</th><th>Nama</th><th>Departemen</th><th class="text-end">Jumlah Tugas</th><th class="text-end">Aksi</th></tr>
                </thead>
                <tbody>
                    @forelse ($dosen as $item)
                        <tr>
                            <td>{{ $item->nip }}</td>
                            <td>{{ $item->nama }}<br><small class="text-body-secondary">{{ $item->email }}</small></td>
                            <td>{{ $item->departemen->nama }}</td>
                            <td class="text-end">{{ $item->tugas_count }}</td>
                            <td class="text-end text-nowrap">
                                @can('edit-dosen')
                                    <a href="{{ route('admin.dosen.edit', $item) }}" class="btn btn-sm btn-primary"><i class="bi bi-pencil"></i> Edit</a>
                                @endcan
                                @include('partials.delete-button', [
                                    'permission' => 'hapus-dosen',
                                    'action' => route('admin.dosen.destroy', $item),
                                    'label' => $item->nama,
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
            {{ $dosen->links() }}
        </div>
    </div>
@stop
