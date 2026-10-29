# Peta Belajar ETS Pemodelan dan Simulasi

Persiapan dari dasar untuk Jumat, 30 Oktober 2026. Disusun dari resource yang kamu kirim pada 29 Oktober 2026.

## Mulai di sini

Tujuan pertama adalah bisa mengenali jenis soal, menentukan langkah, dan mengerjakan contoh dengan kalkulator. Sembilan paket di bawah merupakan susunan belajar kita, bukan kepastian bahwa kelasmu berlangsung tepat sembilan pertemuan.

Pegangan utamanya adalah slide dalam folder resource/Averill/PPT. Jerry Banks, buku lengkap, dan spreadsheet dipakai sebagai penjelas atau latihan saat diperlukan. Kamu tidak perlu membaca semua buku dari awal.

Format belajar tiap paket: baca gambaran sederhana, lihat satu contoh, kerjakan ulang tanpa melihat, lalu buat catatan singkat. Kalau belum bisa mengerjakan sendiri, kembali ke langkah yang belum dipahami.

## Aturan ujian yang sudah diketahui

- Tanggal: Jumat, 30 Oktober 2026.
- Closed book. Hanya alat tulis dan kalkulator hitung sesuai pengumuman.
- Waktu: 100 menit.
- Kerjakan lima soal. Nomor 1 dan 3 wajib dipilih. Kerjakan secara berurutan sesuai instruksi.
- Tulis kelas yang sebenarnya, C/D/E, pada jawaban.
- Ambil kolom random digit sesuai angka akhir NRP. Pengumuman terbaru menyebut kolom 0, 1, 2, dan seterusnya. Ikuti instruksi terbaru, bukan ketentuan berbeda pada soal lama.
- Batas materi dari informasi yang kamu terima: sampai Output Analysis, prosedur Welch.

Potongan pengumuman belum memperlihatkan isi soal atau seluruh pilihan nomor. Kita belum mengetahui topik soal wajib nomor 1 dan 3.

## Apa yang ditunjukkan resource

Slide utama meliputi bab 1 sampai 9, termasuk dua versi Generating Random Variates dan satu file perbandingan alternatif sistem. Untuk batas yang kamu sampaikan, fokus Output Analysis adalah file 09.1 Output Analysis, slide 1–26. Welch dibahas pada slide 23–26. Slide setelah itu dan file alternative comparisons dapat ditunda dalam persiapan ini, kecuali ada arahan tambahan dari dosen.

Soal lama memberi contoh, bukan jaminan pola ujian baru:

| Sumber | Bentuk soal yang terlihat |
|---|---|
| ETS 2025 kelas A | Simulasi antrean job-shop satu server, interarrival diskrit, service time eksponensial, kondisi awal tidak kosong, LCG, pengujian bilangan acak |
| ETS 2025 kelas C | Simulasi jumlah pelanggan dan pesanan bagel, evaluasi profit, pembangkitan lead time eksponensial, pengujian kesesuaian distribusi |
| Foto 2024 kelas C/D | Istilah dasar, state, clock, seed, LCG, GRV, inventory, transient, dan pengujian statistik dalam bentuk teka-teki silang |
| Tugas Input Analysis | Distribusi empiris, histogram, statistik deskriptif, K–S untuk Uniform(0,100), chi-square untuk eksponensial |

Catatan kualitas pembahasan teman: pada workbook Pembahasan Soal 2025, sheet A No 2, judul chi-square dan runs test tertukar. Chi-square di contoh tersebut memeriksa keseragaman distribusi, sedangkan runs test memeriksa independensi urutan. Beberapa perhitungan juga memakai 20 angka walaupun soal meminta 50. Kita akan mengikuti konsep dan ukuran sampel yang benar-benar diminta soal.

## Sembilan paket belajar

Waktu di bawah adalah perkiraan sesi awal. Tambahkan latihan bila langkahnya belum bisa kamu ulang sendiri.

