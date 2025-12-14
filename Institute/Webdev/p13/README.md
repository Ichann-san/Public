# Dokumentasi Aplikasi CRUD Data Siswa dengan Upload Gambar

## 📋 Deskripsi Proyek

Aplikasi ini merupakan sistem manajemen data siswa berbasis web yang dibangun menggunakan **PHP** dan **MySQL**. Aplikasi ini memungkinkan pengguna untuk melakukan operasi CRUD (Create, Read, Update, Delete) pada data siswa, termasuk fitur upload foto siswa.

---

## 🏗️ Arsitektur Sistem

### Struktur File

```
p12/
├── index.php           # Halaman utama - menampilkan daftar siswa
├── koneksi.php         # Konfigurasi koneksi database (PDO)
├── form_simpan.php     # Form input data siswa baru
├── proses_simpan.php   # Proses penyimpanan data ke database
├── form_ubah.php       # Form edit data siswa
├── proses_ubah.php     # Proses update data di database
├── proses_hapus.php    # Proses hapus data dari database
├── db.sql              # Script SQL untuk membuat tabel
└── images/             # Folder penyimpanan foto siswa
```

### Diagram Arsitektur

```
┌─────────────────────────────────────────────────────────────────┐
│                         BROWSER (Client)                         │
└─────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                      APACHE WEB SERVER                           │
│                        (XAMPP/Laragon)                           │
└─────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                        PHP APPLICATION                           │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────────────┐   │
│  │  index.php   │  │ form_*.php   │  │   proses_*.php       │   │
│  │  (READ)      │  │ (UI Forms)   │  │ (CREATE/UPDATE/DEL)  │   │
│  └──────────────┘  └──────────────┘  └──────────────────────┘   │
│                            │                                     │
│                            ▼                                     │
│                    ┌──────────────┐                              │
│                    │ koneksi.php  │                              │
│                    │    (PDO)     │                              │
│                    └──────────────┘                              │
└─────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                     MySQL DATABASE                               │
│                    Database: fotocrud                            │
│                    Tabel: siswa                                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 🔄 Workflow Detail

### 1. READ - Menampilkan Data (index.php)

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   Browser   │────▶│  index.php  │────▶│ koneksi.php │────▶│   MySQL     │
│  Request    │     │             │     │    (PDO)    │     │  Database   │
└─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘
                           │                                       │
                           │◀──────────────────────────────────────┘
                           │         Data Array (fetch)
                           ▼
                    ┌─────────────┐
                    │ HTML Table  │
                    │  + Images   │
                    └─────────────┘
```

**Alur Proses:**
1. User mengakses `index.php` melalui browser
2. PHP melakukan koneksi ke database via `koneksi.php`
3. Eksekusi query: `SELECT * FROM siswa`
4. Data diambil menggunakan method `fetch()` dalam loop `while`
5. Data ditampilkan dalam format tabel HTML dengan foto

---

### 2. CREATE - Menambah Data Baru

```
┌─────────────┐     ┌────────────────┐     ┌─────────────────┐
│   Browser   │────▶│ form_simpan.php│────▶│  HTML Form      │
│   (User)    │     │                │     │  + File Upload  │
└─────────────┘     └────────────────┘     └─────────────────┘
                                                   │
                                                   │ POST + FILES
                                                   ▼
┌─────────────┐     ┌────────────────┐     ┌─────────────────┐
│   index.php │◀────│proses_simpan.php│◀───│  Form Submit    │
│  (Redirect) │     │                │     │                 │
└─────────────┘     └────────────────┘     └─────────────────┘
                           │
                           ▼
                    ┌─────────────────────────────────────┐
                    │         PROSES:                     │
                    │  1. Ambil data $_POST & $_FILES     │
                    │  2. Generate nama file unik         │
                    │     (timestamp + nama asli)         │
                    │  3. move_uploaded_file() ke /images │
                    │  4. INSERT INTO siswa (PDO)         │
                    │  5. Redirect ke index.php           │
                    └─────────────────────────────────────┘
```

