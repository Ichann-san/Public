# Belajar dari Soal ETS: Cara Mengenali Tugas dan Memilih Langkah

Pembahasan empat soal ETS 2025 kelas A dan C, ditambah enam contoh soal serupa. Sumber: file di dalam pemsimgoat.zip yang kamu kirim. Disusun untuk belajar dari dasar, dengan kalkulator dan penjelasan setiap langkah.

## Cara memakai pembahasan ini

Mulai dari satu soal utuh. Baca cerita soalnya, pahami hasil yang diminta, lalu ikuti tabel sampai akhir. Jangan membaca semua rumus sekaligus. Setelah satu soal selesai, tutup pembahasan dan coba tulis ulang urutan pekerjaannya dengan kalimat biasa. Tidak perlu mengetik jawaban panjang.

Kita memakai urutan A1, A2, C1, lalu C2. Setelah itu baru melihat variasi soal. Dokumen ini panjang karena semua pembahasan disimpan bersama; kamu cukup membuka satu bagian pada satu waktu.

Yang memang perlu diingat untuk closed book akan diberi nama sesuai tugasnya, misalnya “mengubah angka random menjadi waktu eksponensial”. Rumus antrean bisa dibangun kembali dari cerita: pelanggan harus sudah datang dan petugas harus sudah kosong. Rumus profit bisa dibangun dari arus uang: pendapatan dikurangi biaya.

## Empat soal yang akan kita bahas

| Soal | Cerita dan perintah | Pekerjaan utamanya |
|---|---|---|
| A nomor 1 | Job datang dan diproses; diminta simulasi serta ukuran waktu | Ubah angka random menjadi input, isi tabel antrean, rangkum hasil |
| A nomor 2 | Diberikan seed, a, c, m; diminta 50 angka dan pengujian | Jalankan LCG, periksa uniformity dan independence |
| C nomor 1 | Pelanggan membeli bagel; pilih jumlah produksi dari profit | Bangkitkan pelanggan dan pesanan, hitung demand, bandingkan profit |
| C nomor 2 | Lead time eksponensial rata-rata 3,7 hari; bangkitkan 10 nilai dan jelaskan uji | Inverse transform, kemudian goodness-of-fit |

### Dua pertanyaan sebelum mengambil rumus

1. Apakah angka random U sudah disediakan? Jika sudah, langsung gunakan. LCG diperlukan ketika soal meminta membangkitkan U dari seed dan parameter.
2. Soal meminta membuat nilai, menjalankan sistem, menguji data, atau membandingkan kebijakan? Perintah itulah yang menentukan langkah berikutnya.

Kata “eksponensial” sendiri belum menentukan semua pekerjaan. “Bangkitkan waktu eksponensial” memakai inverse transform. “Uji apakah data eksponensial” memakai pengujian kecocokan dengan CDF eksponensial.

## Aturan angka random untuk contoh numerik

Jawaban yang memakai tabel random tidak mempunyai satu hasil numerik yang sama untuk semua mahasiswa. Hasil bergantung pada kolom NRP, cara mengelompokkan digit, dan urutan pemakaian angka. Kita perlu menetapkan satu contoh yang bisa diperiksa ulang.

Dalam dokumen ini kolom 7 pada gambar Random Number.jpg dipakai sebagai contoh kerja. Deretan lima digit pada setiap baris disambung dari atas ke bawah, lalu dikelompokkan dua digit sekali baca. Contohnya:

58701 68558 53496 ... menjadi 58, 70, 16, 85, 58, 53, 49, ... sehingga U = 0,58; 0,70; 0,16; 0,85; dan seterusnya.

Ini merupakan satu konvensi pembacaan yang dinyatakan terbuka. Jika dosen menetapkan lima digit per angka atau aturan lain, gunakan aturan tersebut dan hasil hitungan akan berubah. Kolom 7 di sini adalah contoh, bukan penetapan digit NRP-mu.

Untuk setiap soal yang berbeda, pembacaan dimulai kembali dari awal. Di dalam satu soal, angka dikonsumsi berurutan. Untuk tabel diskrit kita memakai batas kiri termasuk dan batas kanan tidak termasuk, misalnya 0,40 ≤ U < 0,70. Ikuti aturan batas pada soal jika ditentukan berbeda.

Tiga puluh kelompok digit awal yang dipakai dari kolom 7 adalah:

58701 68558 53496 07471 99057 33456 42822 45390 54786 15016 20926 46439 57753 81421 78462 12282 50391 95878 82697 35712 82072 63099 03126 90527 39578 77869 88937 63966 47554 92600

Dua puluh U pertama: 0,58; 0,70; 0,16; 0,85; 0,58; 0,53; 0,49; 0,60; 0,74; 0,71; 0,99; 0,05; 0,73; 0,34; 0,56; 0,42; 0,82; 0,24; 0,53; 0,90. Perhitungan menyimpan digit penuh; angka pada tabel dibulatkan untuk dibaca.

## A1 — Antrean job-shop: dari cerita sampai jawaban

### A1.1 Apa isi soal aslinya?

Antarwaktu kedatangan job mempunyai kemungkinan 0, 1, 2, atau 3 jam, dengan peluang 0,23; 0,37; 0,28; dan 0,12. Waktu pemrosesan mengikuti distribusi eksponensial dengan rata-rata 50 menit. Saat simulasi dimulai, satu job mempunyai waktu proses 25 menit dan satu job lain sudah menunggu dengan kebutuhan proses 50 menit. Diminta simulasi dengan 10 job dan tiga hasil: rata-rata waktu tunggu, rata-rata total waktu proses per job, dan waktu tunggu maksimum.

### A1.2 Bagaimana mengenali pekerjaan yang diminta?

Ada kata kedatangan, job menunggu, dan waktu proses. Berarti ini cerita antrean. Hasil akhirnya harus datang dari tabel yang mengikuti perjalanan setiap job. Ada dua cara pembangkitan input karena distribusinya berbeda: tabel peluang untuk kedatangan, rumus eksponensial untuk pelayanan.

Tidak ada seed atau parameter generator yang harus dipakai pada nomor ini. Kita menggunakan angka random dari lampiran. Soal A2 yang akan memerlukan LCG.

### A1.3 Tentukan asumsi dan satuan sebelum menghitung

Kita memakai satu server dan FIFO. Semua jam kedatangan diubah menjadi menit. Job awal diproses 25 menit sejak t = 0; sesudahnya job yang sudah mengantre diproses 50 menit. Jadi dua job awal menempati server sampai menit 75.

Redaksi “dengan 10 job” dapat dibaca mencakup dua job awal atau sebagai 10 job baru. Pembahasan utama memakai 10 job baru setelah dua job awal, agar satu contoh lengkap 10 input tersedia. Alternatif hitungan untuk 10 job total diberikan setelah tabel. Tuliskan asumsi jumlah job di jawaban dan ikuti klarifikasi dosen jika tersedia.