| Paket | Isi dan target | Sumber utama | Menit |
|---|---|---|---:|
| 1 | Sistem, model, simulasi, entity, state, event, clock. Bisa menjelaskan dengan contoh antrean | Bab 1, terutama slide 3–17 | 20 |
| 2 | Probabilitas, diskrit/kontinu, CDF, mean, varians, IID. Bisa membaca tabel peluang | Bab 4 | 25 |
| 3 | LCG, seed, modulo, periode, uniformity, independence. Bisa menghasilkan angka dan menyusun tabel uji | Bab 7, terutama slide 3–16 | 35 |
| 4 | Random variates: distribusi diskrit, inverse transform eksponensial, uniform, dan empiris | Bab 8; versi Selective untuk ringkasan awal | 35 |
| 5 | Antrean satu server, tabel kedatangan–mulai–selesai, waktu tunggu, waktu dalam sistem, utilisasi | Bab 1, slide 20–42; soal 2025 A | 45 |
| 6 | Persediaan dan simulasi profit. Bisa menghitung demand, penjualan, sisa, dan profit kebijakan | Bab 1, slide 43–46; soal 2025 C | 30 |
| 7 | Input analysis: empiris, histogram, parameter, chi-square, K–S. Bisa menulis hipotesis dan kesimpulan | Bab 6; tugas Input Analysis | 45 |
| 8 | Verification, validation, credibility, daftar event, fungsi software. Bisa membedakan konsep tanpa menghafal kode | Bab 2, 3, dan 5 | 15 |
| 9 | Replikasi, confidence interval, transient, steady-state, warm-up, prosedur Welch | Bab 9, slide 1–26 | 35 |

Total sesi awal sekitar 4 jam 45 menit. Tambahkan sekitar 45 menit latihan gabungan dan jeda. Ini perkiraan kerja awal, bukan janji penguasaan semua materi dalam waktu tersebut.

Untuk versi sangat singkat tiga jam: konsep dan probabilitas 20 menit, distribusi diskrit dan eksponensial 25 menit, antrean 35 menit, LCG dan uji RNG 25 menit, input analysis 30 menit, output dan Welch 30 menit, inventory dan V&V 15 menit. Pakai versi singkat hanya bila waktunya memang terbatas.

## Paket 1 — Konsep dari nol

Bayangkan sebuah tempat fotokopi dengan satu petugas. Mahasiswa datang, mungkin menunggu, dilayani, lalu pergi.

| Istilah | Makna | Contoh |
|---|---|---|
| Sistem | Bagian dunia yang sedang dipelajari | Tempat fotokopi beserta pelanggan dan petugas |
| Model | Representasi sistem dengan aturan dan asumsi yang relevan | Satu petugas, antrean FIFO, waktu kedatangan dan layanan tertentu |
| Simulasi | Menjalankan model untuk mengamati perilaku dan hasil | Mengikuti perjalanan pelanggan selama dua jam |
| Entity | Objek yang mengikuti proses | Pelanggan |
| Attribute | Sifat milik entity tertentu | Waktu kedatangan pelanggan ke-3 |
| Resource | Fasilitas atau kapasitas yang digunakan | Petugas atau mesin |
| State | Variabel yang mendeskripsikan kondisi saat ini | Jumlah yang menunggu, petugas sibuk atau idle |
| Event | Kejadian sesaat yang dapat mengubah state | Pelanggan datang atau layanan selesai |
| Activity | Kegiatan yang berlangsung selama durasi tertentu | Proses fotokopi selama 4 menit |
| Clock | Waktu dalam model | Menit ke-7 sejak simulasi dimulai |

Dalam discrete-event simulation, clock dapat melompat ke event berikutnya. Kalau event ada pada menit 2 dan 5, kita tidak harus memeriksa setiap detik di antaranya.

Klasifikasi yang perlu dikenal: static/dynamic, deterministic/stochastic, discrete/continuous. Antrean dengan kedatangan dan layanan acak biasanya merupakan model dynamic, stochastic, dan discrete-event.

Catatan satu kalimat: sistem adalah yang dipelajari, model memuat representasinya, dan simulasi menjalankan model untuk memperoleh ukuran kinerja.

