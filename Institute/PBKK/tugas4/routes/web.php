<?php

use App\Http\Controllers\PageController;
use Illuminate\Support\Facades\Route;

Route::get('/', [PageController::class, 'home'])->name('home');
Route::get('/beranda', [PageController::class, 'home'])->name('beranda');
Route::get('/profil-mahasiswa', [PageController::class, 'profile'])->name('profile');
Route::get('/ide-agent', [PageController::class, 'ideas'])->name('ideas');
Route::post('/ide-agent', [PageController::class, 'storeIdea'])->name('ideas.store');
