@extends('layouts.panel')

@php($edit = $tugas->exists)

@section('title', $edit ? 'Edit Tugas' : 'Tambah Tugas')

@section('content_header')
    <h1>{{ $edit ? 'Edit Tugas' : 'Tambah Tugas' }}</h1>
@stop

@section('content')
    <div class="card">
        <form method="POST" action="{{ $edit ? route('admin.tugas.update', $tugas) : route('admin.tugas.store') }}">
            @csrf
            @if ($edit) @method('PUT') @endif

            <div class="card-body row g-3">
                <div class="col-md-8">
                    <label for="judul" class="form-label">Judul</label>
                    <input type="text" id="judul" name="judul" value="{{ old('judul', $tugas->judul) }}" class="form-control @error('judul') is-invalid @enderror" required>
                    @error('judul')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-4">
                    <label for="deadline" class="form-label">Tenggat</label>
                    <input type="datetime-local" id="deadline" name="deadline" value="{{ old('deadline', $tugas->deadline?->format('Y-m-d\TH:i')) }}" class="form-control @error('deadline') is-invalid @enderror" required>
                    @error('deadline')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-6">
                    <label for="dosen_id" class="form-label">Dosen pengampu</label>
                    <select id="dosen_id" name="dosen_id" class="form-select @error('dosen_id') is-invalid @enderror" required>
                        <option value="">Pilih...</option>
                        @foreach ($dosen as $item)
                            <option value="{{ $item->id }}" @selected(old('dosen_id', $tugas->dosen_id) == $item->id)>{{ $item->nama }}</option>
                        @endforeach
                    </select>
                    @error('dosen_id')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-md-6">
                    <label for="departemen_id" class="form-label">Departemen</label>
                    <select id="departemen_id" name="departemen_id" class="form-select @error('departemen_id') is-invalid @enderror" required>
                        <option value="">Pilih...</option>
                        @foreach ($departemen as $dept)
                            <option value="{{ $dept->id }}" @selected(old('departemen_id', $tugas->departemen_id) == $dept->id)>{{ $dept->nama }}</option>
                        @endforeach
                    </select>
                    @error('departemen_id')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
                <div class="col-12">
                    <label for="deskripsi" class="form-label">Deskripsi</label>
                    <textarea id="deskripsi" name="deskripsi" rows="4" class="form-control @error('deskripsi') is-invalid @enderror">{{ old('deskripsi', $tugas->deskripsi) }}</textarea>
                    @error('deskripsi')<div class="invalid-feedback">{{ $message }}</div>@enderror
                </div>
            </div>

            <div class="card-footer d-flex gap-2">
                <button type="submit" class="btn btn-primary"><i class="bi bi-save"></i> Simpan</button>
                <a href="{{ route('admin.tugas.index') }}" class="btn btn-outline-secondary">Batal</a>
            </div>
        </form>
    </div>
@stop