Latihan: tentukan entity, resource, dua state, dua event, serta satu output untuk antrean kasir minimarket. Jawab dulu dengan bahasa sehari-hari.

## Paket 2 — Probabilitas secukupnya untuk mulai menghitung

Variabel diskrit mempunyai nilai yang dapat dihitung satu per satu, misalnya jumlah pelanggan. Variabel kontinu dapat mengambil nilai dalam suatu rentang, misalnya lama layanan 2,37 menit.

Untuk distribusi diskrit, peluang semua kemungkinan harus berjumlah 1. CDF adalah peluang kumulatif: F(x) = P(X ≤ x).

Contoh latihan buatan:

| X: lama layanan (menit) | Peluang | Peluang kumulatif |
|---:|---:|---:|
| 1 | 0,20 | 0,20 |
| 2 | 0,50 | 0,70 |
| 3 | 0,30 | 1,00 |

Mean teoritis: E[X] = Σ x p(x) = 1(0,20) + 2(0,50) + 3(0,30) = 2,10 menit.

Untuk data sampel, mean = Σx/n. Varians sampel s² = Σ(x − mean)²/(n − 1). Simpangan baku s = √s². Mean menyatakan pusat, sedangkan simpangan baku menyatakan sebaran dengan satuan yang sama seperti data.

IID berarti independent and identically distributed. Angka input yang IID tidak menjamin waktu tunggu pelanggan dalam satu run juga IID, karena antrean membawa pengaruh dari pelanggan sebelumnya.

Latihan: hitung peluang X ≤ 2, peluang X = 3, serta mean dari tabel tanpa melihat jawaban. Kunci: 0,70; 0,30; 2,10 menit.

## Paket 3 — Random number generation dan LCG

Random number biasanya dilambangkan U atau R dan berada pada skala 0–1. Untuk simulasi ini kita menginginkan distribusi Uniform(0,1) dan urutan yang independen. Komputer dapat menghasilkan urutan pseudorandom melalui aturan deterministik dengan seed tertentu.

LCG:

$$X_{i+1}=(aX_i+c)\bmod m,\qquad U_i=X_i/m.$$

Modulo berarti sisa pembagian. Contoh dari parameter soal lama: X₀ = 27, a = 8, c = 47, m = 100.

- X₁ = (8 × 27 + 47) mod 100 = 263 mod 100 = 63, sehingga U₁ = 0,630.
- X₂ = (8 × 63 + 47) mod 100 = 551 mod 100 = 51, sehingga U₂ = 0,510.
- X₃ = (8 × 51 + 47) mod 100 = 455 mod 100 = 55, sehingga U₃ = 0,550.

Gunakan X integer yang tepat untuk menghitung X berikutnya. Tiga angka di belakang koma adalah format penyajian U. Seed X₀ biasanya tidak dihitung sebagai angka hasil pertama, kecuali soal memberi konvensi berbeda.

Uniformity: apakah nilai tersebar sesuai Uniform(0,1)? Untuk k interval sama lebar, frekuensi harapan E = n/k. Statistik chi-square standar:

$$\chi^2=\sum_{j=1}^{k}\frac{(O_j-E_j)^2}{E_j}.$$

Untuk Uniform(0,1) yang parameternya ditentukan, df = k − 1. Pilih atau gabungkan kelas agar frekuensi harapan memadai. Bila n = 50 dan k = 10, setiap E = 5.

Independence: apakah urutan mempunyai pola ketergantungan? Pada runs up-and-down test, tulis tanda + jika nilai berikutnya naik dan − jika turun. Satu rangkaian tanda yang sama merupakan satu run. Banyak run = 1 + banyak pergantian tanda jika setidaknya ada satu perbandingan. Rumus standar tanpa ties:

$$\mu_A=\frac{2n-1}{3},\qquad \sigma_A^2=\frac{16n-29}{90},\qquad Z=\frac{A-\mu_A}{\sqrt{\sigma_A^2}}.$$

Jangan mengurutkan data sebelum runs test. Untuk K–S justru harus diurutkan. Jika ada nilai berturut-turut yang sama, gunakan aturan penanganan ties yang diberikan dalam soal atau materi.

