<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\HasMany;

class Departemen extends Model
{
    use HasFactory;

    protected $table = 'departemen';

    protected $fillable = ['kode', 'nama'];

    public function dosen(): HasMany
    {
        return $this->hasMany(Dosen::class);
    }

    public function mahasiswa(): HasMany
    {
        return $this->hasMany(Mahasiswa::class);
    }

    public function tugas(): HasMany
    {
        return $this->hasMany(Tugas::class);
    }
}
