<?php
include 'koneksi.php';
$mahasiswa = mysqli_query($connect, "SELECT * FROM mahasiswa");
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Daftar Siswa Kelas XII RPL</title>
    <style>
        body {
            font-family: 'Poppins', sans-serif;
            background: #0d0d0d;
            margin: 0;
            padding: 30px;
        }

        .container {
            width: 800px;
            margin: auto;
            background: #1a1a1a;
            padding: 25px;
            border-radius: 12px;
            box-shadow: 0 0 30px rgba(0, 0, 0, 0.5);
            border: 1px solid #333;
        }

        h2 {
            text-align: center;
            color: #ffffff;
            margin-top: 0;
            font-size: 28px;
            font-weight: 600;
        }

        .btn {
            display: inline-block;
            background: #2a2a2a;
            color: #fff;
            padding: 12px 20px;
            border-radius: 8px;
            text-decoration: none;
            font-size: 15px;
            margin-bottom: 15px;
            font-weight: 500;
            transition: 0.2s;
            border: 1px solid #444;
        }

        .btn:hover {
            background: #3a3a3a;
            transform: scale(1.05);
            border-color: #666;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
            border-radius: 10px;
            overflow: hidden;
        }

        th {
            background: #222;
            color: #fff;
            padding: 12px;
            font-size: 15px;
            border-bottom: 2px solid #444;
        }

        td {
            padding: 12px;
            background: #1a1a1a;
            border-bottom: 1px solid #333;
            font-size: 14px;
            text-align: center;
            color: #ccc;
        }

        tr:hover td {
            background: #252525;
        }
    </style>
</head>
<body>
<div class="container">
    <h2>Daftar Siswa Kelas IX RPL - SMKN 2 Bangsa</h2>

    <a class="btn" href="laporanpdf.php" target="_blank">Unduh PDF</a>

    <table>
        <tr>
            <th>NIM</th>
            <th>Nama Lengkap</th>
            <th>Tanggal Lahir</th>
            <th>No HP</th>
        </tr>
        <?php while($row = mysqli_fetch_array($mahasiswa)): ?>
        <tr>
            <td><?= $row['nim']; ?></td>
            <td><?= $row['nama_lengkap']; ?></td>
            <td><?= $row['tanggal_lahir']; ?></td>
            <td><?= $row['no_hp']; ?></td>
        </tr>
        <?php endwhile; ?>
    </table>
</div>
</body>
</html>