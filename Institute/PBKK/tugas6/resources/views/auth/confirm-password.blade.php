@extends('adminlte::auth.auth-page', ['authType' => 'login'])

@section('title', 'Konfirmasi Password')

@section('auth_header', 'Konfirmasi password')

@section('auth_body')
    <p class="small text-body-secondary">Area ini aman. Konfirmasi password Anda sebelum melanjutkan.</p>
    <form action="{{ route('password.confirm') }}" method="post">
        @csrf
        @include('partials.auth-field', ['name' => 'password', 'type' => 'password', 'placeholder' => 'Password', 'icon' => 'bi-lock-fill', 'autofocus' => true, 'autocomplete' => 'current-password'])
        <div class="d-grid">
            <button type="submit" class="btn btn-primary">Konfirmasi</button>
        </div>
    </form>
@stop
