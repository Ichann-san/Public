<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sistem Autentikasi Multi Level - Portal Login</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
    <h1>Portal Autentikasi Pengguna</h1>
    <?php
        if(isset($_GET['pesan'])){
            if($_GET['pesan']=="gagal"){
                echo "<div class='alert'>Kredensial yang dimasukkan tidak valid!</div>";
            }
        }
    ?>
    <div class="kotak_login">
        <p class="tulisan_login">Masuk ke Akun Anda</p>
        <form action="cek_login.php" method="post">
            <label>Nama Pengguna</label>
            <input type="text" name="username" class="form_login"
                placeholder="Masukkan nama pengguna" required="required">
            <label>Kata Sandi</label>
            <input type="password" name="password" class="form_login"
                placeholder="Masukkan kata sandi" required="required">
            <input type="submit" class="tombol_login" value="MASUK">
            <br/>
            <br/>
            <center>
                <a class="link" href="#">Lupa kata sandi?</a>
            </center>
        </form>
    </div>
</body>
</html>