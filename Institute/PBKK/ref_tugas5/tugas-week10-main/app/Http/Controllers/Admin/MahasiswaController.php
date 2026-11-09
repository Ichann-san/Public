<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Models\Departemen;
use App\Models\Mahasiswa;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;
use Illuminate\Routing\Controllers\HasMiddleware;
use Illuminate\Routing\Controllers\Middleware;
use Illuminate\Validation\Rule;
use Illuminate\View\View;

class MahasiswaController extends Controller implements HasMiddleware
{
    /**
     * Pengaman server-side: setiap aksi dikunci dengan izin Spatie,
     * sehingga request manual (mis. lewat Postman) tetap ditolak.
     */
    public static function middleware(): array
    {
        return [
            new Middleware('permission:lihat-mahasiswa', only: ['index']),
            new Middleware('permission:tambah-mahasiswa', only: ['create', 'store']),
            new Middleware('permission:edit-mahasiswa', only: ['edit', 'update']),
            new Middleware('permission:hapus-mahasiswa', only: ['destroy']),
        ];
    }

    public function index(Request $request): View
    {
        $search = $request->input('search');
        $status = $request->input('status');

        // Filter multi-variabel menggunakan kueri kondisional when().
        $mahasiswa = Mahasiswa::query()
            ->with('departemen')
            ->when($search, function ($query, $search) {
                return $query->where(function ($q) use ($search) {
                    $q->where('nama', 'like', "%{$search}%")
                        ->orWhere('nrp', 'like', "%{$search}%");
                });
            })
            ->when($request->departemen_id, function ($query, $departemenId) {
                return $query->where('departemen_id', $departemenId);
            })
            ->when(in_array($status, ['aktif', 'cuti'], true), function ($query) use ($status) {
                return $query->where('is_active', $status === 'aktif');
            })
            ->orderBy('nrp')
            ->paginate(10)
            ->withQueryString(); // Kunci parameter filter pada link pagination.

        $departemen = Departemen::orderBy('nama')->get();

        return view('admin.mahasiswa.index', compact('mahasiswa', 'departemen'));
    }

    public function create(): View
    {
        return view('admin.mahasiswa.form', [
            'mahasiswa' => new Mahasiswa(['is_active' => true, 'angkatan' => now()->year]),
            'departemen' => Departemen::orderBy('nama')->get(),
        ]);
    }

    public function store(Request $request): RedirectResponse
    {
        Mahasiswa::create($this->validated($request));

        return redirect()->route('admin.mahasiswa.index')
            ->with('success', 'Data mahasiswa berhasil ditambahkan.');
    }

    public function edit(Mahasiswa $mahasiswa): View
    {
        return view('admin.mahasiswa.form', [
            'mahasiswa' => $mahasiswa,
            'departemen' => Departemen::orderBy('nama')->get(),
        ]);
    }

    public function update(Request $request, Mahasiswa $mahasiswa): RedirectResponse
    {
        $mahasiswa->update($this->validated($request, $mahasiswa));

        return redirect()->route('admin.mahasiswa.index')
            ->with('success', 'Data mahasiswa berhasil diperbarui.');
    }

    public function destroy(Mahasiswa $mahasiswa): RedirectResponse
    {
        $mahasiswa->delete();

        return redirect()->back()->with('success', 'Data mahasiswa berhasil dihapus.');
    }

    private function validated(Request $request, ?Mahasiswa $mahasiswa = null): array
    {
        $data = $request->validate([
            'nrp' => ['required', 'string', 'max:20', Rule::unique('mahasiswa')->ignore($mahasiswa)],
            'nama' => ['required', 'string', 'max:255'],
            'email' => ['required', 'email', 'max:255', Rule::unique('mahasiswa')->ignore($mahasiswa)],
            'angkatan' => ['required', 'integer', 'min:2000', 'max:'.(now()->year + 1)],
            'departemen_id' => ['required', 'exists:departemen,id'],
        ]);

        $data['is_active'] = $request->boolean('is_active');

        return $data;
    }
}