Sebagai cek hitung untuk 50 hasil X₁–X₅₀ dengan parameter di atas: frekuensi sepuluh kelas sama lebar dari 0 sampai kurang dari 1 adalah 4, 4, 5, 5, 6, 6, 5, 5, 5, 5. Kelas pertama mencakup 0 ≤ U < 0,1, kelas kedua 0,1 ≤ U < 0,2, dan seterusnya. Chi-square = 0,80. Runs up-and-down = 34 dan Z ≈ 0,342. Urutan generator ini berulang dengan periode 20 pada seed yang digunakan. Hasil uji sampel yang kecil tidak membuktikan generator berkualitas baik.

## Paket 4 — Mengubah random number menjadi random variate

U = 0,60 adalah angka pada skala probabilitas. Setelah ditransformasikan, X bisa menjadi waktu layanan, jumlah pesanan, atau kebutuhan persediaan. Karena itu RNG dan generating random variates memiliki peran berbeda.

Untuk tabel diskrit Paket 2, gunakan pemetaan interval: 0 ≤ U < 0,20 menghasilkan X = 1; 0,20 ≤ U < 0,70 menghasilkan X = 2; 0,70 ≤ U < 1 menghasilkan X = 3. Ini konvensi interval kiri tertutup, kanan terbuka. Ikuti aturan batas yang diberikan soal, terutama bila digit random tepat berada pada batas kumulatif.

Eksponensial dengan mean β:

$$F(x)=1-e^{-x/\beta},\quad U=F(x),\quad X=-\beta\ln(1-U).$$

Kalau diberikan rate λ, maka β = 1/λ dan X = −ln(1 − U)/λ. Bedakan rate dan mean. Gunakan tombol ln, bukan log basis 10.

Contoh buatan mengikuti mean lead time pada soal lama: β = 3,7 hari dan U = 0,60 menghasilkan X = −3,7 ln(0,40) = 3,3903 hari.

Kamu mungkin menemukan −β ln U. Bentuk itu juga menghasilkan distribusi eksponensial untuk U uniform, tetapi menghasilkan angka berbeda untuk input U tertentu. Gunakan konvensi yang diminta soal. Catatan kita mengikuti invers CDF −β ln(1 − U), dengan U < 1.

Uniform kontinu pada [a,b]: X = a + (b − a)U. Contoh a = 2, b = 6, U = 0,25 menghasilkan X = 3.

Empiris kontinu dengan interpolasi: bila U berada di antara F₁ dan F₂ yang berpasangan dengan x₁ dan x₂, gunakan X = x₁ + (x₂ − x₁)(U − F₁)/(F₂ − F₁). Contoh slide: pasangan (1,45; 0,60) dan (1,83; 0,80), U = 0,70 menghasilkan 1,64. Jangan menggunakan interpolasi ini untuk jumlah pelanggan yang harus diskrit.

Materi perluasan bab 8 mencakup Weibull, convolution/Erlang, acceptance-rejection, normal, dan Bernoulli. Setelah dasar kuat, kenali idenya dan kerjakan contoh yang memang ditekankan dosen. Versi Selective adalah ringkasan alternatif, bukan bukti bahwa semua slide lain tidak diujikan.

## Paket 5 — Simulasi antrean satu server

Asumsi latihan: satu server, FIFO, mulai kosong dan idle. Notasi: Iᵢ = interarrival time, Aᵢ = waktu kedatangan, Sᵢ = service time, Bᵢ = mulai layanan, Cᵢ = selesai layanan, Wᵢ = waktu tunggu, Tᵢ = waktu dalam sistem.

$$A_i=A_{i-1}+I_i,\quad B_i=\max(A_i,C_{i-1}),\quad C_i=B_i+S_i.$$

$$W_i=B_i-A_i,\qquad T_i=C_i-A_i=W_i+S_i.$$

Contoh buatan dengan semua satuan menit:

| Pelanggan | I | A | S | B | C | W | T |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 | 0 | 0 | 3 | 0 | 3 | 0 | 3 |
| 2 | 2 | 2 | 2 | 3 | 5 | 1 | 3 |
| 3 | 1 | 3 | 4 | 5 | 9 | 2 | 6 |
| 4 | 7 | 10 | 1 | 10 | 11 | 0 | 1 |
| 5 | 1 | 11 | 2 | 11 | 13 | 0 | 2 |

Rata-rata waktu tunggu = 3/5 = 0,60 menit. Rata-rata waktu dalam sistem = 15/5 = 3 menit. Tunggu maksimum = 2 menit. Bila pengamatan berlangsung dari 0 sampai seluruh pelanggan selesai pada menit 13, utilisasi = total waktu sibuk/13 = 12/13 = 92,31%.

Pelanggan pertama datang pada t = 0 karena asumsi latihan ini. Jangan menetapkan demikian untuk semua soal. Periksa kedatangan pertama dan kondisi awal yang diminta.

Pada soal 2025 A sudah ada job dalam layanan dan job dalam antrean ketika simulasi dimulai. Kondisi itu harus dimasukkan sebelum kedatangan baru. Nyatakan apakah indikator dihitung untuk job baru saja atau juga job awal jika redaksi soal tidak tegas.

Samakan jam dan menit sebelum mengisi tabel. Rata-rata jumlah dalam antrean merupakan rata-rata berbobot waktu, yaitu luas di bawah Q(t) dibagi lama pengamatan. Jangan menggantinya dengan rata-rata biasa dari panjang antrean pada event.

Latihan: tutup tabel mulai kolom B, lalu hitung ulang. Jelaskan mengapa pelanggan ke-4 tidak menunggu walaupun pelanggan ke-3 selesai pada menit 9.

## Paket 6 — Persediaan dan profit

Untuk produksi harian Q dan demand harian D pada model penjualan dengan sisa yang dijual murah:

- Terjual normal = min(Q,D).
- Sisa = max(Q − D,0).
- Permintaan tidak terpenuhi = max(D − Q,0).
- Profit = harga normal × terjual normal + harga sisa × sisa − biaya produksi × Q, sebelum biaya lain yang secara eksplisit disebut soal.

Contoh buatan dengan harga dari soal bagel lama: Q = 20 lusin, D = 18 lusin, harga jual 8,40 per lusin, harga sisa 4,20, biaya produksi 5,80. Profit = 8,40(18) + 4,20(2) − 5,80(20) = 43,60.

Kalau D = 25, profit kas dengan Q = 20 menjadi 8,40(20) − 5,80(20) = 52,00. Jangan otomatis mengurangi lost profit sebagai biaya tambahan. Tidak terjualnya permintaan sudah membatasi pendapatan. Masukkan shortage penalty hanya bila kebijakan atau fungsi tujuan soal memang menyatakannya.

Jika jumlah pelanggan dan jumlah pesanan per pelanggan sama-sama acak, bangkitkan keduanya. Demand satu hari adalah jumlah seluruh pesanan pelanggan hari itu. Saat berpindah hari, lanjutkan penggunaan angka random sesuai aturan soal, jangan memakai ulang deret yang sama tanpa penjelasan. Untuk membandingkan kebijakan produksi, gunakan realisasi demand yang sama agar perbandingannya setara.

Untuk inventory dinamis juga kenali inventory level, reorder point, order quantity, lead time, holding cost, ordering cost, dan shortage cost. Ini berbeda dari kasus produksi harian sederhana tanpa pemesanan ulang.

## Paket 7 — Input analysis

Alur yang perlu diingat: tentukan jenis input dan satuannya, lihat data/histogram, pilih kandidat distribusi, estimasi parameter, uji kecocokan, lalu simpulkan. Bentuk histogram dan CV memberi petunjuk, bukan bukti tunggal distribusi.

Distribusi empiris: frekuensi relatif = f/n dan kumulatif = penjumlahan frekuensi relatif sampai nilai tersebut. Histogram mengelompokkan data ke kelas. Bila lebar kelas berbeda dan memakai density, tinggi batang harus memperhitungkan lebar kelas.

