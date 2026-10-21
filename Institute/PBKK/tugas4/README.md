# Tugas 4 — Profil Akademik Multi-View

Mini-website Laravel untuk profil mahasiswa ITS, rancangan platform Agentic AI kelompok, dan formulir pengumpulan ide. Tampilan mengikuti arah visual `../tugas2/web.php`: navbar putih, aksen indigo, badge lembut, kartu berbayang, dan footer ITS. Struktur halaman kini memakai Blade dan CSS Tailwind yang dibundel secara lokal oleh Vite.

## Kebutuhan

- PHP 8.3 atau lebih baru dan Composer
- Node.js dan NPM (gunakan versi Node yang mendukung Vite 8)

## Menjalankan proyek

```powershell
composer install
Copy-Item .env.example .env
php artisan key:generate
npm install
```

Buka dua terminal di direktori `tugas4`:

```powershell
php artisan serve
```

```powershell
npm run dev
```

Lalu buka alamat yang ditampilkan oleh `php artisan serve` (biasanya `http://127.0.0.1:8000`). Untuk build aset produksi, jalankan `npm run build` sebagai pengganti server Vite. Proyek ini belum memerlukan migrasi database.

## Halaman dan rute

| Metode | URL | Nama rute | Fungsi |
| --- | --- | --- | --- |
| GET | `/` | `home` | Beranda utama |
| GET | `/beranda` | `beranda` | Alias beranda untuk challenge parameter `user` |
| GET | `/profil-mahasiswa` | `profile` | Profil mahasiswa |
| GET | `/ide-agent` | `ideas` | Konsep Agentic AI dan formulir ide |
| POST | `/ide-agent` | `ideas.store` | Validasi formulir dan tampilkan status |

Semua rute ditangani oleh `app/Http/Controllers/PageController.php`. Tiga halaman anak berada di `resources/views/pages` dan menggunakan `@extends('layouts.app')`. Struktur HTML, judul dinamis, navbar, container, pemanggilan `@vite`, serta footer ITS hanya ada di `resources/views/layouts/app.blade.php`.

Komponen `resources/views/components/info-card.blade.php` menerima prop `label` dan slot isi untuk data profil. Komponen `status-banner.blade.php` menerima prop `tone`, slot pesan, serta atribut HTML tambahan; dipakai untuk sambutan dan konfirmasi formulir.

## Challenge dan demo singkat

1. Buka `/beranda?user=Andi` untuk melihat sambutan dinamis. Nilai `user` dibatasi panjangnya dan Blade melakukan escape HTML.
2. Buka `/ide-agent?mode=dark` untuk melihat mode gelap. `PageController` mengirim variabel `$isDarkMode` ke layout; layout memilih kelas Tailwind sesuai nilainya. Tombol mode pada halaman juga dapat dipakai.
3. Isi dan kirim formulir di `/ide-agent`. Input divalidasi, lalu komponen status menampilkan konfirmasi. Data **belum disimpan** karena integrasi database adalah materi pertemuan berikutnya. Validasi gagal mengembalikan kesalahan dan nilai input lama.

Contoh alur live demo 3 menit: tunjukkan ketiga halaman, buka dua URL challenge di atas, kirim contoh ide, lalu perlihatkan `routes/web.php`, layout, dua komponen, dan `vite.config.js`.

## Verifikasi

```powershell
php artisan route:list --except-vendor
php artisan test --compact
npm run build
```

## Pengumpulan

Unggah source code proyek ke repositori GitHub pribadi dan kirim tautannya ke LMS ITS sebelum H-1 perkuliahan berikutnya. `.gitignore` sudah mengecualikan `.env`, `vendor/`, `node_modules/`, serta build lokal. Jangan unggah rahasia aplikasi. File `composer.lock` dan `package-lock.json` perlu ikut diunggah agar instalasi dapat diulang.
