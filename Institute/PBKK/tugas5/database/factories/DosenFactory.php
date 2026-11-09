<?php

namespace Database\Factories;

use App\Models\Departemen;
use Illuminate\Database\Eloquent\Factories\Factory;

/**
 * @extends Factory<\App\Models\Dosen>
 */
class DosenFactory extends Factory
{
    public function definition(): array
    {
        return [
            'nip' => fake()->unique()->numerify('19##########'),
            'nama' => fake()->name(),
            'email' => fake()->unique()->safeEmail(),
            'departemen_id' => Departemen::factory(),
        ];
    }
}
