@extends('adminlte::page')

@section('title', 'Pengguna & Peran')

@section('content_header')
    <h1>Pengguna &amp; Peran</h1>
@stop

@section('content')
    @include('partials.flash')

    <div class="card">
        <div class="card-header">
            <form method="GET" action="{{ route('admin.users.index') }}" class="row g-2 align-items-center">
                <div class="col-md">
                    <input type="search" name="search" value="{{ request('search') }}" class="form-control" placeholder="Cari nama atau email...">
                </div>
                <div class="col-md-3">
                    <select name="role" class="form-select">
                        <option value="">Semua peran</option>
                        @foreach ($roles as $role)
                            <option value="{{ $role }}" @selected(request('role') === $role)>{{ ucfirst($role) }}</option>
                        @endforeach
                    </select>
                </div>
                <div class="col-auto d-flex gap-2 text-nowrap">
                    <button type="submit" class="btn btn-primary"><i class="bi bi-funnel"></i> Filter</button>
                    <a href="{{ route('admin.users.index') }}" class="btn btn-outline-secondary">Reset</a>
                </div>
            </form>
        </div>

        <div class="card-body p-0 table-responsive">
            <table class="table table-hover table-striped mb-0 align-middle">
                <thead>
                    <tr><th>Nama</th><th>Email</th><th>Peran saat ini</th><th style="width: 280px">Ubah peran</th></tr>
                </thead>
                <tbody>
                    @foreach ($users as $user)
                        @php($peran = $user->getRoleNames()->first())
                        <tr>
                            <td>{{ $user->name }}</td>
                            <td>{{ $user->email }}</td>
                            <td>
                                <span class="badge text-bg-{{ ['admin' => 'danger', 'staf' => 'warning', 'mahasiswa' => 'secondary'][$peran] ?? 'light' }}">
                                    {{ $peran ? ucfirst($peran) : 'Tanpa peran' }}
                                </span>
                            </td>
                            <td>
                                <form method="POST" action="{{ route('admin.users.role', $user) }}" class="d-flex gap-2">
                                    @csrf
                                    @method('PUT')
                                    <select name="role" class="form-select form-select-sm">
                                        @foreach ($roles as $role)
                                            <option value="{{ $role }}" @selected($peran === $role)>{{ ucfirst($role) }}</option>
                                        @endforeach
                                    </select>
                                    <button type="submit" class="btn btn-sm btn-primary">Simpan</button>
                                </form>
                            </td>
                        </tr>
                    @endforeach
                </tbody>
            </table>
        </div>

        <div class="card-footer d-flex justify-content-end">
            {{ $users->links() }}
        </div>
    </div>
@stop
