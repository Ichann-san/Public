@extends('adminlte::auth.auth-page', ['authType' => 'login'])

@section('title', 'Login')

@section('auth_header', 'Selamat datang kembali.')

@section('auth_body')
    <p class="auth-copy">Masuk untuk melanjutkan aktivitas akademik Anda.</p>
    @if (session('status'))
        <div class="alert alert-success small">{{ session('status') }}</div>
    @endif

    <form action="{{ route('login') }}" method="post">
        @csrf

        @include('partials.auth-field', [
            'name' => 'email', 'type' => 'email', 'placeholder' => 'Email',
            'icon' => 'bi-envelope', 'autofocus' => true, 'autocomplete' => 'username',
        ])
        @include('partials.auth-field', [
            'name' => 'password', 'type' => 'password', 'placeholder' => 'Password',
            'icon' => 'bi-lock-fill', 'autocomplete' => 'current-password',
        ])

        <div class="row align-items-center">
            <div class="col-7">
                <div class="form-check">
                    <input class="form-check-input" type="checkbox" name="remember" id="remember">
                    <label class="form-check-label" for="remember">Ingat saya</label>
                </div>
            </div>
            <div class="col-5 d-grid">
                <button type="submit" class="btn btn-primary">
                    <i class="bi bi-box-arrow-in-right me-1"></i> Masuk
                </button>
            </div>
        </div>
    </form>

    @if (config('app.demo_login'))
        {{-- Tombol auto-login akun uji coba untuk demo di kelas. --}}
        <div class="demo-logins">
        <p class="text-center text-body-secondary small mb-2">Coba portal dengan akun demo</p>
        <div class="d-grid gap-2">
            @foreach ([
                'admin' => ['Admin', 'btn-outline-secondary', 'bi-shield-lock'],
                'staf' => ['Staf', 'btn-outline-secondary', 'bi-person-badge'],
                'mahasiswa' => ['Mahasiswa', 'btn-outline-secondary', 'bi-person'],
            ] as $role => [$label, $class, $icon])
                <form method="POST" action="{{ route('demo-login', $role) }}" class="d-grid">
                    @csrf
                    <button type="submit" class="btn btn-sm {{ $class }}" dusk="demo-{{ $role }}">
                        <i class="bi {{ $icon }} me-1"></i> Masuk sebagai {{ $label }}
                    </button>
                </form>
            @endforeach
        </div>
        </div>
    @endif
@stop

@section('auth_footer')
    <p class="my-0"><a href="{{ route('password.request') }}">Lupa password?</a></p>
    <p class="my-0"><a href="{{ route('register') }}">Daftar akun baru</a></p>
@stop
