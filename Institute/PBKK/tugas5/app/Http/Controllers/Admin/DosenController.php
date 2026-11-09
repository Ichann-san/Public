<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Models\Departemen;
use App\Models\Dosen;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;
use Illuminate\Routing\Controllers\HasMiddleware;
use Illuminate\Routing\Controllers\Middleware;
use Illuminate\Validation\Rule;
use Illuminate\View\View;

class DosenController extends Controller implements HasMiddleware
{
    public static function middleware(): array
    {
        return [
            new Middleware('permission:lihat-dosen', only: ['index']),
            new Middleware('permission:tambah-dosen', only: ['create', 'store']),
            new Middleware('permission:edit-dosen', only: ['edit', 'update']),
            new Middleware('permission:hapus-dosen', only: ['destroy']),
        ];
    }

    public function index(Request $request): View
    {
        $dosen = Dosen::query()
            ->with('departemen')
            ->withCount('tugas')
            ->when($request->search, function ($query, $search) {
                return $query->where(function ($q) use ($search) {
                    $q->where('nama', 'like', "%{$search}%")
                        ->orWhere('nip', 'like', "%{$search}%");
                });
            })
            ->when($request->departemen_id, function ($query, $departemenId) {
                return $query->where('departemen_id', $departemenId);
            })
            ->orderBy('nama')
            ->paginate(10)
            ->withQueryString();

        $departemen = Departemen::orderBy('nama')->get();

        return view('admin.dosen.index', compact('dosen', 'departemen'));
    }

    public function create(): View
    {
        return view('admin.dosen.form', [
            'dosen' => new Dosen(),
            'departemen' => Departemen::orderBy('nama')->get(),
        ]);
    }

    public function store(Request $request): RedirectResponse
    {
        Dosen::create($this->validated($request));

        return redirect()->route('admin.dosen.index')
            ->with('success', 'Data dosen berhasil ditambahkan.');
    }

    public function edit(Dosen $dosen): View
    {
        return view('admin.dosen.form', [
            'dosen' => $dosen,
            'departemen' => Departemen::orderBy('nama')->get(),
        ]);
    }

    public function update(Request $request, Dosen $dosen): RedirectResponse
    {
        $dosen->update($this->validated($request, $dosen));

        return redirect()->route('admin.dosen.index')
            ->with('success', 'Data dosen berhasil diperbarui.');
    }

    public function destroy(Dosen $dosen): RedirectResponse
    {
        $dosen->delete();

        return redirect()->back()->with('success', 'Data dosen berhasil dihapus.');
    }

    private function validated(Request $request, ?Dosen $dosen = null): array
    {
        return $request->validate([
            'nip' => ['required', 'string', 'max:20', Rule::unique('dosen')->ignore($dosen)],
            'nama' => ['required', 'string', 'max:255'],
            'email' => ['required', 'email', 'max:255', Rule::unique('dosen')->ignore($dosen)],
            'departemen_id' => ['required', 'exists:departemen,id'],
        ]);
    }
}
