<?php

namespace App\Http\Controllers;

use Illuminate\Contracts\View\View;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;

class PageController extends Controller
{
    public function home(Request $request): View
    {
        $user = $request->query('user');
        $userName = is_string($user) ? mb_substr(trim($user), 0, 60) : '';

        return view('pages.home', [
            'title' => 'Beranda',
            'userName' => $userName,
            'isDarkMode' => false,
        ]);
    }

    public function profile(): View
    {
        return view('pages.profile', [
            'title' => 'Profil Mahasiswa',
            'isDarkMode' => false,
            'student' => [
                'name' => 'Maulana',
                'nrp' => '5025241001',
                'university' => 'Institut Teknologi Sepuluh Nopember',
                'program' => 'Teknik Informatika',
                'status' => 'Mahasiswa Aktif',
            ],
        ]);
    }

    public function ideas(Request $request): View
    {
        return view('pages.ideas', [
            'title' => 'Ide Agentic AI',
            'isDarkMode' => $request->query('mode') === 'dark',
        ]);
    }

    public function storeIdea(Request $request): RedirectResponse
    {
        $validated = $request->validate([
            'name' => ['required', 'string', 'max:80'],
            'idea' => ['required', 'string', 'max:120'],
            'description' => ['required', 'string', 'max:1000'],
            'mode' => ['nullable', 'in:dark'],
        ]);

        $query = ($validated['mode'] ?? null) === 'dark' ? ['mode' => 'dark'] : [];

        return redirect()->route('ideas', $query)
            ->with('status', 'Terima kasih, '.$validated['name'].'! Ide "'.$validated['idea'].'" berhasil diterima untuk pratinjau.');
    }
}