Total waktu proses pada bagian (b) kita artikan sebagai waktu dalam sistem, yaitu tunggu ditambah pelayanan, sesuai jenis kolom pembahasan yang ada dalam resource. Rata-rata durasi pelayanan murni juga dilaporkan agar kedua istilah tidak tertukar.

### A1.4 Kalimat: “antarwaktu kedatangan berdistribusi sebagai berikut”

Artinya kita membuat batas kumulatif untuk memilih selang kedatangan dari U. Tambahkan peluang dari atas ke bawah:

| Selang (jam) | Peluang | Kumulatif | Rentang U | Selang (menit) |
| --- | --- | --- | --- | --- |
| 0 | 0,23 | 0,23 | 0 ≤ U < 0,23 | 0 |
| 1 | 0,37 | 0,60 | 0,23 ≤ U < 0,60 | 60 |
| 2 | 0,28 | 0,88 | 0,60 ≤ U < 0,88 | 120 |
| 3 | 0,12 | 1,00 | 0,88 ≤ U < 1 | 180 |

Jika U = 0,58, nilainya masuk baris kedua: selang 1 jam = 60 menit. Ini selang sejak kedatangan sebelumnya. Untuk memperoleh waktu kedatangan, tambahkan selang-selang tersebut secara berurutan. Selang 0 berarti dua job dapat datang pada waktu yang sama.

### A1.5 Kalimat: “waktu pemrosesan eksponensial, rata-rata 50 menit”

Artinya angka random berikutnya harus diubah menjadi lama pelayanan. Ambil rata-rata 50 sebagai pengali:

$$\text{Pelayanan}=-50\ln(1-U).$$

Untuk U = 0,70, tekan kalkulator: 1 − 0,70 = 0,30; ln(0,30) = −1,2039728; kalikan −50. Hasilnya 60,19864 menit.

Angka 50 adalah rata-rata dari distribusi, bukan durasi tetap setiap job. Gunakan ln, bukan log basis 10.

### A1.6 Bangkitkan dua input per job

Kita mengambil satu U untuk selang kedatangan, lalu U berikutnya untuk pelayanan job yang sama. Selanjutnya pindah ke job berikutnya. Jangan memakai satu U yang sama untuk dua input yang diasumsikan independen.

| Job baru | U kedatangan | Selang (menit) | U pelayanan | Pelayanan (menit) |
| --- | --- | --- | --- | --- |
| 1 | 0,58 | 60 | 0,70 | 60,20 |
| 2 | 0,16 | 0 | 0,85 | 94,86 |
| 3 | 0,58 | 60 | 0,53 | 37,75 |
| 4 | 0,49 | 60 | 0,60 | 45,81 |
| 5 | 0,74 | 120 | 0,71 | 61,89 |
| 6 | 0,99 | 180 | 0,05 | 2,56 |
| 7 | 0,73 | 120 | 0,34 | 20,78 |
| 8 | 0,56 | 60 | 0,42 | 27,24 |
| 9 | 0,82 | 120 | 0,24 | 13,72 |
| 10 | 0,53 | 60 | 0,90 | 115,13 |

### A1.7 Isi tabel perjalanan job: pahami tiga kolom inti

Urutan kerjanya selalu sama:

1. Datang = waktu kedatangan sebelumnya + selang kedatangan baru.
2. Mulai = waktu yang lebih akhir antara pelanggan datang dan server tersedia.
3. Selesai = mulai + pelayanan.
4. Tunggu = mulai − datang.
5. Waktu dalam sistem = selesai − datang.

Kalimat “ambil yang lebih akhir” dapat ditulis dengan max. Jadi max bukan rumus asing: kita sedang memastikan job sudah datang dan mesin sudah kosong.

Job baru 1: datang menit 60. Mesin masih menangani dua job awal sampai menit 75. Ia mulai 75, selesai 75 + 60,19864 = 135,19864. Tunggunya 75 − 60 = 15 menit. Waktu dalam sistem 135,19864 − 60 = 75,19864 menit.

Job baru 2: selang kedatangannya 0, sehingga datang juga pada menit 60. Dengan FIFO dan urutan pengambilan sebagai pemecah kedatangan bersamaan, ia berada setelah job baru 1. Maka mulai 135,19864, selesai 230,05464, dan tunggu 75,19864 menit.

Job baru 6: datang pada menit 480. Job sebelumnya sudah selesai pada 375,51402. Mesin menunggu kedatangannya, sehingga job 6 langsung mulai 480. Ia tidak mulai pada 375,51402 karena belum datang.

| Job baru | Datang | Mulai | Selesai | Tunggu | Dalam sistem |
| --- | --- | --- | --- | --- | --- |
| 1 | 60 | 75,00 | 135,20 | 15,00 | 75,20 |
| 2 | 60 | 135,20 | 230,05 | 75,20 | 170,05 |
| 3 | 120 | 230,05 | 267,81 | 110,05 | 147,81 |
| 4 | 180 | 267,81 | 313,62 | 87,81 | 133,62 |
| 5 | 300 | 313,62 | 375,51 | 13,62 | 75,51 |
| 6 | 480 | 480,00 | 482,56 | 0,00 | 2,56 |
| 7 | 600 | 600,00 | 620,78 | 0,00 | 20,78 |
| 8 | 660 | 660,00 | 687,24 | 0,00 | 27,24 |
| 9 | 780 | 780,00 | 793,72 | 0,00 | 13,72 |
| 10 | 840 | 840,00 | 955,13 | 0,00 | 115,13 |

### A1.8 Jawab tiga pertanyaan

Semua hasil berikut khusus 10 job baru dengan konvensi random dan asumsi di atas.

- Rata-rata waktu tunggu = total tunggu / 10 = 301,67935 / 10 = **30,17 menit/job**.
- Rata-rata waktu dalam sistem = total waktu dalam sistem / 10 = 781,62127 / 10 = **78,16 menit/job**.
- Waktu tunggu maksimum = nilai terbesar kolom tunggu = **110,05 menit**, dialami job baru 3.
- Jika yang dimaksud waktu proses adalah pelayanan murni, rata-rata pelayanan = **47,99 menit/job**. Nyatakan definisi ukuran yang dipakai.

Tidak perlu rumus distribusi lagi ketika merangkum tabel. Kata rata-rata berarti jumlahkan lalu bagi banyak job; kata maksimum berarti ambil nilai terbesar.

### A1.9 Jika “10 job” mencakup dua job awal

Kita berhenti setelah 8 job baru, sehingga ada 10 job total. Jika semua indikator didefinisikan sejak t = 0, job awal dalam layanan mempunyai sisa durasi 25 menit dan tunggu sejak t = 0 sebesar 0; job awal yang mengantre menunggu 25 dan berada di sistem selama 75 menit.

