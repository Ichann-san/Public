@extends('adminlte::page')

@section('title', 'Profil')

@section('content_header')
    <h1>Profil</h1>
@stop

@section('content')
    @if (session('status') === 'profile-updated')
        <div class="alert alert-success">Profil berhasil diperbarui.</div>
    @elseif (session('status') === 'password-updated')
        <div class="alert alert-success">Password berhasil diperbarui.</div>
    @endif

    <div class="row">
        <div class="col-lg-6">
            <div class="card mb-4">
                <div class="card-header"><h3 class="card-title">Informasi Profil</h3></div>
                <form method="POST" action="{{ route('profile.update') }}">
                    @csrf
                    @method('PATCH')
                    <div class="card-body">
                        <div class="mb-3">
                            <label for="name" class="form-label">Nama</label>
                            <input type="text" id="name" name="name" value="{{ old('name', $user->name) }}" class="form-control @error('name') is-invalid @enderror" required>
                            @error('name')<div class="invalid-feedback">{{ $message }}</div>@enderror
                        </div>
                        <div class="mb-3">
                            <label for="email" class="form-label">Email</label>
                            <input type="email" id="email" name="email" value="{{ old('email', $user->email) }}" class="form-control @error('email') is-invalid @enderror" required>
                            @error('email')<div class="invalid-feedback">{{ $message }}</div>@enderror
                        </div>
                        <p class="mb-0 small text-body-secondary">Peran: {{ $user->getRoleNames()->implode(', ') ?: '-' }}</p>
                    </div>
                    <div class="card-footer"><button type="submit" class="btn btn-primary">Simpan</button></div>
                </form>
            </div>
        </div>

        <div class="col-lg-6">
            <div class="card mb-4">
                <div class="card-header"><h3 class="card-title">Ubah Password</h3></div>
                <form method="POST" action="{{ route('password.update') }}">
                    @csrf
                    @method('PUT')
                    <div class="card-body">
                        @foreach (['current_password' => 'Password saat ini', 'password' => 'Password baru', 'password_confirmation' => 'Ulangi password baru'] as $field => $label)
                            <div class="mb-3">
                                <label for="{{ $field }}" class="form-label">{{ $label }}</label>
                                <input type="password" id="{{ $field }}" name="{{ $field }}" class="form-control @error($field, 'updatePassword') is-invalid @enderror">
                                @error($field, 'updatePassword')<div class="invalid-feedback">{{ $message }}</div>@enderror
                            </div>
                        @endforeach
                    </div>
                    <div class="card-footer"><button type="submit" class="btn btn-primary">Simpan Password</button></div>
                </form>
            </div>

            <div class="card card-outline card-danger mb-4">
                <div class="card-header"><h3 class="card-title">Hapus Akun</h3></div>
                <form method="POST" action="{{ route('profile.destroy') }}" onsubmit="return confirm('Yakin ingin menghapus akun ini secara permanen?');">
                    @csrf
                    @method('DELETE')
                    <div class="card-body">
                        <p class="small">Setelah akun dihapus, semua data akun akan hilang permanen.</p>
                        <label for="delete_password" class="form-label">Password</label>
                        <input type="password" id="delete_password" name="password" class="form-control @error('password', 'userDeletion') is-invalid @enderror">
                        @error('password', 'userDeletion')<div class="invalid-feedback">{{ $message }}</div>@enderror
                    </div>
                    <div class="card-footer"><button type="submit" class="btn btn-danger">Hapus Akun</button></div>
                </form>
            </div>
        </div>
    </div>
@stop
