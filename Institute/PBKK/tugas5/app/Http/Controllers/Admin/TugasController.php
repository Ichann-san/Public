<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Models\Departemen;
use App\Models\Dosen;
use App\Models\Tugas;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;
use Illuminate\Routing\Controllers\HasMiddleware;
use Illuminate\Routing\Controllers\Middleware;
use Illuminate\View\View;

class TugasController extends Controller implements HasMiddleware
{
    public static function middleware(): array
    {
        return [
            new Middleware('permission:lihat-tugas', only: ['index']),
            new Middleware('permission:tambah-tugas', only: ['create', 'store']),
            new Middleware('permission:edit-tugas', only: ['edit', 'update']),
            new Middleware('permission:hapus-tugas', only: ['destroy']),
        ];
    }

    public function index(Request $request): View
    {
        $status = $request->input('status');

        $tugas = Tugas::query()
            ->with(['dosen', 'departemen'])
            ->when($request->search, function ($q, $search) {
                return $q->where('judul', 'like', "%{$search}%");
            })
            ->when($request->departemen_id, function ($q, $deptId) {
                return $q->where('departemen_id', $deptId);
            })
            ->when($status === 'aktif', fn ($q) => $q->where('deadline', '>=', now()))
            ->when($status === 'lewat', fn ($q) => $q->where('deadline', '<', now()))
            ->orderBy('deadline')
            ->paginate(15)
            ->withQueryString(); // Kunci query parameter.

        $departemen = Departemen::orderBy('nama')->get();

        return view('admin.tugas.index', compact('tugas', 'departemen'));
    }

    public function create(): View
    {
        return view('admin.tugas.form', $this->formData(new Tugas()));
    }

    public function store(Request $request): RedirectResponse
    {
        Tugas::create($this->validated($request));

        return redirect()->route('admin.tugas.index')
            ->with('success', 'Tugas berhasil ditambahkan.');
    }

    public function edit(Tugas $tugas): View
    {
        return view('admin.tugas.form', $this->formData($tugas));
    }

    public function update(Request $request, Tugas $tugas): RedirectResponse
    {
        $tugas->update($this->validated($request));

        return redirect()->route('admin.tugas.index')
            ->with('success', 'Tugas berhasil diperbarui.');
    }

    public function destroy(Tugas $tugas): RedirectResponse
    {
        $tugas->delete();

        return redirect()->back()->with('success', 'Tugas berhasil dihapus.');
    }

    private function formData(Tugas $tugas): array
    {
        return [
            'tugas' => $tugas,
            'departemen' => Departemen::orderBy('nama')->get(),
            'dosen' => Dosen::orderBy('nama')->get(),
        ];
    }

    private function validated(Request $request): array
    {
        return $request->validate([
            'judul' => ['required', 'string', 'max:255'],
            'deskripsi' => ['nullable', 'string'],
            'deadline' => ['required', 'date'],
            'dosen_id' => ['required', 'exists:dosen,id'],
            'departemen_id' => ['required', 'exists:departemen,id'],
        ]);
    }
}
