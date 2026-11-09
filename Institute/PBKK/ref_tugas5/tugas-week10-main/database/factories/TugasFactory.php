<?php

namespace Database\Factories;

use App\Models\Departemen;
use App\Models\Dosen;
use Illuminate\Database\Eloquent\Factories\Factory;

/**
 * @extends Factory<\App\Models\Tugas>
 */
class TugasFactory extends Factory
{
    public function definition(): array
    {
        $topik = fake()->randomElement([
            'Laporan Praktikum', 'Kuis', 'Proyek Akhir', 'Resume Jurnal',
            'Implementasi Algoritma', 'Desain Basis Data', 'Analisis Sistem', 'Presentasi',
        ]);

        return [
            'judul' => $topik.' '.fake()->numberBetween(1, 12),
            'deskripsi' => fake()->paragraph(),
            'deadline' => fake()->dateTimeBetween('-1 month', '+2 months'),
            'dosen_id' => Dosen::factory(),
            'departemen_id' => Departemen::factory(),
        ];
    }
}
