@extends('adminlte::auth.auth-page', ['authType' => 'login'])

@section('title', 'Lupa Password')

@section('auth_header', 'Lupa password')

@section('auth_body')
    <p class="small text-body-secondary">Masukkan email Anda, kami akan mengirim tautan untuk mengatur ulang password.</p>

    @if (session('status'))
        <div class="alert alert-success small">{{ session('status') }}</div>
    @endif

    <form action="{{ route('password.email') }}" method="post">
        @csrf
        @include('partials.auth-field', ['name' => 'email', 'type' => 'email', 'placeholder' => 'Email', 'icon' => 'bi-envelope', 'autofocus' => true])
        <div class="d-grid">
            <button type="submit" class="btn btn-primary">Kirim tautan reset password</button>
        </div>
    </form>
@stop

@section('auth_footer')
    <p class="my-0"><a href="{{ route('login') }}">Kembali ke login</a></p>
@stop
