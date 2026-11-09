<?php

namespace Tests\Feature;

use App\Models\Departemen;
use App\Models\Mahasiswa;
use App\Models\Tugas;
use App\Models\User;
use Database\Seeders\RoleAndPermissionSeeder;
use Illuminate\Foundation\Testing\RefreshDatabase;
use Tests\TestCase;

class RbacTest extends TestCase
{
    use RefreshDatabase;

    protected function setUp(): void
    {
        parent::setUp();

        $this->seed(RoleAndPermissionSeeder::class);
    }

    private function userWithRole(string $role): User
    {
        return User::factory()->create()->assignRole($role);
    }

    public function test_admin_diarahkan_ke_dashboard_admin_setelah_login(): void
    {
        $admin = $this->userWithRole('admin');

        $this->post('/login', ['email' => $admin->email, 'password' => 'password'])
            ->assertRedirect(route('admin.dashboard', absolute: false));
    }

    public function test_staf_diarahkan_ke_dashboard_admin_setelah_login(): void
    {
        $staf = $this->userWithRole('staf');

        $this->post('/login', ['email' => $staf->email, 'password' => 'password'])
            ->assertRedirect(route('admin.dashboard', absolute: false));
    }

    public function test_mahasiswa_diarahkan_ke_beranda_publik_setelah_login(): void
    {
        $mahasiswa = $this->userWithRole('mahasiswa');

        $this->post('/login', ['email' => $mahasiswa->email, 'password' => 'password'])
            ->assertRedirect(route('home', absolute: false));
    }

    public function test_tamu_tidak_bisa_membuka_dashboard_admin(): void
    {
        $this->get('/admin/dashboard')->assertRedirect('/login');
    }

    public function test_mahasiswa_tidak_bisa_bypass_url_dashboard_admin(): void
    {
        $this->actingAs($this->userWithRole('mahasiswa'))
            ->get('/admin/dashboard')
            ->assertForbidden();
    }

    public function test_dashboard_menampilkan_widget_statistik(): void
    {
        Mahasiswa::factory(3)->create();
        Tugas::factory()->create(['deadline' => now()->addDay()]);
        Tugas::factory()->create(['deadline' => now()->subDay()]);

        $this->actingAs($this->userWithRole('admin'))
            ->get('/admin/dashboard')
            ->assertOk()
            ->assertSee('Total Mahasiswa')
            ->assertSee('Total Staf Dosen')
            ->assertSee('Total Tugas Aktif')
            ->assertViewHas('statistik', fn ($s) => $s['mahasiswa'] === 3 && $s['tugas_aktif'] === 1);
    }

    public function test_tombol_hapus_hanya_tampil_untuk_admin(): void
    {
        Mahasiswa::factory()->create();

        $this->actingAs($this->userWithRole('admin'))
            ->get('/admin/mahasiswa')
            ->assertOk()
            ->assertSee('bi bi-trash', false);

        $this->actingAs($this->userWithRole('staf'))
            ->get('/admin/mahasiswa')
            ->assertOk()
            ->assertDontSee('bi bi-trash', false);
    }

    public function test_staf_tidak_bisa_menghapus_data_lewat_request_manual(): void
    {
        $mahasiswa = Mahasiswa::factory()->create();

        $this->actingAs($this->userWithRole('staf'))
            ->delete(route('admin.mahasiswa.destroy', $mahasiswa))
            ->assertForbidden();

        $this->assertModelExists($mahasiswa);
    }

    public function test_admin_bisa_menghapus_data(): void
    {
        $mahasiswa = Mahasiswa::factory()->create();

        $this->actingAs($this->userWithRole('admin'))
            ->from('/admin/mahasiswa')
            ->delete(route('admin.mahasiswa.destroy', $mahasiswa))
            ->assertRedirect('/admin/mahasiswa');

        $this->assertModelMissing($mahasiswa);
    }

    public function test_staf_bisa_menambah_data(): void
    {
        $departemen = Departemen::factory()->create();

        $this->actingAs($this->userWithRole('staf'))
            ->post(route('admin.mahasiswa.store'), [
                'nrp' => '5025231001',
                'nama' => 'Budi Santoso',
                'email' => 'budi@example.com',
                'angkatan' => 2023,
                'departemen_id' => $departemen->id,
                'is_active' => '1',
            ])
            ->assertRedirect(route('admin.mahasiswa.index'));

        $this->assertDatabaseHas('mahasiswa', ['nrp' => '5025231001']);
    }

    public function test_staf_tidak_bisa_mengelola_pengguna(): void
    {
        $this->actingAs($this->userWithRole('staf'))
            ->get('/admin/users')
            ->assertForbidden();
    }

    public function test_admin_bisa_mengubah_peran_pengguna(): void
    {
        $user = $this->userWithRole('mahasiswa');

        $this->actingAs($this->userWithRole('admin'))
            ->put(route('admin.users.role', $user), ['role' => 'staf'])
            ->assertRedirect();

        $this->assertTrue($user->fresh()->hasRole('staf'));
    }

    public function test_pencarian_when_dan_pagination_mempertahankan_filter(): void
    {
        $dept = Departemen::factory()->create();
        Mahasiswa::factory(15)->for($dept)->create(['nama' => 'Andi Pratama']);
        Mahasiswa::factory(5)->create(['nama' => 'Siti Rahma']);

        $response = $this->actingAs($this->userWithRole('admin'))
            ->get('/admin/mahasiswa?search=Andi&departemen_id='.$dept->id);

        $response->assertOk()
            ->assertSee('Andi Pratama')
            ->assertDontSee('Siti Rahma')
            ->assertViewHas('mahasiswa', fn ($p) => $p->total() === 15);

        // Link halaman 2 tetap membawa parameter filter (withQueryString).
        $response->assertSee('search=Andi', false)
            ->assertSee('departemen_id='.$dept->id, false);
    }

    public function test_pencarian_berdasarkan_nrp(): void
    {
        Mahasiswa::factory()->create(['nrp' => '5025999999', 'nama' => 'Target']);
        Mahasiswa::factory()->create(['nama' => 'Lainnya']);

        $this->actingAs($this->userWithRole('admin'))
            ->get('/admin/mahasiswa?search=5025999999')
            ->assertSee('Target')
            ->assertDontSee('Lainnya');
    }
}
