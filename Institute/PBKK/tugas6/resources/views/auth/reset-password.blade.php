@extends('adminlte::auth.auth-page', ['authType' => 'login'])

@section('title', 'Reset Password')

@section('auth_header', 'Atur ulang password')

@section('auth_body')
    <form action="{{ route('password.store') }}" method="post">
        @csrf
        <input type="hidden" name="token" value="{{ $request->route('token') }}">
        @include('partials.auth-field', ['name' => 'email', 'type' => 'email', 'placeholder' => 'Email', 'icon' => 'bi-envelope', 'value' => $request->email, 'autocomplete' => 'username'])
        @include('partials.auth-field', ['name' => 'password', 'type' => 'password', 'placeholder' => 'Password baru', 'icon' => 'bi-lock-fill', 'autofocus' => true, 'autocomplete' => 'new-password'])
        @include('partials.auth-field', ['name' => 'password_confirmation', 'type' => 'password', 'placeholder' => 'Ulangi password', 'icon' => 'bi-lock', 'autocomplete' => 'new-password'])
        <div class="d-grid">
            <button type="submit" class="btn btn-primary">Simpan password</button>
        </div>
    </form>
@stop
