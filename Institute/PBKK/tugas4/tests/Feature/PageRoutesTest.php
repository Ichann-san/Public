<?php

namespace Tests\Feature;

use Tests\TestCase;

class PageRoutesTest extends TestCase
{
    public function test_the_three_pages_and_beranda_alias_render_from_the_page_controller(): void
    {
        $this->get('/')->assertOk()->assertSee('Arek ITS!');
        $this->get('/beranda')->assertOk()->assertSee('Arek ITS!');
        $this->get('/profil-mahasiswa')->assertOk()->assertSee('5025241001');
        $this->get('/ide-agent')->assertOk()->assertSee('StudyFlow');
    }

    public function test_welcome_name_is_dynamic_and_escaped(): void
    {
        $this->get('/beranda?user=Andi')->assertOk()->assertSee('Selamat datang, <strong>Andi</strong>!', false);
        $this->get('/beranda?user=%3Cscript%3Ealert(1)%3C%2Fscript%3E')
            ->assertOk()
            ->assertDontSee('<script>alert(1)</script>', false);
    }

    public function test_dark_mode_only_applies_to_the_requested_idea_page(): void
    {
        $this->get('/ide-agent?mode=dark')->assertOk()->assertSee('theme-dark bg-slate-950', false);
        $this->get('/ide-agent')->assertOk()->assertDontSee('theme-dark bg-slate-950', false);
    }

    public function test_idea_submission_validates_input_and_shows_a_status(): void
    {
        $this->from('/ide-agent?mode=dark')->post('/ide-agent', [
            'name' => 'Andi',
            'idea' => 'Asisten belajar adaptif',
            'description' => 'Membantu menyusun rencana belajar mingguan.',
            'mode' => 'dark',
        ])->assertRedirect('/ide-agent?mode=dark')
            ->assertSessionHas('status');

        $this->from('/ide-agent')->post('/ide-agent', [
            'name' => '',
            'idea' => '',
            'description' => '',
        ])->assertRedirect('/ide-agent')
            ->assertSessionHasErrors(['name', 'idea', 'description']);
    }
}
