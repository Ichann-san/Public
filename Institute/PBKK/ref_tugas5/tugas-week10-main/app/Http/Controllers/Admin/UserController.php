<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use App\Models\User;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;
use Illuminate\Routing\Controllers\HasMiddleware;
use Illuminate\Routing\Controllers\Middleware;
use Illuminate\Validation\Rule;
use Illuminate\View\View;
use Spatie\Permission\Models\Role;

class UserController extends Controller implements HasMiddleware
{
    public static function middleware(): array
    {
        return [
            new Middleware('permission:kelola-pengguna'),
        ];
    }

    public function index(Request $request): View
    {
        $users = User::query()
            ->with('roles')
            ->when($request->search, function ($query, $search) {
                return $query->where(function ($q) use ($search) {
                    $q->where('name', 'like', "%{$search}%")
                        ->orWhere('email', 'like', "%{$search}%");
                });
            })
            ->when($request->role, fn ($query, $role) => $query->role($role))
            ->orderBy('name')
            ->paginate(10)
            ->withQueryString();

        $roles = Role::orderBy('name')->pluck('name');

        return view('admin.users.index', compact('users', 'roles'));
    }

    public function updateRole(Request $request, User $user): RedirectResponse
    {
        $data = $request->validate([
            'role' => ['required', Rule::exists('roles', 'name')],
        ]);

        // Admin tidak boleh menurunkan perannya sendiri agar tidak terkunci.
        if ($user->is($request->user()) && $data['role'] !== 'admin') {
            return back()->with('error', 'Anda tidak dapat mengubah peran akun Anda sendiri.');
        }

        $user->syncRoles([$data['role']]);

        return back()->with('success', "Peran {$user->name} diubah menjadi {$data['role']}.");
    }
}
