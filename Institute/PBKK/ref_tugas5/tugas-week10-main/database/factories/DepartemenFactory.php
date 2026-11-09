<?php

namespace Database\Factories;

use Illuminate\Database\Eloquent\Factories\Factory;

/**
 * @extends Factory<\App\Models\Departemen>
 */
class DepartemenFactory extends Factory
{
    public function definition(): array
    {
        return [
            'kode' => fake()->unique()->bothify('D??#'),
            'nama' => 'Departemen '.fake()->unique()->word(),
        ];
    }
}
