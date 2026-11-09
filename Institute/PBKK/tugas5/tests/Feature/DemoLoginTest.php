<?php

namespace Tests\Feature;

use Database\Seeders\RoleAndPermissionSeeder;
use Database\Seeders\UserSeeder;
use Illuminate\Foundation\Testing\RefreshDatabase;
use Tests\TestCase;

class DemoLoginTest extends TestCase
{
    use RefreshDatabase;

    protected function setUp(): void
    {
        parent::setUp();

        $this->seed([RoleAndPermissionSeeder::class, UserSeeder::class]);
    }

    public function test_tombol_auto_login_admin(): void
    {
        config(['app.demo_login' => true]);

        $this->post('/demo-login/admin')->assertRedirect(route('dashboard'));
        $this->assertAuthenticatedAs(\App\Models\User::where('email', 'admin@its.ac.id')->first());
    }

    public function test_auto_login_nonaktif_jika_demo_login_false(): void
    {
        config(['app.demo_login' => false]);

        $this->post('/demo-login/admin')->assertNotFound();
        $this->assertGuest();
    }

    public function test_halaman_login_menampilkan_tombol_demo(): void
    {
        config(['app.demo_login' => true]);

        $this->get('/login')->assertOk()->assertSee('Masuk sebagai Admin');
    }
}
