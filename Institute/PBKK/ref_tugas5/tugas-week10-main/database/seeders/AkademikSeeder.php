<?php

namespace Database\Seeders;

use App\Models\Departemen;
use App\Models\Dosen;
use App\Models\Mahasiswa;
use App\Models\Tugas;
use Illuminate\Database\Seeder;

class AkademikSeeder extends Seeder
{
    public function run(): void
    {
        $daftarDepartemen = [
            ['kode' => 'IF', 'nama' => 'Teknik Informatika'],
            ['kode' => 'SI', 'nama' => 'Sistem Informasi'],
            ['kode' => 'TE', 'nama' => 'Teknik Elektro'],
            ['kode' => 'TK', 'nama' => 'Teknik Komputer'],
            ['kode' => 'TB', 'nama' => 'Teknik Biomedik'],
            ['kode' => 'IT', 'nama' => 'Teknologi Informasi'],
        ];

        foreach ($daftarDepartemen as $data) {
            $departemen = Departemen::firstOrCreate(['kode' => $data['kode']], $data);

            $dosen = Dosen::factory(4)->for($departemen)->create();

            Mahasiswa::factory(15)->for($departemen)->create();

            foreach ($dosen as $pengampu) {
                Tugas::factory(fake()->numberBetween(1, 3))
                    ->for($departemen)
                    ->for($pengampu)
                    ->create();
            }
        }
    }
}
