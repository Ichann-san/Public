<?php

namespace Tests\Feature;

use Tests\TestCase;

class AssignmentRoutesTest extends TestCase
{
    public function test_home_page_can_be_opened(): void
    {
        $this->get('/')->assertOk()->assertSee('Arek ITS');
    }

    public function test_profile_accepts_exactly_ten_digit_nrp(): void
    {
        $this->get('/dashboard/mahasiswa/5025241001')
            ->assertOk()
            ->assertSee('5025241001');

        $this->get('/dashboard/mahasiswa/123')->assertNotFound();
        $this->get('/dashboard/mahasiswa/abcdefghij')->assertNotFound();
    }

    public function test_agent_uses_default_and_custom_theme(): void
    {
        $this->get('/dashboard/agent')->assertOk()->assertSee('General Assistant Agent');
        $this->get('/dashboard/agent/Education')->assertOk()->assertSee('Education');
    }

    public function test_ipk_calculator_returns_the_average(): void
    {
        $this->get('/dashboard/hitung-ipk/3.75/3.90')
            ->assertOk()
            ->assertSee('7.65')
            ->assertSee('3.83');
    }

    public function test_unknown_page_uses_the_fallback(): void
    {
        $this->get('/halaman-tidak-ada')
            ->assertNotFound()
            ->assertSee('Halaman tidak ditemukan');
    }
}
