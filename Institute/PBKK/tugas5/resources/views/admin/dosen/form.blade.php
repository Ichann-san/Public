@extends('layouts.panel')

@php($edit = $dosen->exists)

@section('title', $edit ? 'Edit Dosen' : 'Tambah Dosen')

@section('content_header')
    <h1>{{ $edit ? 'Edit Dosen' : 'Tambah Dosen' }}</h1>
@stop

@section('content')
    <div class="card">
        <form method="POST" action="{{ $edit ? route('admin.dosen.update', $dosen) : route('admin.dosen.store') }}">
            @csrf
            @if ($edit) @method('PUT') @endif

            <div class="card-body row g-3">
                <div class="col-md-4">
                    <label for="nip" class="form-label">NIP</label>
                    <input type="text" id="nip" name="nip" value="{{ old('nip', $dosen->nip) }}" class="form-control @error('nip') is-invalid @enderror" required>
                    @error('nip')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-8">
                    <label for="nama" class="form-label">Nama</label>
                    <input type="text" id="nama" name="nama" value="{{ old('nama', $dosen->nama) }}" class="form-control @error('nama') is-invalid @enderror" required>
                    @error('nama')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-6">
                    <label for="email" class="form-label">Email</label>
                    <input type="email" id="email" name="email" value="{{ old('email', $dosen->email) }}" class="form-control @error('email') is-invalid @enderror" required>
                    @error('email')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-6">
                    <label for="departemen_id" class="form-label">Departemen</label>
                    <select id="departemen_id" name="departemen_id" class="form-select @error('departemen_id') is-invalid @enderror" required>
                        <option value="">Pilih...</option>
                        @foreach ($departemen as $dept)
                            <option value="{{ $dept->id }}" @selected(old('departemen_id', $dosen->departemen_id) == $dept->id)>{{ $dept->nama }}</option>
                        @endforeach
                    </select>
                    @error('departemen_id')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
            </div>

            <div class="card-footer d-flex gap-2">
                <button type="submit" class="btn btn-primary"><i class="bi bi-save"></i> Simpan</button>
                <a href="{{ route('admin.dosen.index') }}" class="btn btn-outline-secondary">Batal</a>
            </div>
        </form>
    </div>
@stop
