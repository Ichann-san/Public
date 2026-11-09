<?php

namespace App\Http\Controllers;

use App\Models\Tugas;
use Illuminate\View\View;

class HomeController extends Controller
{
    /**
     * Beranda publik untuk pengguna non-admin.
     */
    public function __invoke(): View
    {
        $tugasAktif = Tugas::aktif()
            ->with(['dosen', 'departemen'])
            ->orderBy('deadline')
            ->limit(5)
            ->get();

        return view('home', compact('tugasAktif'));
    }
}