- Rata-rata tunggu 10 job total sejak t = 0: **32,67 menit**.
- Rata-rata durasi dalam sistem yang teramati sejak t = 0: **75,28 menit**.
- Tunggu maksimum sejak t = 0: **110,05 menit**.

Jika pelaporan dibatasi 8 job baru saja, mean tunggu = 37,71 dan mean waktu dalam sistem = 81,60 menit. Riwayat waktu sebelum t = 0 untuk job yang sudah ada tidak disediakan, sehingga waktu historis penuh kedua job awal tidak dapat dipulihkan. Jangan mencampur total 10 dengan pembagi 8 atau total 12 dengan pembagi 10.

### A1.10 Yang perlu kamu bawa dari soal ini

Cerita antrean menghasilkan tabel, bukan satu rumus besar. Tabel peluang memilih selang; eksponensial membuat lama proses; aturan ketersediaan mesin menentukan mulai; pengurangan menghasilkan tunggu. Saat mengerjakan, ulangi nama operasi itu pada setiap kolom.

## A2 — LCG dan dua pengujian

### A2.1 Kenali perintah dari soal

Soal memberikan X₀ = 27, a = 8, c = 47, m = 100. Diminta membangkitkan 50 bilangan dengan tiga angka di belakang koma, kemudian menguji independent dan identik. Catatan soal mengatakan tidak perlu membandingkan statistik hitung dengan tabel statistik.

Ini saatnya LCG dipakai: kita diberi bahan untuk membuat U, bukan langsung diberi daftar U untuk digunakan dalam antrean.

### A2.2 Jalankan generator

$$X_{i+1}=(8X_i+47)\bmod100,\qquad U_i=X_i/100.$$

mod berarti sisa pembagian. Untuk mod 100, bilangan positif mempunyai sisa yang sama dengan dua digit terakhirnya.

- X₁ = (8 × 27 + 47) mod 100 = 263 mod 100 = 63; U₁ = 0,630.
- X₂ = (8 × 63 + 47) mod 100 = 551 mod 100 = 51; U₂ = 0,510.
- X₃ = (8 × 51 + 47) mod 100 = 455 mod 100 = 55; U₃ = 0,550.

Gunakan X integer untuk meneruskan generator. Permintaan tiga desimal mengatur tampilan U, sehingga 0,63 ditulis 0,630. Nilai m tetap 100. X₀ merupakan seed dan tidak ikut dihitung sebagai satu dari 50 output dalam konvensi ini.

### A2.3 Lima puluh hasil

| i | Xᵢ | Uᵢ | i | Xᵢ | Uᵢ |
| --- | --- | --- | --- | --- | --- |
| 1 | 63 | 0,630 | 26 | 91 | 0,910 |
| 2 | 51 | 0,510 | 27 | 75 | 0,750 |
| 3 | 55 | 0,550 | 28 | 47 | 0,470 |
| 4 | 87 | 0,870 | 29 | 23 | 0,230 |
| 5 | 43 | 0,430 | 30 | 31 | 0,310 |
| 6 | 91 | 0,910 | 31 | 95 | 0,950 |
| 7 | 75 | 0,750 | 32 | 7 | 0,070 |
| 8 | 47 | 0,470 | 33 | 3 | 0,030 |
| 9 | 23 | 0,230 | 34 | 71 | 0,710 |
| 10 | 31 | 0,310 | 35 | 15 | 0,150 |
| 11 | 95 | 0,950 | 36 | 67 | 0,670 |
| 12 | 7 | 0,070 | 37 | 83 | 0,830 |
| 13 | 3 | 0,030 | 38 | 11 | 0,110 |
| 14 | 71 | 0,710 | 39 | 35 | 0,350 |
| 15 | 15 | 0,150 | 40 | 27 | 0,270 |
| 16 | 67 | 0,670 | 41 | 63 | 0,630 |
| 17 | 83 | 0,830 | 42 | 51 | 0,510 |
| 18 | 11 | 0,110 | 43 | 55 | 0,550 |
| 19 | 35 | 0,350 | 44 | 87 | 0,870 |
| 20 | 27 | 0,270 | 45 | 43 | 0,430 |
| 21 | 63 | 0,630 | 46 | 91 | 0,910 |
| 22 | 51 | 0,510 | 47 | 75 | 0,750 |
| 23 | 55 | 0,550 | 48 | 47 | 0,470 |
| 24 | 87 | 0,870 | 49 | 23 | 0,230 |
| 25 | 43 | 0,430 | 50 | 31 | 0,310 |

### A2.4 Apa maksud pengujian identik dan independen?

Dalam konteks materi RNG, sasaran angkanya adalah Uniform(0,1) dengan urutan independen. Pemeriksaan marginal uniformity memakai chi-square pada kelas nilai. Pemeriksaan independensi memakai runs up-and-down pada urutan asli.

Chi-square tidak membuktikan independensi. Runs test tidak membuktikan bahwa distribusi marginalnya uniform. Dua pemeriksaan menjawab pertanyaan berbeda. “Lolos” pengujian terbatas juga bukan bukti matematis seluruh sifat IID.

### A2.5 Uniformity: kelompokkan besar-kecil nilainya

Gunakan 10 kelas sama lebar: 0 ≤ U < 0,1; 0,1 ≤ U < 0,2; dan seterusnya. Karena Uniform(0,1) memberi peluang 0,1 pada setiap kelas, harapan tiap kelas E = 50 × 0,1 = 5.

O berarti observed, hitungan angka yang benar-benar masuk kelas. E berarti expected, hitungan yang diharapkan menurut hipotesis.

$$\chi^2=\sum\frac{(O-E)^2}{E}.$$

Contoh kelas pertama: O = 4, E = 5, sehingga kontribusi = (4 − 5)²/5 = 0,20. Kerjakan untuk semua kelas lalu jumlahkan.

| Kelas U | O | E | Kontribusi chi-square |
| --- | --- | --- | --- |
| 0,0 ≤ U < 0,1 | 4 | 5 | 0,20 |
| 0,1 ≤ U < 0,2 | 4 | 5 | 0,20 |
| 0,2 ≤ U < 0,3 | 5 | 5 | 0,00 |
| 0,3 ≤ U < 0,4 | 5 | 5 | 0,00 |
| 0,4 ≤ U < 0,5 | 6 | 5 | 0,20 |
| 0,5 ≤ U < 0,6 | 6 | 5 | 0,20 |
| 0,6 ≤ U < 0,7 | 5 | 5 | 0,00 |
| 0,7 ≤ U < 0,8 | 5 | 5 | 0,00 |
| 0,8 ≤ U < 0,9 | 5 | 5 | 0,00 |
| 0,9 ≤ U < 1,0 | 5 | 5 | 0,00 |

Hasilnya **chi-square = 0,80**, dengan df = 10 − 1 = 9 untuk hipotesis Uniform(0,1) yang parameternya sudah ditentukan. Sesuai catatan soal asli, statistik hitung ini dapat dilaporkan tanpa mencari nilai kritis.

