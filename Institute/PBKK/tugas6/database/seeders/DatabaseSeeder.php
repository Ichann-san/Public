<?php

namespace Database\Seeders;

use App\Models\User;
use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    public function run(): void
    {
        if (app()->environment('local', 'testing')) {
            User::firstOrCreate(['email' => 'maulana@its.ac.id'], [
                'name' => 'Maulana',
                'password' => 'password',
                'email_verified_at' => now(),
            ]);
        }
    }
}
