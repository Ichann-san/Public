<?php
$host = "localhost"; 
$username = "root"; 
$password = "090307"; 
$database = "fotocrud"; 

// Koneksi ke MySQL dengan PDO
try {
    $pdo = new PDO('mysql:host=' . $host . ';dbname=' . $database, $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    echo "Koneksi gagal: " . $e->getMessage();
}
?>