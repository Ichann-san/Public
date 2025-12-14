<?php
require('fpdf.php');
include 'koneksi.php';

class PDF extends FPDF
{
    function Header()
    {
        // Dark header background
        $this->SetFillColor(34, 34, 34); // dark gray
        $this->Rect(0, 0, 210, 25, 'F');

        // Title
        $this->SetFont('Helvetica', 'B', 16);
        $this->SetTextColor(255, 255, 255);
        $this->Cell(0, 12, 'Laporan Data Siswa', 0, 1, 'C');

        $this->Ln(8);
    }

    function Footer()
    {
        $this->SetY(-15);
        $this->SetTextColor(120, 120, 120);
        $this->SetFont('Helvetica', 'I', 10);
        $this->Cell(0, 10, 'Halaman '.$this->PageNo(), 0, 0, 'C');
    }
}

$pdf = new PDF();
$pdf->AddPage();
$pdf->SetFont('Helvetica', 'B', 12);

// Header Tabel
$pdf->SetFillColor(34, 34, 34);
$pdf->SetTextColor(255, 255, 255);
$pdf->Cell(40, 10, 'NIM', 1, 0, 'C', true);
$pdf->Cell(60, 10, 'Nama Lengkap', 1, 0, 'C', true);
$pdf->Cell(40, 10, 'Tgl Lahir', 1, 0, 'C', true);
$pdf->Cell(40, 10, 'No HP', 1, 1, 'C', true);

// Isi Tabel
include 'koneksi.php';
$data = mysqli_query($connect, "SELECT * FROM mahasiswa");

$pdf->SetFont('Helvetica', '', 11);
$pdf->SetTextColor(0, 0, 0);

while ($row = mysqli_fetch_array($data)) {
    $pdf->Cell(40, 10, $row['nim'], 1, 0, 'C');
    $pdf->Cell(60, 10, $row['nama_lengkap'], 1, 0, 'C');
    $pdf->Cell(40, 10, $row['tanggal_lahir'], 1, 0, 'C');
    $pdf->Cell(40, 10, $row['no_hp'], 1, 1, 'C');
}

$pdf->Output();
?>