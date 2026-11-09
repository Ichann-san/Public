@extends('adminlte::master')

@section('title', 'Selamat Datang')

@section('classes_body', 'bg-body-secondary')

@section('body')
    <main class="container py-5">
        <div class="row justify-content-center">
            <div class="col-lg-8 text-center">
                <img src="{{ asset(config('adminlte.logo_img')) }}" alt="Logo" height="72" class="mb-3">
                <h1 class="display-5 fw-bold">Portal Akademik</h1>
                <p class="lead text-body-secondary mb-4">
                    Admin Dashboard &amp; Role-Based Access Control dengan Laravel, AdminLTE,
                    Laravel Breeze, dan Spatie Laravel Permission.
                </p>
                <div class="d-flex gap-2 justify-content-center">
                    @auth
                        <a href="{{ route('dashboard') }}" class="btn btn-primary btn-lg">
                            <i class="bi bi-speedometer2 me-1"></i> Buka Dashboard
                        </a>
                    @else
                        <a href="{{ route('login') }}" class="btn btn-primary btn-lg">
                            <i class="bi bi-box-arrow-in-right me-1"></i> Masuk
                        </a>
                        <a href="{{ route('register') }}" class="btn btn-outline-secondary btn-lg">Daftar</a>
                    @endauth
                </div>
            </div>
        </div>
    </main>
@stop