**Alur Proses:**
1. User klik "Tambah Data" → diarahkan ke `form_simpan.php`
2. User mengisi form (NIS, Nama, Jenis Kelamin, Telepon, Alamat, Foto)
3. Form disubmit dengan method POST dan `enctype="multipart/form-data"`
4. `proses_simpan.php` menerima data:
   - Data teks: `$_POST['field_name']`
   - File foto: `$_FILES['foto']`
5. Nama file dibuat unik: `date('dmYHis') + nama_asli`
6. File dipindahkan ke folder `/images/`
7. Data disimpan ke database dengan prepared statement (PDO)
8. Redirect ke `index.php`

---

### 3. UPDATE - Mengubah Data

```
┌─────────────┐     ┌────────────────┐     ┌─────────────────┐
│   index.php │────▶│ form_ubah.php  │────▶│  Query GET id   │
│  (Klik Ubah)│     │   ?id=X        │     │  Tampil Data    │
└─────────────┘     └────────────────┘     └─────────────────┘
                                                   │
                                                   │ Form terisi data lama
                                                   ▼
┌─────────────┐     ┌────────────────┐     ┌─────────────────┐
│   index.php │◀────│ proses_ubah.php│◀───│  Form Submit    │
│  (Redirect) │     │    ?id=X       │     │  (POST + GET)   │
└─────────────┘     └────────────────┘     └─────────────────┘
                           │
                           ▼
                    ┌─────────────────────────────────────┐
                    │         PROSES:                     │
                    │  1. Cek apakah foto baru diupload   │
                    │                                     │
                    │  JIKA TIDAK ADA FOTO BARU:          │
                    │  → UPDATE tanpa kolom foto          │
                    │                                     │
                    │  JIKA ADA FOTO BARU:                │
                    │  → Hapus foto lama (unlink)         │
                    │  → Upload foto baru                 │
                    │  → UPDATE semua kolom               │
                    └─────────────────────────────────────┘
```

**Alur Proses:**
1. User klik "Ubah" pada baris data → `form_ubah.php?id=X`
2. Query mengambil data berdasarkan ID: `SELECT * FROM siswa WHERE id=:id`
3. Form ditampilkan dengan value dari data yang sudah ada
4. User mengedit data dan submit
5. `proses_ubah.php` memproses:
   - **Tanpa foto baru**: Update field teks saja
   - **Dengan foto baru**: Hapus foto lama, upload baru, update semua field
6. Redirect ke `index.php`

---

### 4. DELETE - Menghapus Data

```
┌─────────────┐     ┌─────────────────┐     ┌─────────────────┐
│   index.php │────▶│ proses_hapus.php│────▶│  Query GET id   │
│ (Klik Hapus)│     │     ?id=X       │     │                 │
└─────────────┘     └─────────────────┘     └─────────────────┘
                           │
                           ▼
                    ┌─────────────────────────────────────┐
                    │         PROSES:                     │
                    │  1. SELECT foto WHERE id=X          │
                    │  2. Hapus file foto (unlink)        │
                    │  3. DELETE FROM siswa WHERE id=X    │
                    │  4. Redirect ke index.php           │
                    └─────────────────────────────────────┘
                           │
                           ▼
                    ┌─────────────┐
                    │  index.php  │
                    │ (Data hilang)│
                    └─────────────┘
```

**Alur Proses:**
1. User klik "Hapus" → `proses_hapus.php?id=X`
2. Query mengambil nama foto: `SELECT foto FROM siswa WHERE id=:id`
3. File foto dihapus dari server: `unlink("images/" . $foto)`
4. Data dihapus dari database: `DELETE FROM siswa WHERE id=:id`
5. Redirect ke `index.php`

---

## 🗃️ Struktur Database

### Database: `fotocrud`

### Tabel: `siswa`

