# Minggu Ke-15 – Implementasi Laporan PDF Menggunakan PHP & FPDF

Pada tugas ini, saya mengimplementasikan pembuatan laporan dalam bentuk
PDF menggunakan bahasa pemrograman PHP dan database MySQL. Laporan merupakan
fitur penting dalam aplikasi berbasis web karena berfungsi untuk mengekspor data
ke format yang mudah dibaca dan dapat disimpan oleh pengguna. Format PDF dipilih
karena sifatnya yang universal, rapi, dan tidak mudah berubah ketika dibuka di
perangkat yang berbeda.

**1. Tujuan Pembelajaran**
Tugas ini bertujuan untuk:
- Memahami cara mengambil data dari database MySQL menggunakan PHP.
- Mempraktikkan penggunaan library FPDF untuk menghasilkan dokumen PDF.
- Membuat tampilan antarmuka yang sederhana namun informatif sebagai halaman
  utama sebelum pengguna mengunduh laporan.
- Menghubungkan antara UI (HTML) dan fitur backend (PDF generator).

**2. Deskripsi Singkat Proyek**
Project ini terdiri dari dua bagian utama:

a. Halaman utama (index.php)
Halaman ini menampilkan data mahasiswa dari database secara langsung dalam bentuk
tabel. Antarmuka dibuat dengan nuansa warna pink agar lebih lembut dan nyaman
dilihat, tanpa mengurangi keterbacaan data. Pada halaman ini juga terdapat tombol
untuk men-download laporan PDF.

b. Generator PDF (laporanpdf.php)
File ini memanfaatkan library FPDF untuk menghasilkan file PDF berisi daftar
mahasiswa. Beberapa elemen diatur secara manual seperti ukuran halaman, jenis
font, header laporan, dan tabel data. Header laporan diberikan sentuhan warna
pink pastel sebagai identitas visual dari tugas ini.

**3. Teknologi yang Digunakan**
- **PHP** untuk backend processing.
- **MySQL** sebagai penyimpanan data.
- **FPDF** sebagai library untuk membuat file PDF.
- **HTML + CSS** untuk tampilan halaman utama.
- **XAMPP** sebagai web server lokal.

**4. Alur Kerja Sistem**
1. Pengguna membuka halaman utama.
2. Sistem menampilkan data mahasiswa dari tabel `mahasiswa`.
3. Jika tombol “Unduh PDF” ditekan, pengguna akan diarahkan ke file
   `laporanpdf.php`.
4. File tersebut memproses data dari database dan membangkitkan dokumen PDF.
5. PDF dikirim ke browser dan dapat diunduh oleh pengguna.

**5. Struktur Folder**
```
/
|-- index.php
|-- laporanpdf.php
|-- koneksi.php
|-- fpdf/
|-- assets/
```
