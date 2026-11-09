<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Models\Departemen;
use App\Models\Dosen;
use App\Models\Mahasiswa;
use App\Models\Tugas;
use App\Models\User;
use Illuminate\Routing\Controllers\HasMiddleware;
use Illuminate\Routing\Controllers\Middleware;
use Illuminate\View\View;

class DashboardController extends Controller implements HasMiddleware
{
    public static function middleware(): array
    {
        return [
            new Middleware('permission:akses-dashboard'),
        ];
    }

    public function index(): View
    {
        // Widget statistik agregat (kueri count()).
        $statistik = [
            'mahasiswa' => Mahasiswa::count(),
            'dosen' => Dosen::count(),
            'tugas_aktif' => Tugas::aktif()->count(),
            'pengguna' => User::count(),
        ];

        $mahasiswaPerDepartemen = Departemen::withCount([
            'mahasiswa',
            'mahasiswa as mahasiswa_aktif_count' => fn ($q) => $q->where('is_active', true),
        ])->orderBy('nama')->get();

        $tugasTerdekat = Tugas::aktif()
            ->with(['dosen', 'departemen'])
            ->orderBy('deadline')
            ->limit(5)
            ->get();

        return view('admin.dashboard', compact('statistik', 'mahasiswaPerDepartemen', 'tugasTerdekat'));
    }
}
