<?php

namespace Database\Factories;

use App\Models\Departemen;
use Illuminate\Database\Eloquent\Factories\Factory;

/**
 * @extends Factory<\App\Models\Mahasiswa>
 */
class MahasiswaFactory extends Factory
{
    public function definition(): array
    {
        $angkatan = fake()->numberBetween(2021, 2025);

        return [
            'nrp' => '50'.substr((string) $angkatan, 2).fake()->unique()->numerify('1######'),
            'nama' => fake()->name(),
            'email' => fake()->unique()->safeEmail(),
            'angkatan' => $angkatan,
            'is_active' => fake()->boolean(85),
            'departemen_id' => Departemen::factory(),
        ];
    }
}
