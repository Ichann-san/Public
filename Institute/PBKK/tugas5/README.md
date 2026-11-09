# Tugas 5 PBKK - Portal Akademik ITS

Maulana - 5025241001

Portal akademik Laravel dengan dashboard AdminLTE, autentikasi Breeze, dan hak akses Spatie. Implementasi diadaptasi dari `../ref_tugas5/tugas-week10-main`; gaya indigo, panel membulat, dan identitas mengikuti proyek `../tugas4`.

## Menjalankan

Kebutuhan: PHP 8.2+ dengan ekstensi SQLite dan Composer.

```sh
composer run setup
composer run dev
```

Buka http://localhost:8005. Jika dependensi dan database sudah disiapkan, cukup jalankan `composer run dev` atau `php artisan serve --port=8005`.

Aset AdminLTE dan tema tersedia lokal di `public/`, sehingga Node/Vite tidak diperlukan untuk menjalankan aplikasi. Tema khusus berada di `public/css/portal.css`.

## Akun demo

| Peran | Email | Password | Hak akses |
| --- | --- | --- | --- |
| Admin | admin@its.ac.id | password | Seluruh data, hapus, dan manajemen peran |
| Staf | staf@its.ac.id | password | Dashboard, lihat, tambah, dan edit data |
| Mahasiswa | mahasiswa@its.ac.id | password | Beranda tugas aktif dan profil |

Tombol akun demo tersedia pada halaman login saat `DEMO_LOGIN=true`. Akun pendaftaran baru mendapat peran mahasiswa. Nama akun demo mahasiswa: Maulana.

## Fitur

- Login, daftar, reset password, dan profil.
- Dashboard berisi jumlah mahasiswa, dosen, tugas aktif, dan pengguna.
- CRUD mahasiswa, dosen, dan tugas; pencarian, filter, dan pagination.
- Tabel mahasiswa per departemen dan daftar tenggat terdekat.
- Pembatasan rute dan aksi di server: mahasiswa tidak dapat membuka panel; staf tidak dapat menghapus data atau mengatur peran.
- Tema terang/gelap, tata letak responsif, dan aset lokal.
- Seeder berisi 6 departemen, 24 dosen, 90 mahasiswa, tugas, dan akun demo.

Reset data demo (menghapus data lokal): `php artisan migrate:fresh --seed`.

## Pengujian

```sh
php artisan test
php artisan view:cache
```

Test bawaan referensi mencakup autentikasi, profil, pengalihan peran, penolakan akses, CRUD mahasiswa, filter/pagination, dan login demo.
