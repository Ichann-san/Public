# Tugas 2 Routing Design

## Tujuan

Membuat sandbox routing Laravel paling sederhana untuk menampilkan profil akademis,
ide Agentic AI, kalkulator IPK dua semester, dan halaman 404.

## Keputusan

- Seluruh implementasi berada di `tugas2/web.php` menggunakan route closure.
- Halaman utama berada di `/`; fitur akademis dikelompokkan di bawah `/dashboard`.
- Semua route memiliki nama agar tautan internal dibuat dengan `route()`.
- NRP dibatasi tepat 10 digit menggunakan `where()`.
- Tampilan memakai satu helper HTML bersama dengan gaya Bootstrap/Inter bernuansa
  indigo yang diadaptasi dari `college/fp_pweb`.
- Tidak ditambahkan controller, Blade view, database, autentikasi, atau dependency baru.

## Kriteria Selesai

Semua route tugas terdaftar, navigasi memakai named route, perhitungan rata-rata
benar, tema agent memiliki fallback, NRP non-10-digit ditolak, dan URL lain
ditangani fallback 404.
