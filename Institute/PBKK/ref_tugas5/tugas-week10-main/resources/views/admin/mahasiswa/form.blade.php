@extends('adminlte::page')

@php($edit = $mahasiswa->exists)

@section('title', $edit ? 'Edit Mahasiswa' : 'Tambah Mahasiswa')

@section('content_header')
    <h1>{{ $edit ? 'Edit Mahasiswa' : 'Tambah Mahasiswa' }}</h1>
@stop

@section('content')
    <div class="card">
        <form method="POST" action="{{ $edit ? route('admin.mahasiswa.update', $mahasiswa) : route('admin.mahasiswa.store') }}">
            @csrf
            @if ($edit) @method('PUT') @endif

            <div class="card-body row g-3">
                <div class="col-md-4">
                    <label for="nrp" class="form-label">NRP</label>
                    <input type="text" id="nrp" name="nrp" value="{{ old('nrp', $mahasiswa->nrp) }}" class="form-control @error('nrp') is-invalid @enderror" required>
                    @error('nrp')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-8">
                    <label for="nama" class="form-label">Nama</label>
                    <input type="text" id="nama" name="nama" value="{{ old('nama', $mahasiswa->nama) }}" class="form-control @error('nama') is-invalid @enderror" required>
                    @error('nama')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-6">
                    <label for="email" class="form-label">Email</label>
                    <input type="email" id="email" name="email" value="{{ old('email', $mahasiswa->email) }}" class="form-control @error('email') is-invalid @enderror" required>
                    @error('email')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-3">
                    <label for="angkatan" class="form-label">Angkatan</label>
                    <input type="number" id="angkatan" name="angkatan" value="{{ old('angkatan', $mahasiswa->angkatan) }}" class="form-control @error('angkatan') is-invalid @enderror" required>
                    @error('angkatan')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-3">
                    <label for="departemen_id" class="form-label">Departemen</label>
                    <select id="departemen_id" name="departemen_id" class="form-select @error('departemen_id') is-invalid @enderror" required>
                        <option value="">Pilih...</option>
                        @foreach ($departemen as $dept)
                            <option value="{{ $dept->id }}" @selected(old('departemen_id', $mahasiswa->departemen_id) == $dept->id)>{{ $dept->nama }}</option>
                        @endforeach
                    </select>
                    @error('departemen_id')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-12">
                    <div class="form-check form-switch">
                        <input type="checkbox" class="form-check-input" id="is_active" name="is_active" value="1" @checked(old('is_active', $mahasiswa->is_active))>
                        <label class="form-check-label" for="is_active">Mahasiswa aktif (tidak cuti)</label>
                    </div>
                </div>
            </div>

            <div class="card-footer d-flex gap-2">
                <button type="submit" class="btn btn-primary"><i class="bi bi-save"></i> Simpan</button>
                <a href="{{ route('admin.mahasiswa.index') }}" class="btn btn-outline-secondary">Batal</a>
            </div>
        </form>
    </div>
@stop
