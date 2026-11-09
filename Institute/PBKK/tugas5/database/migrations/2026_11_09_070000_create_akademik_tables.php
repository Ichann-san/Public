<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class () extends Migration {
    /**
     * Membuat tabel data akademik: departemen, dosen, mahasiswa, dan tugas.
     */
    public function up(): void
    {
        Schema::create('departemen', function (Blueprint $table) {
            $table->id();
            $table->string('kode', 10)->unique();
            $table->string('nama');
            $table->timestamps();
        });

        Schema::create('dosen', function (Blueprint $table) {
            $table->id();
            $table->string('nip', 20)->unique();
            $table->string('nama')->index();
            $table->string('email')->unique();
            $table->foreignId('departemen_id')->constrained('departemen')->cascadeOnDelete();
            $table->timestamps();
        });

        Schema::create('mahasiswa', function (Blueprint $table) {
            $table->id();
            $table->string('nrp', 20)->unique();
            $table->string('nama')->index();
            $table->string('email')->unique();
            $table->unsignedSmallInteger('angkatan');
            $table->boolean('is_active')->default(true)->index();
            $table->foreignId('departemen_id')->constrained('departemen')->cascadeOnDelete();
            $table->timestamps();
        });

        Schema::create('tugas', function (Blueprint $table) {
            $table->id();
            $table->string('judul')->index();
            $table->text('deskripsi')->nullable();
            $table->dateTime('deadline')->index();
            $table->foreignId('dosen_id')->constrained('dosen')->cascadeOnDelete();
            $table->foreignId('departemen_id')->constrained('departemen')->cascadeOnDelete();
            $table->timestamps();
        });
    }

    public function down(): void
    {
        Schema::dropIfExists('tugas');
        Schema::dropIfExists('mahasiswa');
        Schema::dropIfExists('dosen');
        Schema::dropIfExists('departemen');
    }
};
