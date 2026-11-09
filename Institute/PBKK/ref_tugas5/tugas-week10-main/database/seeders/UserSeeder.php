<?php

namespace Database\Seeders;

use App\Models\User;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\Hash;

class UserSeeder extends Seeder
{
    /**
     * Akun uji coba untuk demo (dipakai juga oleh tombol auto-login).
     */
    public const AKUN_DEMO = [
        ['name' => 'Administrator', 'email' => 'admin@its.ac.id', 'role' => 'admin'],
        ['name' => 'Staf Akademik', 'email' => 'staf@its.ac.id', 'role' => 'staf'],
        ['name' => 'Mahasiswa Demo', 'email' => 'mahasiswa@its.ac.id', 'role' => 'mahasiswa'],
    ];

    public const PASSWORD_DEMO = 'password';

    public function run(): void
    {
        foreach (self::AKUN_DEMO as $akun) {
            $user = User::updateOrCreate(
                ['email' => $akun['email']],
                [
                    'name' => $akun['name'],
                    'password' => Hash::make(self::PASSWORD_DEMO),
                    'email_verified_at' => now(),
                ],
            );

            $user->syncRoles([$akun['role']]);
        }

        // Beberapa pengguna tambahan dengan peran staf dan mahasiswa.
        User::factory(3)->create()->each(fn (User $user) => $user->assignRole('staf'));
        User::factory(6)->create()->each(fn (User $user) => $user->assignRole('mahasiswa'));
    }
}