### A2.6 Independence: periksa pola urutannya

Jangan mengurutkan U dari kecil ke besar untuk runs test. Bandingkan hasil pertama dengan kedua, kedua dengan ketiga, dan seterusnya. Berikut contoh 10 hasil pertama:

0,630; 0,510; 0,550; 0,870; 0,430; 0,910; 0,750; 0,470; 0,230; 0,310.

Turun beri tanda −, naik beri tanda +. Untuk 10 angka pertama, tandanya: −, +, +, −, +, −, −, −, +. Kelompok run-nya adalah (−), (++), (−), (+), (−−−), (+): 6 run untuk contoh sepuluh angka ini.

Untuk soal lengkap, kita memakai seluruh 50 angka: ada 49 perbandingan dan **34 run**. Berikut seluruh kelompok tanda untuk membantu pengecekan hitung:

(−) (++) (−) (+) (−−−) (++) (−−) (+) (−) (++) (−) (+) (−) (+) (−) (++) (−) (+) (−−−) (++) (−−) (+) (−) (++) (−) (+) (−) (+) (−) (++) (−) (+) (−−−) (+)

Satu kelompok tanda sama merupakan satu run. Karena itu jumlah run = 1 + jumlah pergantian tanda, jika setidaknya ada satu tanda. n dalam rumus berikut adalah 50 angka, bukan 49 tanda dan bukan 34 run.

$$\mu_A=\frac{2n-1}{3}=\frac{99}{3}=33.$$

$$\sigma_A^2=\frac{16n-29}{90}=\frac{771}{90}=8,56667.$$

$$Z=\frac{A-\mu_A}{\sqrt{\sigma_A^2}}=\frac{34-33}{\sqrt{8,56667}}=0,34166.$$

Rumus ini untuk runs up-and-down tanpa ties berturut-turut, seperti hasil yang digunakan di sini. Tidak boleh diganti dengan rumus runs above/below mean karena jenis run-nya berbeda.

### A2.7 Bentuk jawaban akhir

Laporkan 50 U, tabel frekuensi uniformity dengan chi-square = 0,80, serta hasil runs A = 34 dan Z = 0,34166. Karena soal menyatakan tidak perlu membandingkan nilai tabel, jangan memaksakan keputusan signifikan tanpa menetapkan aturan uji.

Untuk memahami interpretasi saja: jika kita memilih uji runs dua sisi 5% dengan pendekatan normal, |Z| = 0,342 < 1,96, sehingga gagal menolak hipotesis independensi berdasarkan runs test tersebut. Ini bukan bukti bahwa generator pasti baik.

Generator kembali ke seed 27 pada X₂₀, sehingga urutannya berulang dengan periode 20. Karena itu 50 angka sebenarnya terdiri dari dua siklus penuh dan sepuluh angka berikutnya. Periode pendek ini menjelaskan mengapa angka bisa terlihat cukup seimbang dan lolos pemeriksaan sederhana, tetapi tetap kurang baik untuk simulasi panjang.

### A2.8 Cara mengenali rumusnya di soal lain

Seed dan a,c,m menandai LCG. Perintah periksa distribusi uniform menandai tabel frekuensi/chi-square atau uji kecocokan lain yang diminta. Perintah periksa independensi menandai urutan dan runs/autocorrelation. Perintah membangkitkan eksponensial belum memerlukan chi-square sampai diminta pengujian.

## C1 — Bagel: produksi mana yang menghasilkan profit terbesar?

### C1.1 Baca soal sebagai alur satu hari usaha

Pada soal asli, jumlah pelanggan per hari adalah 8, 10, 12, atau 14 dengan peluang 0,35; 0,30; 0,25; 0,10. Pesanan masing-masing pelanggan adalah 1, 2, 3, atau 4 lusin dengan peluang 0,40; 0,30; 0,20; 0,10.

Harga normal 8,40 dolar per lusin. Biaya produksi 5,80 dolar per lusin. Sisa pada akhir hari dijual setengah harga, sehingga nilai jual sisa 4,20 dolar per lusin. Kita mensimulasikan lima hari lalu memilih produksi harian dalam kelipatan lima lusin.

Ini cerita keputusan produksi, bukan antrean. Tidak ada waktu mulai/selesai yang harus dihitung. Kita perlu jumlah pelanggan, pesanan tiap pelanggan, demand harian, lalu uang masuk dan biaya untuk setiap alternatif Q.

### C1.2 Dua tabel peluang mempunyai dua fungsi

| Pelanggan/hari | Peluang | Kumulatif | Rentang U |
| --- | --- | --- | --- |
| 8 | 0,35 | 0,35 | 0 ≤ U < 0,35 |
| 10 | 0,30 | 0,65 | 0,35 ≤ U < 0,65 |
| 12 | 0,25 | 0,90 | 0,65 ≤ U < 0,90 |
| 14 | 0,10 | 1,00 | 0,90 ≤ U < 1 |

| Pesanan/pelanggan (lusin) | Peluang | Kumulatif | Rentang U |
| --- | --- | --- | --- |
| 1 | 0,40 | 0,40 | 0 ≤ U < 0,40 |
| 2 | 0,30 | 0,70 | 0,40 ≤ U < 0,70 |
| 3 | 0,20 | 0,90 | 0,70 ≤ U < 0,90 |
| 4 | 0,10 | 1,00 | 0,90 ≤ U < 1 |

Untuk satu hari: gunakan satu U untuk jumlah pelanggan. Jika hasilnya 10 pelanggan, ambil 10 U berikutnya untuk pesanan mereka. Jumlahkan sepuluh pesanan itu. Hari berikutnya mulai dari U yang belum dipakai. Jangan mengalikan jumlah pelanggan dengan satu hasil pesanan acak saja karena pesanan setiap pelanggan dibangkitkan tersendiri.

### C1.3 Hari pertama dikerjakan sampai demand

U pertama = 0,58. Berdasarkan tabel pelanggan, hasilnya 10 pelanggan. Untuk pesanan, kita memakai U kedua sampai kesebelas:

| Pelanggan | U pesanan | Pesanan (lusin) |
| --- | --- | --- |
| 1 | 0,70 | 3 |
| 2 | 0,16 | 1 |
| 3 | 0,85 | 3 |
| 4 | 0,58 | 2 |
| 5 | 0,53 | 2 |
| 6 | 0,49 | 2 |
| 7 | 0,60 | 2 |
| 8 | 0,74 | 3 |
| 9 | 0,71 | 3 |
| 10 | 0,99 | 4 |

Demand hari pertama = 3 + 1 + 3 + 2 + 2 + 2 + 2 + 3 + 3 + 4 = **25 lusin**. Pada konvensi batas yang kita pilih, U = 0,70 masuk pesanan 3 lusin.

### C1.4 Lima hari simulasi

