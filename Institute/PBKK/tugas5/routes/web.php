<?php

use App\Http\Controllers\Admin\DashboardController;
use App\Http\Controllers\Admin\DosenController;
use App\Http\Controllers\Admin\MahasiswaController;
use App\Http\Controllers\Admin\TugasController;
use App\Http\Controllers\Admin\UserController;
use App\Http\Controllers\Auth\DemoLoginController;
use App\Http\Controllers\HomeController;
use App\Http\Controllers\ProfileController;
use Illuminate\Support\Facades\Route;

// Halaman publik.
Route::view('/', 'welcome')->name('welcome');

// Tombol auto-login akun uji coba (hanya aktif jika DEMO_LOGIN=true).
Route::post('/demo-login/{role}', DemoLoginController::class)
    ->middleware('guest')
    ->whereIn('role', ['admin', 'staf', 'mahasiswa'])
    ->name('demo-login');

Route::middleware('auth')->group(function () {
    // Pengalihan otomatis berdasarkan peran setelah login.
    Route::get('/dashboard', function () {
        return auth()->user()->hasAnyRole(['admin', 'staf'])
            ? redirect()->route('admin.dashboard')
            : redirect()->route('home');
    })->name('dashboard');

    // Beranda pengguna biasa (mahasiswa).
    Route::get('/home', HomeController::class)->name('home');

    Route::get('/profile', [ProfileController::class, 'edit'])->name('profile.edit');
    Route::patch('/profile', [ProfileController::class, 'update'])->name('profile.update');
    Route::delete('/profile', [ProfileController::class, 'destroy'])->name('profile.destroy');
});

// Panel admin: hanya untuk peran admin dan staf.
Route::middleware(['auth', 'role:admin|staf'])
    ->prefix('admin')
    ->name('admin.')
    ->group(function () {
        Route::get('/dashboard', [DashboardController::class, 'index'])->name('dashboard');

        Route::resource('mahasiswa', MahasiswaController::class)
            ->except('show')
            ->parameters(['mahasiswa' => 'mahasiswa']);

        Route::resource('dosen', DosenController::class)
            ->except('show')
            ->parameters(['dosen' => 'dosen']);

        Route::resource('tugas', TugasController::class)
            ->except('show')
            ->parameters(['tugas' => 'tugas']);

        // Manajemen pengguna & peran: khusus admin.
        Route::middleware('role:admin')->group(function () {
            Route::get('/users', [UserController::class, 'index'])->name('users.index');
            Route::put('/users/{user}/role', [UserController::class, 'updateRole'])->name('users.role');
        });
    });

require __DIR__.'/auth.php';
