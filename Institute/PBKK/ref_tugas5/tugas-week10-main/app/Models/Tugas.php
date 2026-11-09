<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Builder;
use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\BelongsTo;

class Tugas extends Model
{
    use HasFactory;

    protected $table = 'tugas';

    protected $fillable = ['judul', 'deskripsi', 'deadline', 'dosen_id', 'departemen_id'];

    protected function casts(): array
    {
        return [
            'deadline' => 'datetime',
        ];
    }

    /**
     * Tugas yang belum melewati tenggat waktu.
     */
    public function scopeAktif(Builder $query): Builder
    {
        return $query->where('deadline', '>=', now());
    }

    public function dosen(): BelongsTo
    {
        return $this->belongsTo(Dosen::class);
    }

    public function departemen(): BelongsTo
    {
        return $this->belongsTo(Departemen::class);
    }
}