Berikut semua hasil, sehingga proses pengambilan random dan penjumlahan demand dapat ditelusuri:

| Hari | U pelanggan | Jumlah pelanggan | U untuk pesanan | Pesanan berturut-turut (lusin) | Demand |
| --- | --- | --- | --- | --- | --- |
| 1 | 0,58 | 10 | nomor 2–11 | 3, 1, 3, 2, 2, 2, 2, 3, 3, 4 | 25 |
| 2 | 0,05 | 8 | nomor 13–20 | 3, 1, 2, 2, 3, 1, 2, 4 | 18 |
| 3 | 0,54 | 10 | nomor 22–31 | 3, 2, 2, 1, 1, 4, 2, 2, 1, 2 | 20 |
| 4 | 0,75 | 12 | nomor 33–44 | 1, 1, 1, 3, 2, 1, 1, 3, 2, 1, 1, 2 | 19 |
| 5 | 0,78 | 12 | nomor 46–57 | 3, 2, 3, 2, 1, 3, 1, 1, 1, 4, 1, 1 | 23 |

Hari kedua memakai U ke-12 = 0,05 untuk jumlah pelanggan, sehingga diperoleh 8 pelanggan. Pesanan memakai U ke-13 sampai ke-20. Hari ketiga memakai U ke-21 untuk jumlah pelanggan. Polanya berlanjut dengan cara yang sama. Total 57 angka random dipakai untuk lima hari ini.

Demand yang dihasilkan adalah **25, 18, 20, 19, dan 23 lusin**. Setelah demand ini terbentuk, pakai demand yang sama untuk membandingkan seluruh alternatif produksi. Jangan membuat ulang demand berbeda bagi setiap Q dalam contoh perbandingan ini.

### C1.5 Dari demand menjadi profit: ikuti arus barang dan uang

Untuk produksi Q dan demand D:

- Terjual normal = yang lebih kecil antara Q dan D.
- Sisa = Q − terjual normal.
- Pendapatan = terjual normal × 8,40 + sisa × 4,20.
- Biaya = semua Q yang dibuat × 5,80.
- Profit = pendapatan − biaya.

Rumus singkatnya:

$$\text{Profit}=8,40\min(Q,D)+4,20\max(Q-D,0)-5,80Q.$$

Contoh hari kedua: D = 18 dan kita mencoba Q = 20. Terjual normal 18 lusin, sisa 2 lusin. Pendapatan 18 × 8,40 + 2 × 4,20 = 159,60. Biaya 20 × 5,80 = 116. Profit = **43,60 dolar**.

Contoh hari pertama: D = 25 dan Q = 20. Terjual normal 20, tidak ada sisa, dan permintaan 5 lusin tidak terpenuhi. Pendapatan 168, biaya 116, profit = **52 dolar**. Soal tidak menyebut biaya penalti kekurangan. Karena itu kita tidak otomatis mengurangi lost profit sebagai biaya tambahan.

Sisa menghasilkan pendapatan di soal ini karena redaksi secara eksplisit mengatakan sisa dijual setengah harga. Jika soal lain mengatakan sisa dibuang tanpa nilai, pendapatan sisa menjadi nol.

### C1.6 Bandingkan alternatif kelipatan lima

Semua nilai profit berikut dalam dolar. Rata-rata profit adalah total lima hari dibagi lima.

| Produksi Q | Hari 1 | Hari 2 | Hari 3 | Hari 4 | Hari 5 | Rata-rata |
| --- | --- | --- | --- | --- | --- | --- |
| 5 | 13,00 | 13,00 | 13,00 | 13,00 | 13,00 | 13,00 |
| 10 | 26,00 | 26,00 | 26,00 | 26,00 | 26,00 | 26,00 |
| 15 | 39,00 | 39,00 | 39,00 | 39,00 | 39,00 | 39,00 |
| 20 | 52,00 | 43,60 | 52,00 | 47,80 | 52,00 | 49,48 |
| 25 | 65,00 | 35,60 | 44,00 | 39,80 | 56,60 | 48,20 |
| 30 | 57,00 | 27,60 | 36,00 | 31,80 | 48,60 | 40,20 |
| 35 | 49,00 | 19,60 | 28,00 | 23,80 | 40,60 | 32,20 |

Hasil contoh ini memilih **Q = 20 lusin per hari**, dengan rata-rata profit **49,48 dolar per hari**. Total lima hari = 247,40 dolar.

Pilihan di atas 25 lusin tidak memperbaiki hasil pada lima demand tersebut: semua permintaan paling tinggi 25, sehingga setiap produksi tambahan hanya menjadi sisa yang dijual 4,20 tetapi menghabiskan biaya 5,80. Di bawah 15, seluruh produksi terjual normal dan profit meningkat ketika Q ditambah. Karena itu perbandingan kandidat di sekitar 15, 20, dan 25 cukup menentukan pilihan kelipatan lima dalam realisasi lima hari ini.

Keputusan ini berlaku untuk contoh random yang digunakan, bukan keputusan universal untuk semua sampel atau semua NRP. Hasilnya dapat berbeda dari workbook teman karena konvensi random kita dinyatakan berbeda dan perhitungan profit mengikuti komponen yang ditulis di soal.

### C1.7 Cara mengingat tanpa menghafal rumus panjang

Gambar arus uang dengan kata-kata: uang dari penjualan normal, tambah uang penjualan sisa, kurangi uang membuat semua produk. Setelah itu bandingkan rata-rata profit setiap pilihan Q. Kamu dapat membangun rumus min/max dari alur tersebut.

## C2 — Lead time eksponensial: dua perintah, dua pekerjaan

### C2.1 Apa yang diminta soal asli?

Lead time inventory mengikuti distribusi eksponensial dengan rata-rata 3,7 hari. Diminta membangkitkan 10 nilai menggunakan random number lampiran dan menjelaskan bagaimana menguji kesesuaian distribusi hasil pembangkitan.

Soal ini tidak meminta menjalankan tabel stok, memesan barang, atau menghitung biaya. Kata inventory merupakan konteks. Dua tugas yang benar-benar diminta adalah menghasilkan 10 waktu dan menjelaskan uji kecocokannya.

### C2.2 Bagian pertama: buat waktu dari U

Karena rata-rata diberikan langsung sebesar 3,7 hari:

$$X=-3,7\ln(1-U).$$

Contoh U = 0,58: X = −3,7 ln(0,42) = 3,209752 hari. Angka 3,7 adalah mean, sehingga tidak perlu dibalik menjadi 1/3,7 sebagai pengali. Jika soal memberi rate λ, barulah pengalinya adalah 1/λ.

Gunakan sepuluh U pertama sesuai konvensi contoh kita:

