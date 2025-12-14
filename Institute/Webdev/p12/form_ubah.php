<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ubah Data Siswa</title>
</head>
<body>
    <h1>Ubah Data Siswa</h1>
    <?php
    include "koneksi.php";

    $id = $_GET['id']; 
    $sql = $pdo->prepare("SELECT * FROM siswa WHERE id=:id");
    $sql->bindParam(':id', $id);
    $sql->execute(); 
    $data = $sql->fetch(); 

    ?>

    <form method="post" action="proses_ubah.php" enctype="multipart/form-data">
        <table cellpadding="8">
            <tr>
                <td>NIS</td>
                <td><input type="text" name="nis" value= "<?php echo $data['nis'];?>" ></td>
            </tr>
            <tr>
                <td>Nama</td>
                <td><input type="text" name="nama" value = "<?php echo $data['nama'];?>"></td>
            </tr>
            <tr>
                <td>Jenis Kelamin</td>
                <td>
                <?php
                    if ($data['jenis_kelamin'] == "Laki-laki") {
                        echo "<input type='radio' name='jenis_kelamin' value='Laki-laki' checked='checked'> Laki-laki ";
                        echo "<input type='radio' name='jenis_kelamin' value='Perempuan'> Perempuan";
                    } else {
                        echo "<input type='radio' name='jenis_kelamin' value='Laki-laki'> Laki-laki ";
                        echo "<input type='radio' name='jenis_kelamin' value='Perempuan' checked='checked'> Perempuan";
                    }
                    ?>
                </td>
            </tr>
            <tr>
                <td>Telepon</td>
                <td><input type="text" name="telp" value = "<?php echo $data['telp'];?>"></td>
            </tr>
            <tr>
                <td>Alamat</td>
                <td><textarea name="alamat" value = "<?php echo $data['alamat'];?>"></textarea></td>
            </tr>
            <tr>
                <td>Foto</td>
                <td><input type="file" name="foto"></td>
            </tr>
        </table>
        <hr>
        <input type="submit" value="Simpan">
        <a href="index.php"><input type="button" value="Batal"></a>
    </form>
</body>
</html>