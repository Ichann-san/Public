<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use Spatie\Permission\Models\Permission;
use Spatie\Permission\Models\Role;
use Spatie\Permission\PermissionRegistrar;

class RoleAndPermissionSeeder extends Seeder
{
    /**
     * Modul data yang dikelola di panel admin.
     */
    public const MODUL = ['mahasiswa', 'dosen', 'tugas'];

    public function run(): void
    {
        app()[PermissionRegistrar::class]->forgetCachedPermissions();

        // Izin umum.
        $izinUmum = ['akses-dashboard', 'kelola-pengguna'];

        // Izin per modul: lihat, tambah, edit, hapus.
        $izinModul = [];
        foreach (self::MODUL as $modul) {
            foreach (['lihat', 'tambah', 'edit', 'hapus'] as $aksi) {
                $izinModul[] = "{$aksi}-{$modul}";
            }
        }

        foreach (array_merge($izinUmum, $izinModul) as $nama) {
            Permission::firstOrCreate(['name' => $nama]);
        }

        // Admin: akses penuh.
        Role::firstOrCreate(['name' => 'admin'])
            ->syncPermissions(Permission::all());

        // Staf: akses terbatas (tanpa hapus data dan tanpa kelola pengguna).
        $izinStaf = collect($izinModul)
            ->reject(fn (string $izin) => str_starts_with($izin, 'hapus-'))
            ->push('akses-dashboard')
            ->all();

        Role::firstOrCreate(['name' => 'staf'])
            ->syncPermissions($izinStaf);

        // Mahasiswa: pengguna biasa, hanya beranda publik.
        Role::firstOrCreate(['name' => 'mahasiswa'])
            ->syncPermissions([]);
    }
}
