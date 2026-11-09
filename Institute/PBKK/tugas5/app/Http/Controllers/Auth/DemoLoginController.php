<?php

namespace App\Http\Controllers\Auth;

use App\Http\Controllers\Controller;
use App\Models\User;
use Database\Seeders\UserSeeder;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class DemoLoginController extends Controller
{
    /**
     * Login instan menggunakan akun uji coba sesuai peran.
     */
    public function __invoke(Request $request, string $role): RedirectResponse
    {
        abort_unless(config('app.demo_login'), 404);

        $email = collect(UserSeeder::AKUN_DEMO)->firstWhere('role', $role)['email'] ?? null;
        $user = User::where('email', $email)->firstOrFail();

        Auth::login($user);
        $request->session()->regenerate();

        return redirect()->route('dashboard');
    }
}