| Urutan pembangkitan | U | Lead time X (hari) |
| --- | --- | --- |
| 1 | 0,58 | 3,2098 |
| 2 | 0,70 | 4,4547 |
| 3 | 0,16 | 0,6451 |
| 4 | 0,85 | 7,0193 |
| 5 | 0,58 | 3,2098 |
| 6 | 0,53 | 2,7936 |
| 7 | 0,49 | 2,4914 |
| 8 | 0,60 | 3,3903 |
| 9 | 0,74 | 4,9842 |
| 10 | 0,71 | 4,5801 |

### C2.3 Bagian kedua: jelaskan pengujian

Untuk contoh ini kita memilih K–S, karena menguji kecocokan distribusi kontinu dan hanya terdapat sepuluh nilai. Chi-square dengan banyak kelas pada n = 10 mudah menghasilkan frekuensi harapan terlalu kecil.

Tetapkan H₀: data mengikuti eksponensial dengan mean 3,7 hari. H₁: distribusinya berbeda. Mean di sini diketahui dari soal, bukan diestimasi ulang dari sepuluh nilai.

Urutkan sepuluh X dari kecil ke besar. Pada setiap nilai, hitung peluang teoritis:

$$F_0(x)=1-e^{-x/3,7}.$$

Perhatikan tugas kedua ini membalik arah perhitungan. Sebelumnya U diubah menjadi X. Sekarang X diubah menjadi peluang F₀(X) untuk dibandingkan dengan proporsi data. Karena X dibangkitkan tepat dengan invers CDF yang sama, F₀(X) kembali ke U asal sebelum pembulatan. Ini bisa menjadi cek perhitungan.

### C2.4 Mengapa ada i/n dan (i−1)/n?

Pada data urutan ke-i, CDF empiris sesudah loncatan adalah i/n dan sebelum loncatan adalah (i−1)/n. Untuk n = 10, tangganya bergerak sebesar 0,1. Kita memeriksa dua sisi loncatan:

$$d_i^+=i/n-F_0(x_i),\qquad d_i^-=F_0(x_i)-(i-1)/n.$$

Ambil maksimum tiap kolom, lalu maksimum keduanya. Huruf kecil d di sini untuk hasil per baris, D untuk maksimum statistik keseluruhan. Kandidat selisih bertanda dapat negatif; jangan mengubah setiap kandidat menjadi nilai mutlak sebelum mencari maksimum dua kolom ini.

| i | X terurut (hari) | F₀(X) | (i−1)/10 | i/10 | d⁺ | d⁻ |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 0,6451 | 0,16 | 0,00 | 0,10 | -0,06 | 0,16 |
| 2 | 2,4914 | 0,49 | 0,10 | 0,20 | -0,29 | 0,39 |
| 3 | 2,7936 | 0,53 | 0,20 | 0,30 | -0,23 | 0,33 |
| 4 | 3,2098 | 0,58 | 0,30 | 0,40 | -0,18 | 0,28 |
| 5 | 3,2098 | 0,58 | 0,40 | 0,50 | -0,08 | 0,18 |
| 6 | 3,3903 | 0,60 | 0,50 | 0,60 | 0,00 | 0,10 |
| 7 | 4,4547 | 0,70 | 0,60 | 0,70 | 0,00 | 0,10 |
| 8 | 4,5801 | 0,71 | 0,70 | 0,80 | 0,09 | 0,01 |
| 9 | 4,9842 | 0,74 | 0,80 | 0,90 | 0,16 | -0,06 |
| 10 | 7,0193 | 0,85 | 0,90 | 1,00 | 0,15 | -0,05 |

Contoh baris kedua: x = 2,491375 hari dan F₀(x) = 0,49. Tepat sesudah observasi kedua, CDF empiris = 2/10 = 0,20. Sebelumnya = 1/10 = 0,10. Maka d⁺ = 0,20 − 0,49 = −0,29 dan d⁻ = 0,49 − 0,10 = 0,39.

Hasil akhirnya **D⁺ = 0,16**, **D⁻ = 0,39**, sehingga **D = 0,39**.

### C2.5 Kesimpulan uji

Soal asli hanya meminta menjelaskan cara menguji; taraf signifikansi tidak dicantumkan pada foto soal. Untuk melengkapi contoh, kita memilih α = 0,05. Dengan nilai kritis sekitar 0,410 yang dipakai dalam pembahasan resource untuk n = 10 dan distribusi kontinu dengan parameter diketahui, D = 0,39 lebih kecil dari nilai kritis, sehingga gagal menolak H₀.

Jika soal menyediakan tabel Law–Kelton yang memakai penyesuaian D, pakai statistik dan tabel yang sesuai. Jangan membandingkan D mentah dengan nilai kritis bagi statistik yang sudah disesuaikan. Jika parameter diestimasi dari data, nilai kritis yang dipakai juga harus sesuai kasus tersebut.

Kesimpulan ini menyatakan tidak cukup bukti ketidakcocokan pada uji tersebut. Ini tidak membuktikan semua sifat generator atau kualitas seluruh model inventory. Karena angka dibangkitkan dari distribusi hipotesis, tugas ini terutama menunjukkan cara menghitung transformasi dan pemeriksaan kecocokan sampel.

### C2.6 Dua kalimat pengingat yang berbeda

- “Bangkitkan nilai eksponensial”: U masuk, waktu keluar; gunakan −mean × ln(1 − U).
- “Uji apakah data sesuai eksponensial”: waktu masuk, peluang teoritis keluar; gunakan F₀(x), lalu bandingkan dengan data melalui uji yang dipilih.

## Soal serupa 1 — Antrean yang mulai kosong

Contoh baru untuk latihan transfer dari A1. Satu server FIFO mulai kosong. Empat job mempunyai selang kedatangan 0, 2, 1, 7 menit dan pelayanan 4, 1, 3, 2 menit. Hitung rata-rata tunggu dan utilisasi sampai semua job selesai.

Kenali perintahnya: selang dan pelayanan sudah diberikan, sehingga tidak perlu LCG atau inverse transform. Langsung buat tabel.

| Job | Selang | Datang | Pelayanan | Mulai | Selesai | Tunggu | Dalam sistem |
|---|---|---|---|---|---|---|---|
| 1 | 0 | 0 | 4 | 0 | 4 | 0 | 4 |
| 2 | 2 | 2 | 1 | 4 | 5 | 2 | 3 |
| 3 | 1 | 3 | 3 | 5 | 8 | 2 | 5 |
| 4 | 7 | 10 | 2 | 10 | 12 | 0 | 2 |

Job 4 mulai 10 karena belum datang ketika server kosong pada 8. Rata-rata tunggu = (0 + 2 + 2 + 0)/4 = **1 menit**. Waktu dalam sistem rata-rata = 14/4 = **3,5 menit**. Utilisasi = total pelayanan / lama pengamatan = (4 + 1 + 3 + 2)/12 = **83,33%**. Idle = 2 menit, sehingga busy + idle = 12 menjadi cek konsistensi.