Untuk eksponensial, estimasi mean β adalah mean sampel, dan estimasi rate λ = 1/mean sampel.

Chi-square goodness-of-fit:

1. Tulis H₀: data mengikuti distribusi yang ditentukan. H₁: tidak mengikuti distribusi tersebut.
2. Tentukan kelas yang mencakup dukungan distribusi, termasuk ekor yang relevan.
3. Hitung Oⱼ, frekuensi teramati.
4. Hitung Eⱼ = n[F(bⱼ) − F(aⱼ)] dari distribusi hipotesis.
5. Gabungkan kelas bila frekuensi harapan terlalu kecil, lalu hitung Σ(O − E)²/E.
6. Dalam pendekatan standar, df = k − 1 − p, dengan p jumlah parameter yang diestimasi dari data dan k jumlah kelas akhir. Gunakan aturan atau tabel yang memang diberikan dalam soal.
7. Tolak H₀ bila statistik melebihi nilai kritis yang sesuai. Jika tidak, tulis gagal menolak H₀, bukan distribusi terbukti benar.

Contoh tugas: enam kelas eksponensial, satu parameter mean diestimasi, sehingga df = 6 − 1 − 1 = 4 sebelum penggabungan kelas. Bila semua kelas dibuat berpeluang sama dengan n = 50, E = 50/6 ≈ 8,33. Batas atas kelas terakhir menuju tak hingga, bukan berhenti pada maksimum sampel.

K–S untuk distribusi kontinu:

1. Urutkan x₍₁₎ ≤ ... ≤ x₍ₙ₎.
2. Hitung F₀(x₍ᵢ₎), i/n, dan (i − 1)/n.
3. Hitung dua selisih pada setiap observasi.

$$D^+=\max_i\left(\frac{i}{n}-F_0(x_{(i)})\right),\quad D^-=\max_i\left(F_0(x_{(i)})-\frac{i-1}{n}\right),\quad D=\max(D^+,D^-).$$

Untuk Uniform(0,100), F₀(x) = x/100 dalam rentangnya. Untuk eksponensial dengan mean β, F₀(x) = 1 − exp(−x/β).

Tabel nilai kritis K–S untuk parameter diketahui berbeda dari kasus parameter diestimasi. Slide 42 Input Analysis juga memakai statistik yang disesuaikan untuk tabel Law–Kelton. Jangan mencampur D mentah, D yang disesuaikan, dan nilai kritis dari konvensi berbeda. Untuk sampel kecil, gunakan nilai kritis tabel yang diberikan, bukan otomatis pendekatan asimtotik.

## Paket 8 — Verification, validation, dan software

Verification memeriksa apakah implementasi mengikuti model konseptual. Contoh: apakah program benar menggunakan FIFO dan rumus waktu tunggu yang direncanakan?

Validation memeriksa apakah model cukup mewakili sistem nyata untuk tujuan studi. Contoh: apakah pola antrean model sesuai data tempat fotokopi pada kondisi operasi yang sebanding?

Credibility berkaitan dengan kepercayaan pengguna atau pengambil keputusan terhadap model dan hasilnya. Pemeriksaan dapat melibatkan trace, kasus sederhana yang bisa dihitung manual, diskusi dengan ahli sistem, dan perbandingan output dengan data nyata.

Untuk bab 2, pahami fungsi daftar antrean dan future event list. Event list menyimpan kejadian mendatang beserta waktunya. Untuk bab 3, kenali fungsi software: mengatur event/clock, membangkitkan input, mengumpulkan statistik, dan membantu eksperimen. Detail kode simlib dan daftar produk software menjadi prioritas lebih rendah dalam rencana singkat ini, bukan dinyatakan pasti tidak keluar.

## Paket 9 — Output analysis sampai Welch

Satu run menghasilkan satu realisasi acak. Replikasi mengulangi simulasi dengan skenario dan aturan awal yang sama, tetapi menggunakan pengacakan yang sesuai untuk menghasilkan run independen. Mengulang seed yang sama persis tidak menghasilkan replikasi independen.