| Kolom | Tipe Data | Keterangan |
|-------|-----------|------------|
| `id` | INT(11) | Primary Key, Auto Increment |
| `nis` | VARCHAR(11) | Nomor Induk Siswa |
| `nama` | VARCHAR(50) | Nama lengkap siswa |
| `jenis_kelamin` | VARCHAR(10) | Laki-laki / Perempuan |
| `telp` | VARCHAR(15) | Nomor telepon |
| `alamat` | TEXT | Alamat lengkap |
| `foto` | VARCHAR(200) | Nama file foto |

### SQL Script

```sql
CREATE DATABASE fotocrud;
USE fotocrud;

CREATE TABLE `siswa` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `nis` VARCHAR(11) NOT NULL,
  `nama` VARCHAR(50) NOT NULL,
  `jenis_kelamin` VARCHAR(10) NOT NULL,
  `telp` VARCHAR(15) NOT NULL,
  `alamat` TEXT NOT NULL,
  `foto` VARCHAR(200) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
```

---

## 🔐 Teknologi & Keamanan

### Teknologi yang Digunakan

| Komponen | Teknologi |
|----------|-----------|
| Backend | PHP 7.x / 8.x |
| Database | MySQL / MariaDB |
| Database Driver | PDO (PHP Data Objects) |
| Web Server | Apache (XAMPP) |
| Frontend | HTML, CSS |

### Fitur Keamanan

1. **Prepared Statements (PDO)**
   - Mencegah SQL Injection
   - Parameter binding: `:nis`, `:nama`, dll.

2. **File Upload Handling**
   - Nama file unik dengan timestamp
   - Validasi tipe file dengan `accept="image/*"`

---

## 🚀 Cara Menjalankan

1. **Pastikan XAMPP aktif** (Apache & MySQL)

2. **Buat database** di phpMyAdmin:
   ```sql
   CREATE DATABASE fotocrud;
   ```

3. **Import tabel** menggunakan `db.sql`

4. **Konfigurasi koneksi** di `koneksi.php`:
   ```php
   $host = "localhost";
   $username = "root";
   $password = "";
   $database = "fotocrud";
   ```

5. **Buat folder images**:
   ```
   p12/images/
   ```

6. **Akses aplikasi**:
   ```
   http://localhost/p12/
   ```

---

## 📊 Diagram Alur Lengkap

```
                              ┌─────────────────┐
                              │    index.php    │
                              │  (Daftar Siswa) │
                              └────────┬────────┘
                                       │
            ┌──────────────────────────┼──────────────────────────┐
            │                          │                          │
            ▼                          ▼                          ▼
   ┌─────────────────┐       ┌─────────────────┐       ┌─────────────────┐
   │  form_simpan.php│       │  form_ubah.php  │       │ proses_hapus.php│
   │   (Tambah Data) │       │   (Edit Data)   │       │   (Hapus Data)  │
   └────────┬────────┘       └────────┬────────┘       └────────┬────────┘
            │                         │                          │
            ▼                         ▼                          │
   ┌─────────────────┐       ┌─────────────────┐                 │
   │proses_simpan.php│       │ proses_ubah.php │                 │
   │   INSERT INTO   │       │     UPDATE      │                 │
   └────────┬────────┘       └────────┬────────┘                 │
            │                         │                          │
            └──────────────────────────┴──────────────────────────┘
                                       │
                                       ▼
                              ┌─────────────────┐
                              │    index.php    │
                              │   (Refresh)     │
                              └─────────────────┘
```

---

## 📝 Catatan Penting

1. **Folder `images/`** harus memiliki permission write
2. **Koneksi PDO** lebih aman dibanding mysqli untuk prepared statements
3. **Timestamp pada nama file** mencegah overwrite file dengan nama sama
4. **Hapus file fisik** saat menghapus/mengubah data untuk menghemat storage

---
<img width="2816" height="1536" alt="Gemini_Generated_Image_4zvtnl4zvtnl4zvt" src="https://github.com/user-attachments/assets/03c7e53f-294a-4934-a822-10c4a3d6b5ec" />



*Dokumentasi ini dibuat untuk keperluan pembelajaran pengembangan web dengan PHP dan MySQL.*