Jika soal meminta hanya pelanggan yang menunggu, pembaginya 2 dan mean tunggu kelompok itu menjadi 2 menit. Ikuti kelompok yang ditanyakan.

## Soal serupa 2 — Parameter LCG berubah

Contoh baru: X₀ = 7, a = 5, c = 3, m = 16. Bangkitkan empat angka pertama.

Kenali: ada seed dan a,c,m, sehingga LCG. Langkah hitungnya sama dengan A2, hanya parameternya berubah.

| i | Langkah | Xᵢ | Uᵢ |
|---|---|---|---|
| 1 | 38 mod 16 | 6 | 0,3750 |
| 2 | 33 mod 16 | 1 | 0,0625 |
| 3 | 8 mod 16 | 8 | 0,5000 |
| 4 | 43 mod 16 | 11 | 0,6875 |

Jika diperlukan tiga desimal, tulis U menjadi 0,375; 0,063; 0,500; 0,688, tetapi jangan mengubah X untuk melanjutkan generator. Jika kemudian diminta eksponensial mean 10 dari U₁, hitung X waktu = −10 ln(1 − 0,375) = **4,7000 menit**. X integer generator dan X waktu dapat memakai huruf sama pada buku, tetapi maknanya berbeda; beri nama kolom yang jelas.

## Soal serupa 3 — Produksi roti tanpa nilai sisa

Contoh baru: harga jual Rp10.000, biaya Rp6.000, sisa dibuang tanpa nilai dan tanpa biaya pembuangan. Bandingkan produksi 10 atau 12 roti selama demand 8, 12, 10.

Kenali perbedaannya dari C1: sisa tidak dijual, jadi pendapatan sisa = 0. Rumus dibangun dari uang: harga × yang terjual, kurangi biaya × semua yang dibuat.

| Demand | Profit Q = 10 | Profit Q = 12 |
|---|---|---|
| 8 | Rp20.000 | Rp8.000 |
| 12 | Rp40.000 | Rp48.000 |
| 10 | Rp40.000 | Rp28.000 |

Mean profit Q10 = Rp33.333,33/hari; Q12 = Rp28.000/hari. Pilih **10 roti untuk realisasi tiga hari ini**. Pada Q12 dan D8, biaya = 12 × 6.000 = 72.000 meskipun hanya 8 terjual. Profit = 80.000 − 72.000 = 8.000. Rp72.000 adalah biaya, bukan profit.

Jika jumlah pelanggan dan pesanan telah diberikan langsung, jangan membangkitkannya lagi. Jika keduanya diberikan sebagai distribusi, lakukan dua tahap seperti C1.

## Soal serupa 4 — Chi-square untuk data eksponensial yang parameternya diestimasi

Contoh baru: tersedia 50 data pelayanan, mean sampelnya 2 menit. Uji keluarga eksponensial memakai 6 kelas berpeluang sama. Frekuensi teramati adalah 9, 8, 7, 10, 8, 8. Nilai kritis 5% untuk df yang sesuai diberikan sebesar 9,488.

Kenali: soal memberi data dan meminta uji. Tidak ada perintah membangkitkan waktu, jadi jangan memakai inverse transform untuk mengganti data pengamatan. Mean distribusi diestimasi dengan mean sampel, yaitu 2 menit.

Untuk membuat enam kelas berpeluang sama, batas atas kelima kelas awal dapat diperoleh dari invers CDF pada peluang 1/6, 2/6, ..., 5/6. Dengan mean 2, batasnya sekitar 0,3646; 0,8109; 1,3863; 2,1972; 3,5835 menit. Kelas terakhir menuju tak hingga. Dalam hitungan gunakan batas presisi penuh; angka ini untuk pembacaan.

| Kelas | O | E = 50/6 | (O−E)²/E |
|---|---|---|---|
| 1 | 9 | 8,333… | 0,05333 |
| 2 | 8 | 8,333… | 0,01333 |
| 3 | 7 | 8,333… | 0,21333 |
| 4 | 10 | 8,333… | 0,33333 |
| 5 | 8 | 8,333… | 0,01333 |
| 6 | 8 | 8,333… | 0,01333 |

Chi-square = **0,64**. df = kelas − 1 − jumlah parameter yang diestimasi = 6 − 1 − 1 = **4**. Karena 0,64 < 9,488, gagal menolak hipotesis kecocokan eksponensial.

Jika kelas tidak dibuat berpeluang sama, jangan memakai E = n/k. Hitung peluang tiap kelas dari CDF, kemudian E = n × peluang kelas. Jika frekuensi harapan terlalu kecil dan kelas digabung, sesuaikan jumlah kelas akhir dalam df.

Perbandingan dengan A2: pada A2, Uniform(0,1) sudah ditetapkan sehingga tidak ada parameter yang diestimasi. Pada contoh ini, mean eksponensial diambil dari data sehingga mengurangi df satu lagi.

## Soal serupa 5 — Welch dari data replikasi sampai warm-up

Ini contoh tambahan untuk batas materi ujianmu. Tiga replikasi mempunyai sembilan pengamatan berikut:

| i | Replikasi 1 | Replikasi 2 | Replikasi 3 | Rata-rata antarreplikasi |
|---|---|---|---|---|
| 1 | 0 | 1 | 2 | 1 |
| 2 | 1 | 2 | 3 | 2 |
| 3 | 3 | 4 | 5 | 4 |
| 4 | 5 | 6 | 7 | 6 |
| 5 | 5 | 6 | 7 | 6 |
| 6 | 5 | 6 | 7 | 6 |
| 7 | 5 | 6 | 7 | 6 |
| 8 | 5 | 6 | 7 | 6 |
| 9 | 5 | 6 | 7 | 6 |

Kenali: ada beberapa replikasi dengan observasi dari awal dan perintah menentukan warm-up. Kita perlu rata-rata pada waktu yang sama, lalu smoothing. Welch ini merupakan prosedur warm-up, bukan Welch t-test.

Langkah pertama menghasilkan deret 1, 2, 4, 6, 6, 6, 6, 6, 6. Pilih w = 1, sehingga titik interior memakai tiga nilai: satu sebelum, pusat, dan satu sesudah.

| Pusat i | Nilai yang dirata-ratakan | Moving average |
|---|---|---|
| 1 | 1, dengan aturan awal yang diperkecil | 1,000 |
| 2 | 1, 2, 4 | 2,333 |
| 3 | 2, 4, 6 | 4,000 |
| 4 | 4, 6, 6 | 5,333 |
| 5 | 6, 6, 6 | 6,000 |
| 6 | 6, 6, 6 | 6,000 |
| 7 | 6, 6, 6 | 6,000 |
| 8 | 6, 6, 6 | 6,000 |

Perhitungan versi slide berhenti pada m − w = 9 − 1 = 8. w adalah setengah lebar jendela, sehingga w = 2 akan memakai 5 nilai interior, bukan 2. Awal deret mempunyai aturan jendela simetris yang diperkecil. Pusat terakhir di ujung kanan harus mempunyai jendela penuh.