Terminating simulation memiliki akhir yang ditentukan oleh tujuan operasi atau horizon, misalnya satu hari layanan. Non-terminating simulation tidak mempunyai akhir alami dalam cakupan studinya. Steady-state menggambarkan perilaku distribusi jangka panjang yang tidak lagi dipengaruhi kuat oleh kondisi awal. Output tetap bisa berfluktuasi.

Untuk n ringkasan replikasi independen X₁,...,Xₙ:

$$\bar X=\frac{1}{n}\sum_jX_j,\quad S^2=\frac{\sum_j(X_j-\bar X)^2}{n-1},\quad CI=\bar X\pm t_{n-1,1-\alpha/2}\frac{S}{\sqrt n}.$$

S/√n merupakan standard error, sedangkan t × S/√n adalah half-width. n adalah jumlah ringkasan replikasi pada perhitungan ini, bukan otomatis jumlah pelanggan dalam satu run. Interval t tepat untuk ringkasan IID normal dan dipakai sebagai pendekatan saat kondisi inferensinya memadai.

Slide 17–20 juga membahas precision absolut dan relatif. Intinya: tambah replikasi untuk memperkecil half-width. Pendekatan perencanaan n baru ≈ n lama × (half-width lama/target half-width)² hanya estimasi awal karena nilai t dan estimasi varians bisa berubah. Jika soal meminta prosedur persis slide, gunakan rumus dan tabel pada slide tersebut.

### Mengapa warm-up diperlukan?

Model yang dimulai kosong dan idle mungkin menghasilkan waktu tunggu awal sangat kecil. Jika tujuan kita mengestimasi operasi jangka panjang, data awal itu dapat menimbulkan initialization bias. Kita memilih panjang warm-up l lalu membuang pengamatan awal saat menghitung estimator steady-state. Untuk studi terminating, kondisi awal bisa menjadi bagian penting masalah, sehingga warm-up tidak otomatis diterapkan pada semua kasus.

### Prosedur Welch

1. Jalankan n replikasi independen dengan m pengamatan per replikasi yang cukup panjang.
2. Untuk setiap indeks waktu i, hitung rata-rata lintas replikasi: ȳᵢ = Σⱼyⱼᵢ/n. Jangan merata-ratakan semua waktu sekaligus pada tahap ini.
3. Haluskan deret ȳᵢ dengan centered moving average.
4. Plot hasil smoothing dan amati bagian awal yang masih menunjukkan tren kondisi awal.
5. Coba beberapa lebar jendela w. Pilih panjang warm-up l yang didukung bagian kurva yang mulai stabil. Keputusan visual ini tidak mempunyai ambang universal yang pasti.
6. Buang pengamatan 1 sampai l saat mengestimasi kinerja steady-state. Pengamatan setelah l tetap dapat naik-turun.

Untuk titik interior dengan jendela setengah lebar w:

$$\bar y_i(w)=\frac{\sum_{s=-w}^{w}\bar y_{i+s}}{2w+1},\qquad i=w+1,\ldots,m-w.$$

Jumlah titik jendelanya 2w + 1. Jika w = 2, rata-ratakan lima titik. Pada awal deret, slide menggunakan jendela simetris yang lebih kecil: untuk i ≤ w, rata-ratakan indeks 1 sampai 2i − 1, dibagi 2i − 1. Contoh w = 2: titik i = 1 memakai ȳ₁ saja, titik i = 2 memakai ȳ₁,ȳ₂,ȳ₃. Perhitungan berhenti pada i = m − w.

Contoh sederhana buatan, bukan data soal lama: rata-rata lintas replikasi pada sembilan waktu adalah 1, 2, 4, 6, 6, 6, 6, 6, 6. Untuk w = 1, moving average pada i = 1 sampai 8 adalah 1; 2,333; 4; 5,333; 6; 6; 6; 6. Plateau terlihat mulai sekitar indeks 5. Nyatakan pilihan l dan alasannya, serta jelaskan bahwa l adalah banyak observasi yang dibuang. Tidak ada satu cutoff wajib hanya dari contoh kecil ini.

