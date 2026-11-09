<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\BelongsTo;
use Illuminate\Database\Eloquent\Relations\HasMany;

class Dosen extends Model
{
    use HasFactory;

    protected $table = 'dosen';

    protected $fillable = ['nip', 'nama', 'email', 'departemen_id'];

    public function departemen(): BelongsTo
    {
        return $this->belongsTo(Departemen::class);
    }

    public function tugas(): HasMany
    {
        return $this->hasMany(Tugas::class);
    }
}
