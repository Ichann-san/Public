<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\BelongsTo;

class Mahasiswa extends Model
{
    use HasFactory;

    protected $table = 'mahasiswa';

    protected $fillable = ['nrp', 'nama', 'email', 'angkatan', 'is_active', 'departemen_id'];

    protected function casts(): array
    {
        return [
            'is_active' => 'boolean',
            'angkatan' => 'integer',
        ];
    }

    public function departemen(): BelongsTo
    {
        return $this->belongsTo(Departemen::class);
    }
}
