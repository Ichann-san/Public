@extends('adminlte::auth.auth-page', ['authType' => 'login'])

@section('title', 'Verifikasi Email')

@section('auth_header', 'Verifikasi email')

@section('auth_body')
    <p class="small">Terima kasih telah mendaftar! Silakan verifikasi email Anda lewat tautan yang kami kirim.</p>

    @if (session('status') == 'verification-link-sent')
        <div class="alert alert-success small">Tautan verifikasi baru telah dikirim ke email Anda.</div>
    @endif

    <div class="d-flex justify-content-between">
        <form method="POST" action="{{ route('verification.send') }}">
            @csrf
            <button type="submit" class="btn btn-primary btn-sm">Kirim ulang email verifikasi</button>
        </form>
        <form method="POST" action="{{ route('logout') }}">
            @csrf
            <button type="submit" class="btn btn-link btn-sm">Keluar</button>
        </form>
    </div>
@stop
