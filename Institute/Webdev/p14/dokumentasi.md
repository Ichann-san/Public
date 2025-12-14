# Sistem User Management
 
## Alur Kerja

1. Menyiapkan Database, Tabel User, dan Koneksi

declare.sql
Berfungsi membuat database multi_user beserta tabel user. Kolom level dipakai untuk menyimpan jenis hak akses (admin, pegawai, pengurus).

koneksi.php
File ini memastikan aplikasi terhubung ke database multi_user melalui mysqli_connect().

2. Membuat Tampilan Login dan Style (index.php & style.css)

index.php
Menyediakan form login berisi input username dan password. Form mengirim data ke cek_login.php lewat metode POST.
Jika URL mengandung ?pesan=gagal, halaman menampilkan pesan bahwa login tidak valid.

style.css
Mengatur tampilan agar form login terlihat rapi dan berada di tengah halaman.

3. Logika Validasi Login dan Penentuan Hak Akses (cek_login.php)

cek_login.php

Menerima input username dan password dari form.

Mengaktifkan session dengan session_start().

Mengeksekusi query SELECT * FROM user WHERE username='...' AND password='...' untuk pengecekan data.

Jika data cocok:

Mengambil data user dengan mysqli_fetch_assoc().

Mengevaluasi nilai level menggunakan if/else if.

Menyimpan username dan level ke dalam session.

Mengarahkan user ke dashboard sesuai levelnya.

Jika tidak cocok: redirect ke index.php?pesan=gagal.

4. Halaman Dashboard untuk Tiap Level Pengguna

halaman_admin.php, halaman_pegawai.php, halaman_pengurus.php
Masing-masing halaman menjadi dashboard sesuai role pengguna.
Di awal file terdapat pengecekan session $_SESSION['level']; jika belum terisi, pengguna dikembalikan ke halaman login.
Halaman menampilkan informasi pengguna yang login dan menyediakan tombol logout.

5. Proses Logout dan Penghapusan Session (logout.php)

logout.php
Menjalankan session_destroy() untuk menghapus semua data session dan mengembalikan pengguna ke halaman login (index.php).



# Tampilan Login
![](/Pertemuan14/imgs/index.png)

# Admin
![](/Pertemuan14/imgs/admin.png)

# Pengurus
![](/Pertemuan14/imgs/pengurus.png)

# Pegawai
![](/Pertemuan14/imgs/pegawai.png)