Contoh asli slide: lima replikasi, 15 observasi, w = 2. Slide 26 menyarankan akhir warm-up sekitar t = 9. Gunakan contoh ini untuk memeriksa urutan hitungmu.

Welch di sini adalah prosedur penentuan warm-up dengan moving average, berbeda dari Welch t-test untuk membandingkan dua mean.

## Bentuk catatan setiap paket

Tulis dengan tangan setelah belajar:

1. Topik dan tujuannya dalam satu kalimat.
2. Istilah penting beserta arti sehari-harinya.
3. Rumus, arti simbol, dan satuan.
4. Satu contoh lengkap yang sudah bisa dikerjakan ulang.
5. Dua kesalahan yang harus dihindari.
6. Tiga pertanyaan yang dapat dijawab tanpa melihat catatan.

Untuk closed book, gunakan catatan sebagai alat mengingat selama persiapan. Latihan terakhir dilakukan tanpa membuka catatan.

## Latihan gabungan sebelum ujian

Dalam sekitar 45 menit, coba: satu tabel antrean kecil, tiga langkah LCG, satu eksponensial dari angka U, kerangka tabel K–S atau chi-square, serta satu moving average Welch. Kerjakan tangan dan kalkulator. Setelah memeriksa hasil, tulis ulang hanya langkah yang masih salah.

Contoh alokasi 100 menit di ruang ujian: lima menit membaca dan menentukan lima soal yang mencakup nomor 1 dan 3, sekitar 85 menit mengerjakan dalam urutan nomor dengan waktu sesuai bobot/kerumitan, lalu sepuluh menit memeriksa satuan, penomoran, kolom random, dan penjumlahan. Sesuaikan alokasi dengan petunjuk lembar ujian.

## Penunjuk sumber

Semua sumber berikut berasal dari pemsimgoat.zip, kecuali pengumuman ujian yang juga dikirim sebagai gambar terpisah.

- resource/Averill/PPT/01.1 Basic Simulation Modeling.ppt: konsep, single-server, inventory, struktur studi simulasi.
- resource/Averill/PPT/02.1 Modeling Complex Systems.ppt: list processing, event list, bank dan job-shop.
- resource/Averill/PPT/03.1 Simulation Software.ppt: fungsi dan klasifikasi software.
- resource/Averill/PPT/04.1 Review of Basic Probability and Statistics.ppt: peluang, mean/varians, proses output, interval kepercayaan.
- resource/Averill/PPT/05.1 Building Valid, Credible, and Appropriately Detailed Simulation Mode.ppt: verification, validation, credibility.
- resource/Averill/PPT/06.1 Input Analysis.ppt: distribusi input, summary statistics, fitting, chi-square dan K–S.
- resource/Averill/PPT/07.1 Random Number Generation.ppt: LCG, uniformity, runs, autocorrelation.
- resource/Averill/PPT/08.1 Generating Random Variates - Selective.ppt dan versi lengkap: transformasi dan teknik pembangkitan variat.
- resource/Averill/PPT/09.1 Output Analysis.ppt: replikasi, CI, precision, transient, steady-state, Welch; Welch pada slide 23–26.
- uts_2025/2025 A.jpg dan uts_2025/2025 C.jpg: contoh format hitung ujian lama.
- uts_2025/2024 C.jpg dan uts_2025/2024 D.jpg: contoh istilah ujian lama. Isian tulisan tangan bukan kunci resmi yang diasumsikan benar.
- uts_2025/Pembahasan Soal 2025.xlsx: contoh pengerjaan teman, dengan beberapa kekeliruan yang dicatat di atas. File asli tidak diubah.
- tugas6/Pem-Sim Kelas E.pdf dan tugas6/Tugas 6 - Input Analysis.xlsx: konteks tugas input analysis.

Nomor slide mengikuti jumlah halaman hasil pembacaan file PPT. Jika tampilan aplikasimu berbeda, cari judul subtopiknya. Contoh berlabel buatan adalah contoh belajar baru, bukan bocoran atau rekonstruksi soal ujian 2026.
