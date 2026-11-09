@extends('adminlte::auth.auth-page', ['authType' => 'register'])

@section('title', 'Daftar')

@section('auth_header', 'Daftar akun baru')

@section('auth_body')
    <form action="{{ route('register') }}" method="post">
        @csrf
        @include('partials.auth-field', ['name' => 'name', 'placeholder' => 'Nama lengkap', 'icon' => 'bi-person', 'autofocus' => true, 'autocomplete' => 'name'])
        @include('partials.auth-field', ['name' => 'email', 'type' => 'email', 'placeholder' => 'Email', 'icon' => 'bi-envelope', 'autocomplete' => 'username'])
        @include('partials.auth-field', ['name' => 'password', 'type' => 'password', 'placeholder' => 'Password', 'icon' => 'bi-lock-fill', 'autocomplete' => 'new-password'])
        @include('partials.auth-field', ['name' => 'password_confirmation', 'type' => 'password', 'placeholder' => 'Ulangi password', 'icon' => 'bi-lock', 'autocomplete' => 'new-password'])

        <div class="d-grid">
            <button type="submit" class="btn btn-primary">
                <i class="bi bi-person-plus me-1"></i> Daftar
            </button>
        </div>
    </form>
@stop

@section('auth_footer')
    <p class="my-0"><a href="{{ route('login') }}">Sudah punya akun? Masuk</a></p>
@stop