Setelah memplot smoothing dan memeriksa sensitivitas terhadap pilihan w, pilih l dengan alasan bagian awal telah mereda dan bagian berikutnya relatif stabil. Dalam contoh buatan ini, misalkan dipilih l = 4. Buang observasi asli 1–4 di setiap replikasi dan hitung kinerja dari observasi 5–9. Rata-rata masing-masing replikasi menjadi 5, 6, 7; mean antarreplikasinya 6.

Moving average dipakai untuk membantu memilih warm-up. Kinerja akhir dihitung dari data asli setelah penghapusan, bukan otomatis dari rata-rata deret smoothing. Tidak ada aturan bahwa w = 1 berarti buang satu data, atau w = 2 berarti buang dua data. l dan w mempunyai fungsi berbeda. Pemilihan l bersifat grafis dan tidak mempunyai satu ambang universal.

## Soal serupa 6 — Confidence interval untuk ringkasan replikasi

Contoh baru: 25 replikasi independen memberi mean waktu tunggu 10 menit dan simpangan baku antarreplikasi 2 menit. Nilai kritis t untuk tingkat kepercayaan yang diminta diberikan sebesar 2,064. Susun CI mean.

Kenali: yang diminta rentang ketidakpastian mean dari ringkasan replikasi. Tidak perlu LCG, chi-square, atau K–S untuk menghitung batasnya.

$$h=t\frac{S}{\sqrt n}=2,064\frac2{\sqrt{25}}=0,8256\text{ menit}.$$

$$CI=\bar X\pm h=10\pm0,8256=[9,1744;10,8256]\text{ menit}.$$

n = 25 replikasi, bukan jumlah pelanggan dalam satu replikasi. Gunakan S atau akar varians sesuai yang diberikan; jangan memasukkan S² ke posisi S. Interval t tepat untuk ringkasan IID normal dan digunakan sebagai pendekatan ketika kondisi inferensi memadai. Jika soal meminta tambahan replikasi untuk presisi tertentu, lihat apakah yang diminta adalah half-width absolut atau relatif.

## Cara memilih rumus saat melihat soal baru

Tabel ini dipakai setelah membaca contoh lengkap, bukan sebagai daftar hafalan pertama.

| Yang diberikan / diminta | Mulai dari pekerjaan ini | Contoh di dokumen |
|---|---|---|
| Seed serta a,c,m; minta angka random | Ulangi perkalian, penambahan, sisa pembagian; bagi m | A2 |
| U tersedia dan distribusi diberikan sebagai tabel | Jumlahkan peluang menjadi kumulatif; cari interval U | A1 dan C1 |
| U tersedia; bangkitkan waktu eksponensial dengan mean β | −β ln(1−U) | A1 dan C2 |
| U tersedia; eksponensial dinyatakan dengan rate λ | −ln(1−U)/λ | Variasi dari C2 |
| Kedatangan dan layanan; minta tunggu/selesai | Isi tabel perjalanan job | A1 dan soal serupa 1 |
| Produksi, demand, harga, biaya; minta profit | Barang terjual, barang sisa, uang masuk, biaya | C1 dan soal serupa 3 |
| Data, distribusi hipotesis, minta kecocokan | Goodness-of-fit sesuai jenis data dan ketentuan soal | C2 dan soal serupa 4 |
| Urutan U; minta independensi | Pertahankan urutan, hitung runs atau metode yang diminta | A2 |
| Beberapa run dari awal; minta warm-up | Rata-rata per waktu, moving average, baca kestabilan grafik | Soal serupa 5 |
| Mean dan simpangan baku replikasi; minta CI | Hitung half-width, kurangi/tambahkan ke mean | Soal serupa 6 |

## Apa yang perlu diingat, dan apa yang bisa dibangun kembali?

Untuk latihan awal, ingat cerita operasinya. Antrean: kapan datang, kapan mesin tersedia, kapan mulai, kapan selesai. Profit: uang masuk dan uang keluar. Rata-rata: jumlahkan lalu bagi. Maksimum: ambil terbesar.

Rumus khusus yang perlu dipelajari lewat pengerjaan ulang adalah LCG, inverse transform eksponensial, statistik uji yang diminta, dan CI. Kaitkan setiap rumus dengan satu soal acuan. Misalnya ingat “LCG = A2” dan “eksponensial mean 3,7 = C2”, kemudian ingat kalimat pekerjaan sebelum simbolnya.

Latihan mengingat yang ringan: setelah membaca A1, tutup rumus dan buat judul kolom tabelnya. Setelah membaca A2, tulis satu langkah generator. Setelah C1, ceritakan arus uang. Setelah C2, sebutkan dua perintah yang berbeda. Pada putaran kedua, kerjakan dengan kalkulator dan pembahasan tertutup. Membaca lancar dan bisa menghitung ulang adalah dua tingkat pemahaman yang berbeda.

## Penunjuk sumber dan batas pembahasan

- uts_2025/2025 A.jpg: dua soal kelas A yang menjadi dasar A1 dan A2.
- uts_2025/2025 C.jpg: dua soal kelas C yang menjadi dasar C1 dan C2.
- uts_2025/Random Number.jpg: contoh digit kolom 7 yang dipakai dengan konvensi pengelompokan yang dinyatakan di awal.
- uts_2025/Pembahasan Soal 2025.xlsx: pembahasan teman, dipakai sebagai konteks dan dibandingkan, bukan dianggap kunci resmi. Di dalamnya label chi-square/runs tertukar, beberapa uji memakai n = 20 walaupun soal meminta 50, dan perhitungan profit menyertakan lost profit yang tidak dinyatakan sebagai penalti pada foto soal.
- resource/Averill/PPT/01.1 Basic Simulation Modeling.ppt: dasar antrean, inventory, dan ukuran kinerja.
- resource/Averill/PPT/06.1 Input Analysis.ppt: pemilihan distribusi, parameter, chi-square, K–S.
- resource/Averill/PPT/07.1 Random Number Generation.ppt: LCG, uniformity, runs dan autocorrelation.
- resource/Averill/PPT/08.1 Generating Random Variates - Selective.ppt: transformasi input eksponensial dan teknik lain.
- resource/Averill/PPT/09.1 Output Analysis.ppt: replikasi, CI, warm-up dan Welch, terutama slide 23–26 untuk Welch.

Pembahasan numerik A1/C1/C2 adalah satu solusi contoh dengan asumsi dan pemakaian random yang dijelaskan, bukan kunci resmi bagi semua kolom NRP. A2 memakai parameter yang diberikan di soal sehingga hasilnya tidak memerlukan kolom NRP dalam konvensi seed yang dipakai. Enam soal serupa adalah latihan buatan untuk mengenali perubahan tugas, bukan prediksi pasti soal ETS 2026.
