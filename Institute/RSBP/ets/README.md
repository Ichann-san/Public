# ETS Rekayasa Sistem Berbasis Pengetahuan: ROSA dengan Protégé 5.6.9

Panduan ini mengerjakan soal [ETS RSBP A_2026_AL.pdf](<ETS RSBP A_2026_AL.pdf>) menggunakan **ontologi OWL, aturan SWRL, dan query SQWRL**. Urutannya: kerjakan di Protégé terlebih dahulu pada Bagian A, gunakan hasilnya untuk menjawab empat pertanyaan soal pada Bagian B, lalu pelajari sintaks dan parameter pada Bagian C.

Sumber utama: PDF soal halaman 2 untuk pertanyaan, halaman 3 untuk observasi 10 staf, halaman 4 untuk kategori risiko, dan **gambar worksheet halaman 5 untuk aturan serta matriks skor**. Perhitungan mengikuti worksheet yang terlampir pada soal.

Navigasi: [tutorial Protégé](#a-kerjakan-di-protégé-terlebih-dahulu), [jawaban soal](#b-jawaban-pertanyaan-pada-soal), [silabus dan sintaks](#c-silabus-ringkas-dan-referensi-sintaks-yang-digunakan), [sumber dan verifikasi](#d-sumber-dan-batas-verifikasi).

| Berkas | Kegunaan |
| --- | --- |
| `README.md` | Tutorial, langkah cadangan, jawaban, dan silabus sintaks. |
| [rosa-ets.owl](rosa-ets.owl) | Cadangan siap buka: 10 staf, data masukan, 176 sel matriks A/B/C, 56 aturan, dan 4 query. Skor keluaran belum dimasukkan sebagai fakta; mesin aturan yang menghitungnya. |

**Status verifikasi:** berkas OWL dimuat menggunakan OWLAPI dari instalasi Protégé 5.6.9 dan dieksekusi dengan SWRLAPI/Drools bawaan plugin `swrltab-plugin-2.0.10.jar`. Keempat query berhasil; query hasil akhir dan jejak skor masing-masing menghasilkan 10 baris dan cocok dengan perhitungan terpisah. Pengujian dilakukan melalui API Java tanpa membuka antarmuka grafis; urutan klik di bawah disusun dari dokumentasi plugin dan label kontrol versi terpasang.

## A. Kerjakan di Protégé terlebih dahulu

### Langkah 1 — Siapkan Protégé dan tab aturan

1. Jalankan Protégé **5.6.9**.
2. Buka **Window → Tabs**, aktifkan **Entities**, **SWRLTab**, dan **SQWRLTab**. Pada beberapa susunan antarmuka, nama tab ditampilkan dengan spasi, misalnya `SWRL Tab`.
3. Pastikan tersedia tempat membuat aturan dan tempat menjalankan query. Plugin resmi menyediakan SWRLTab dan SQWRLTab untuk Protégé 5. [Dokumentasi pemasangan plugin](https://github.com/protegeproject/swrltab-plugin).

**Hasil yang harus terlihat:** tab SWRL dan SQWRL dapat dibuka.

**Jika bermasalah / langkah cadangan:**

- Tab tidak tercantum: periksa **File → Check for plugins…** dan keberadaan SWRLTab. Pasang/aktifkan plugin yang sesuai, kemudian mulai ulang Protégé.
- Instalasi yang ditemukan pada komputer ini memiliki `plugins/swrltab-plugin-2.0.10.jar`; kombinasi tersebut sudah dipakai untuk verifikasi. Tidak perlu memperbarui plugin hanya untuk mengikuti panduan ini.
- Tidak bisa mengunduh plugin: gunakan instalasi Protégé lengkap yang sudah menyertakannya atau salin JAR rilis resmi yang kompatibel ke folder `plugins` ketika Protégé ditutup. Hindari dua versi plugin yang sama dalam folder itu.
- Tab terlihat tetapi engine gagal dimuat: jalankan Protégé memakai Java bawaan distribusi dan periksa log. Berkas OWL saja tidak dapat menggantikan mesin eksekusi SWRL/SQWRL.

### Langkah 2 — Buat dan simpan ontologi

1. Pilih **File → New** untuk membuat ontologi baru.
2. Isi Ontology IRI:

   ```text
   http://www.semanticweb.org/rsbp/ets-rosa
   ```

3. Gunakan namespace entitas:

   ```text
   http://www.semanticweb.org/rsbp/ets-rosa#
   ```

4. Pilih **File → Save As…**, simpan sebagai `rosa-latihan.owl` di folder tugas, gunakan format **RDF/XML**. IRI adalah identitas ontologi; alamat tersebut tidak perlu menjadi situs yang bisa dibuka.

**Hasil yang harus terlihat:** ontologi aktif tersimpan dan nama berkas muncul pada aplikasi.

**Jika bermasalah / langkah cadangan:** gunakan **File → Open…** untuk membuka [rosa-ets.owl](rosa-ets.owl), kemudian **Save As…** menjadi `rosa-latihan.owl`. Jika memakai berkas cadangan, langkah 3–7 sudah terisi: baca dan periksa isinya, lalu lanjut ke langkah 8. Jangan mengetik ulang entitas, sel, atau aturan yang sudah ada. Jika muncul konflik IRI karena membuka dua salinan sekaligus, tutup salah satunya dan gunakan satu ontologi aktif.

### Langkah 3 — Buat empat class

Pada **Entities → Classes**, pilih `owl:Thing`, lalu gunakan tombol tambah subclass untuk membuat:

| Class | Makna | Contoh individual |
| --- | --- | --- |
| `Staf` | Staf beserta satu snapshot assessment pada soal. | `Melati` |
| `SelA` | Satu sel tabel kursi A. | `SelA_4_4` |
| `SelB` | Satu sel tabel monitor–telepon B. | `SelB_4_5` |
| `SelC` | Satu sel tabel mouse–keyboard C. | `SelC_3_4` |

Nama sel menggunakan pola **kelas_baris_kolom**. Tidak perlu membuat object property untuk model satu assessment per staf ini; hubungan ke sel dicocokkan melalui nilai baris dan kolom.

**Hasil yang harus terlihat:** empat class sejajar di bawah `owl:Thing`.

**Jika bermasalah / langkah cadangan:** pilih kembali `owl:Thing` sebelum menambah class berikutnya agar class tidak menjadi anak `Staf`. Jika salah nama, gunakan fasilitas rename/refactor; jangan membuat entitas baru dengan ejaan hampir sama. Buka berkas cadangan bila hierarki sulit dipulihkan.

### Langkah 4 — Buat seluruh data property sebelum menulis aturan

1. Buka **Entities → Data properties**.
2. Tambahkan setiap nama pada tabel berikut. Nama peka huruf besar/kecil.
3. Untuk semua property numerik, set **Range = `xsd:decimal`**. Nilai integer seperti `90` tetap valid; rentang decimal juga menerima `0.5` dan hasil aritmetika.
4. Set `posisiMonitor` dan `kategoriRisiko` ke **Range = `xsd:string`**.
5. Domain property selain `baris`, `kolom`, dan `nilai` adalah `Staf`. Untuk tiga property sel tersebut, **biarkan domain kosong** agar dapat dipakai bersama oleh `SelA`, `SelB`, dan `SelC`.
6. Jangan menandai semua property sebagai Functional pada latihan awal; pemeriksaan satu nilai per staf dilakukan melalui hasil query.

| Kelompok | Nama property yang harus dibuat |
| --- | --- |
| Masukan kursi | `sudutLutut`, `jarakDudukanLutut`, `armrestBermasalah`, `sudutSandaran` |
| Masukan monitor | `jarakMonitor`, `posisiMonitor`, `putaranLeher`, `dokumenTanpaHolder` |
| Masukan telepon | `pakaiHeadset`, `jarakTelepon`, `teleponDijepit`, `tanpaHandsFree` |
| Masukan keyboard/mouse | `ekstensiPergelangan`, `mouseMenjangkau`, `bedaPermukaan`, `pinchGrip`, `palmrest` |
| Durasi jam/hari | `durasiKursi`, `durasiMonitor`, `durasiTelepon`, `durasiKeyboard`, `durasiMouse` |
| Isi sel matriks | `baris`, `kolom`, `nilai` |
| Keluaran kursi | `skorTinggi`, `skorDudukan`, `skorArmrest`, `skorSandaran`, `sumbuAX`, `sumbuAY`, `skorA`, `skorKursi` |
| Tambahan durasi | `tambahanDurasiKursi`, `tambahanDurasiMonitor`, `tambahanDurasiTelepon`, `tambahanDurasiKeyboard`, `tambahanDurasiMouse` |
| Keluaran monitor/telepon | `dasarMonitor`, `tambahanJarakMonitor`, `tambahanPutaran`, `posturMonitor`, `dasarTelepon`, `posturTelepon`, `skorMonitor`, `skorTelepon`, `skorB` |
| Keluaran keyboard/mouse | `posturKeyboard`, `posturMouse`, `skorKeyboard`, `skorMouse`, `skorC` |
| Keluaran akhir | `skorPeriferal`, `skorFinal`, `kategoriRisiko` |

Total **55 data property**. Property keluaran hanya dibuat definisinya; **jangan isi skor hasil secara manual**.

**Hasil yang harus terlihat:** nama yang diperlukan tersedia saat menambah assertion dan ketika mengetik aturan.

**Jika bermasalah / langkah cadangan:**

- Nama property tidak dikenali: pastikan dibuat pada **Data properties**, bukan Object properties atau Annotations.
- Nilai pecahan ditolak: masukkan `0.5`, bukan `0,5`, dengan datatype numerik, bukan string.
- Jangan menambahkan tiga domain terpisah `SelA`, `SelB`, `SelC` pada `baris`: beberapa domain berarti irisan, sehingga setiap sel bisa dianggap anggota ketiganya. Biarkan kosong sesuai petunjuk.
- Jika tipe data sudah tercampur, hapus assertion yang salah lalu masukkan kembali sebagai angka; mengubah label tidak mengubah datatype literal.

### Langkah 5 — Buat 10 individual staf dan isi fakta masukan

1. Pilih class `Staf` pada tab **Individuals by class**, atau gunakan tampilan Individuals yang tersedia pada **Entities**.
2. Tambahkan `Melati`, `Mawar`, `Kanaka`, `Seruni`, `Kenanga`, `Cempaka`, `Teratai`, `Padma`, `Raflesia`, dan `Edelweis`.
3. Pilih satu individual, buka panel **Data property assertions**, klik `+`, pilih property, isi nilai, lalu pilih datatype numerik/string yang tepat. Ulangi untuk seluruh tabel di bawah.
4. Satu angka dalam tabel berarti satu assertion pada individual yang bersangkutan. Tabel Markdown tidak ditempel sekaligus ke kolom nilai.

#### Asumsi yang harus dicatat sebelum mengisi data

Observasi soal belum mencakup semua kondisi tambahan worksheet. Agar solusi dapat dijalankan, gunakan asumsi terbuka berikut dan tuliskan juga pada laporan:

- Durasi pada soal adalah total harian. Gunakan cabang **jam/hari** pada worksheet, tanpa mengasumsikan sesi kontinu lebih dari satu jam. Durasi tepat **1 dan 4 jam** termasuk interval tambahan `0`; `0.5` jam/hari mendapat `-1`.
- Worksheet menyebut dudukan ideal **sekitar 3 inci**. Karena toleransi tidak diberikan, contoh operasional ini menggunakan tepat `3` sebagai kategori netral. Sudut lutut netral menggunakan `90°`; `92°` dan `95°` masuk kategori `>90°`.
- Untuk sandaran 95–110°, diasumsikan penyangga lumbar memadai. Kaki menyentuh lantai, ruang bawah meja memadai, armrest tidak rusak/tidak terlalu lebar, serta penyesuaian peralatan tidak menambah penalti karena kondisi tersebut tidak dilaporkan.
- Monitor `rendah` dipetakan ke kategori dasar 2 dan `tinggi` dengan ekstensi leher ke dasar 3. Jarak `>75 cm` menambah 1 berdasarkan batas rentang ideal 40–75 cm pada gambar; jarak tepat 75 cm tidak ditambah. Teratai diasumsikan tinggi monitor netral, dengan putaran leher 35°. Silau tidak dilaporkan sehingga tidak diberi tambahan.
- Telepon dijepit bahu menambah 2. **Tidak memakai hands-free tidak selalu berarti tidak tersedia pilihan hands-free.** Penalti `tanpaHandsFree=1` hanya diberikan kepada Kanaka dan Raflesia yang secara eksplisit dicatat demikian; untuk Melati dan Teratai nilai 0 adalah asumsi belum ada penalti tambahan tersebut. Kenanga diasumsikan memegang telepon dengan leher netral.
- Keyboard hanya dinilai dari ekstensi yang diberikan. Deviasi pergelangan, bahu terangkat karena tinggi keyboard, jangkauan benda di atas, dan platform tidak dapat disetel diasumsikan tidak menambah penalti. Bahu terangkat pada kolom **armrest** tidak otomatis menjadi fakta tentang keyboard.
- Mouse dekat keyboard diasumsikan sejajar bahu. `bedaPermukaan`, `pinchGrip`, dan `palmrest` diberi 1 hanya ketika disebutkan.

Nilai flag `0` pada kondisi yang tidak disebutkan adalah **asumsi input eksplisit**, bukan kesimpulan bahwa kondisi itu pasti tidak ada. OWL tidak otomatis menganggap fakta yang hilang bernilai salah. Solusi ini mengimplementasikan kasus dalam soal dengan asumsi di atas; belum mencakup seluruh kemungkinan postur pada worksheet.

#### 5a. Kursi dan sudut pergelangan

`armrestBermasalah`: 1 bila terlalu tinggi/rendah atau lengan tidak tersangga, 0 bila tersangga dan rileks. Bahu terangkat dan armrest terlalu tinggi adalah satu kategori dasar 2; jangan dihitung dua kali.

| Staf | sudutLutut (°) | jarakDudukanLutut (inci) | armrestBermasalah | sudutSandaran (°) | ekstensiPergelangan (°) |
| --- | --- | --- | --- | --- | --- |
| Melati | 105 | 1 | 1 | 115 | 20 |
| Mawar | 90 | 3 | 0 | 100 | 5 |
| Kanaka | 85 | 4 | 1 | 90 | 18 |
| Seruni | 95 | 3 | 1 | 105 | 10 |
| Kenanga | 110 | 2 | 1 | 112 | 5 |
| Cempaka | 90 | 3 | 0 | 100 | 20 |
| Teratai | 92 | 3 | 0 | 100 | 5 |
| Padma | 80 | 5 | 1 | 90 | 10 |
| Raflesia | 100 | 2 | 1 | 115 | 22 |
| Edelweis | 90 | 3 | 0 | 100 | 5 |

#### 5b. Monitor

`posisiMonitor` adalah string `"netral"`, `"rendah"`, atau `"tinggi"`; `putaranLeher` dalam derajat. `dokumenTanpaHolder` adalah flag 0/1. Pada editor assertion, isi teksnya dan pilih `xsd:string`; tanda kutip diperlukan saat nilai ditulis dalam aturan SWRL.

| Staf | jarakMonitor (cm) | posisiMonitor | putaranLeher (°) | dokumenTanpaHolder |
| --- | --- | --- | --- | --- |
| Melati | 80 | tinggi | 0 | 0 |
| Mawar | 60 | netral | 0 | 0 |
| Kanaka | 50 | rendah | 0 | 0 |
| Seruni | 85 | tinggi | 0 | 0 |
| Kenanga | 65 | netral | 0 | 1 |
| Cempaka | 55 | rendah | 0 | 0 |
| Teratai | 45 | netral | 35 | 0 |
| Padma | 60 | netral | 0 | 1 |
| Raflesia | 75 | rendah | 0 | 0 |
| Edelweis | 60 | netral | 0 | 0 |

#### 5c. Telepon dan mouse

Semua kolom selain `jarakTelepon` adalah flag numerik 0/1. `—` berarti **jangan buat assertion jarakTelepon** untuk pengguna headset; aturan headset tidak memerlukan jarak. Jangan memasukkan karakter `—` sebagai nilai atau mengarang jarak 0 cm.

| Staf | pakaiHeadset | jarakTelepon (cm) | teleponDijepit | tanpaHandsFree | mouseMenjangkau | bedaPermukaan | pinchGrip | palmrest |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Melati | 0 | 35 | 1 | 0 | 1 | 0 | 0 | 1 |
| Mawar | 1 | — | 0 | 0 | 0 | 0 | 0 | 0 |
| Kanaka | 0 | 35 | 0 | 1 | 1 | 1 | 0 | 0 |
| Seruni | 1 | — | 0 | 0 | 1 | 0 | 0 | 0 |
| Kenanga | 0 | 25 | 0 | 0 | 0 | 0 | 0 | 1 |
| Cempaka | 1 | — | 0 | 0 | 1 | 1 | 0 | 0 |
| Teratai | 0 | 40 | 1 | 0 | 0 | 0 | 0 | 0 |
| Padma | 1 | — | 0 | 0 | 1 | 0 | 0 | 1 |
| Raflesia | 0 | 35 | 0 | 1 | 1 | 0 | 1 | 0 |
| Edelweis | 1 | — | 0 | 0 | 0 | 0 | 0 | 0 |

#### 5d. Durasi harian

Nilai ini belum merupakan penalti durasi; aturan SWRL yang mengubah jam menjadi `-1`, `0`, atau `1`.

| Staf | durasiKursi | durasiMonitor | durasiTelepon | durasiKeyboard | durasiMouse |
| --- | --- | --- | --- | --- | --- |
| Melati | 8 | 7 | 2 | 7 | 7 |
| Mawar | 7 | 7 | 1 | 7 | 7 |
| Kanaka | 6 | 5 | 3 | 5 | 5 |
| Seruni | 8 | 8 | 1 | 8 | 8 |
| Kenanga | 5 | 4 | 2 | 4 | 4 |
| Cempaka | 6 | 6 | 0.5 | 6 | 6 |
| Teratai | 7 | 7 | 4 | 7 | 7 |
| Padma | 8 | 8 | 2 | 8 | 8 |
| Raflesia | 5 | 5 | 2 | 5 | 5 |
| Edelweis | 9 | 9 | 1 | 9 | 9 |

**Contoh input:** pilih `Cempaka`, tambahkan `durasiTelepon` bernilai `0.5` dengan datatype `xsd:decimal`. Pilih `Melati`, tambahkan `posisiMonitor` bernilai `tinggi` dengan datatype `xsd:string`.

**Hasil yang harus terlihat:** setiap staf bertipe `Staf`, memiliki 22 masukan pada tabel, kecuali pengguna headset yang tidak memerlukan `jarakTelepon` sehingga memiliki 21.

**Jika bermasalah / langkah cadangan:**

- Individual tidak muncul di bawah `Staf`: tambahkan **Types → Staf**; nama saja belum menetapkan class.
- Assertion tidak tersedia pada layout sekarang: aktifkan **Individuals by class** melalui **Window → Tabs** atau buka tampilan Individuals pada Entities.
- Staf muncul dua kali pada hasil: periksa apakah ada dua nilai untuk property yang sama. Hapus nilai salah, pertahankan satu nilai per masukan.
- Terlalu banyak input manual: buka berkas cadangan dan periksa satu staf dengan tabel ini, lalu lanjut ke langkah 8.

### Langkah 6 — Masukkan matriks worksheet sebagai pengetahuan

Satu sel dibuat sebagai individual, bukan sebagai data property baru. Contoh:

1. Pilih class `SelB`, buat individual `SelB_4_5`.
2. Isi `baris = 4`, `kolom = 5`, `nilai = 6`.
3. Artinya: pada tabel B, telepon 4 dan monitor 5 menghasilkan skor B = 6.
4. Ulangi pola tersebut dengan matriks berikut. Angka di kiri adalah **nilai baris**, header atas adalah **nilai kolom**.

#### Tabel A: baris = tinggi + dudukan; kolom = armrest + sandaran

| baris \ kolom | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 2 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| 3 | 2 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| 4 | 3 | 3 | 3 | 4 | 5 | 6 | 7 | 8 |
| 5 | 4 | 4 | 4 | 4 | 5 | 6 | 7 | 8 |
| 6 | 5 | 5 | 5 | 5 | 6 | 7 | 8 | 9 |
| 7 | 6 | 6 | 6 | 7 | 7 | 8 | 8 | 9 |
| 8 | 7 | 7 | 7 | 8 | 8 | 9 | 9 | 9 |

`skorA` adalah keluaran tabel A **sebelum** tambahan durasi kursi. `skorKursi = skorA + tambahanDurasiKursi`.

#### Tabel B: baris = skorTelepon; kolom = skorMonitor

| baris \ kolom | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 2 | 3 | 4 | 5 | 6 |
| 1 | 1 | 1 | 2 | 2 | 3 | 4 | 5 | 6 |
| 2 | 1 | 2 | 2 | 3 | 3 | 4 | 5 | 7 |
| 3 | 2 | 2 | 3 | 3 | 4 | 5 | 6 | 8 |
| 4 | 3 | 3 | 4 | 4 | 5 | 6 | 7 | 8 |
| 5 | 4 | 4 | 5 | 5 | 6 | 7 | 8 | 9 |
| 6 | 5 | 5 | 6 | 7 | 8 | 8 | 9 | 9 |

#### Tabel C: baris = skorKeyboard; kolom = skorMouse

| baris \ kolom | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 2 | 3 | 4 | 5 | 6 |
| 1 | 1 | 1 | 2 | 2 | 3 | 4 | 5 | 6 |
| 2 | 1 | 2 | 2 | 3 | 3 | 4 | 5 | 7 |
| 3 | 2 | 2 | 3 | 3 | 4 | 5 | 6 | 8 |
| 4 | 3 | 3 | 4 | 4 | 5 | 6 | 7 | 8 |
| 5 | 4 | 4 | 5 | 5 | 6 | 7 | 8 | 9 |
| 6 | 5 | 5 | 6 | 7 | 8 | 8 | 9 | 9 |
| 7 | 6 | 6 | 7 | 8 | 8 | 9 | 9 | 9 |

Skor monitor, telepon, mouse, dan keyboard pada sumbu B/C **sudah termasuk durasi masing-masing**. Jangan tambahkan durasi sekali lagi sesudah lookup B atau C.

Untuk latihan input manual pada 10 staf ini, cukup masukkan 17 sel berikut terlebih dahulu. Seluruh 176 sel tersedia pada berkas cadangan dan matriks lengkap di atas; tambahan sel diperlukan ketika masukan diubah ke kombinasi lain.

| Class | Individual | baris | kolom | nilai |
| --- | --- | --- | --- | --- |
| SelA | SelA_2_2 | 2 | 2 | 1 |
| SelA | SelA_3_2 | 3 | 2 | 2 |
| SelA | SelA_3_3 | 3 | 3 | 2 |
| SelA | SelA_4_4 | 4 | 4 | 3 |
| SelB | SelB_0_3 | 0 | 3 | 2 |
| SelB | SelB_1_2 | 1 | 2 | 2 |
| SelB | SelB_1_3 | 1 | 3 | 2 |
| SelB | SelB_1_5 | 1 | 5 | 4 |
| SelB | SelB_3_3 | 3 | 3 | 3 |
| SelB | SelB_4_3 | 4 | 3 | 4 |
| SelB | SelB_4_5 | 4 | 5 | 6 |
| SelC | SelC_1_2 | 1 | 2 | 2 |
| SelC | SelC_2_2 | 2 | 2 | 2 |
| SelC | SelC_2_3 | 2 | 3 | 3 |
| SelC | SelC_2_4 | 2 | 4 | 3 |
| SelC | SelC_3_4 | 3 | 4 | 4 |
| SelC | SelC_3_5 | 3 | 5 | 5 |

**Hasil yang harus terlihat:** contoh `SelA_4_4` bernilai 3, `SelB_4_5` bernilai 6, dan `SelC_3_4` bernilai 4. Model lengkap memiliki 56 sel A, 56 sel B, dan 64 sel C.

**Jika bermasalah / langkah cadangan:**

- Skor terasa tertukar: cocokkan label sumbu; B memakai telepon sebagai baris, C memakai keyboard sebagai baris.
- Lookup tidak menghasilkan apa pun: periksa tipe class sel, tiga assertion, dan keberadaan kombinasi baris/kolom tersebut.
- Jangan mengubah lookup menjadi penjumlahan. Contoh tabel B pada `(baris 4, kolom 5)` adalah 6, bukan 9.
- Jika input 176 sel terlalu lama, gunakan 17 sel minimum atau buka berkas `rosa-ets.owl` yang lengkap.

### Langkah 7 — Buat aturan SWRL

1. Buka **SWRLTab** dan gunakan **New** pada tabel aturan.
2. Isi **nama aturan** sesuai judul tebal, lalu tempel hanya isi blok kode pada bagian **rule**. Satu blok kode adalah satu aturan; nama tidak ditempel ke dalam tubuh aturan.
3. Simpan dan aktifkan aturan. Buat seluruh **56 aturan** pada subbagian berikut.
4. Gunakan `^` untuk DAN dan `->` untuk implikasi. Jangan mengganti dengan `AND`, `=>`, atau simbol panah dari pengolah kata.
5. Jika editor menampilkan prefix, pakai `rosa:Staf`, `rosa:sudutLutut`, dan seterusnya setelah mendaftarkan namespace `rosa:`. Blok di bawah memakai short form entitas yang sama dengan berkas cadangan.

Prefix standar:

| Prefix | Namespace |
| --- | --- |
| `rosa:` | `http://www.semanticweb.org/rsbp/ets-rosa#` |
| `swrlb:` | `http://www.w3.org/2003/11/swrlb#` |
| `sqwrl:` | `http://sqwrl.stanford.edu/ontologies/built-ins/3.4/sqwrl.owl#` |
| `xsd:` | `http://www.w3.org/2001/XMLSchema#` |

Konvensi variabel, literal, dan short form mengikuti [sintaks SWRLAPI](https://github.com/protegeproject/swrlapi/wiki/SWRLAPISWRLSyntax).

#### 7a. Skor postur kursi dan sumbu tabel A — 11 aturan

Tinggi dan dudukan dinilai masing-masing; armrest adalah `1 + flag bermasalah`; sandaran netral pada 95–110°. Lalu hitung X dan Y, belum menghitung hasil matriksnya.

**A01_tinggi_netral**

```text
Staf(?s) ^ sudutLutut(?s, ?v) ^ swrlb:equal(?v, 90) -> skorTinggi(?s, 1)
```

**A02_tinggi_rendah**

```text
Staf(?s) ^ sudutLutut(?s, ?v) ^ swrlb:lessThan(?v, 90) -> skorTinggi(?s, 2)
```

**A03_tinggi_tinggi**

```text
Staf(?s) ^ sudutLutut(?s, ?v) ^ swrlb:greaterThan(?v, 90) -> skorTinggi(?s, 2)
```

**A04_dudukan_netral**

```text
Staf(?s) ^ jarakDudukanLutut(?s, ?v) ^ swrlb:equal(?v, 3) -> skorDudukan(?s, 1)
```

**A05_dudukan_panjang**

```text
Staf(?s) ^ jarakDudukanLutut(?s, ?v) ^ swrlb:lessThan(?v, 3) -> skorDudukan(?s, 2)
```

**A06_dudukan_pendek**

```text
Staf(?s) ^ jarakDudukanLutut(?s, ?v) ^ swrlb:greaterThan(?v, 3) -> skorDudukan(?s, 2)
```

**A07_armrest**

```text
Staf(?s) ^ armrestBermasalah(?s, ?v) ^ swrlb:add(?z, 1, ?v) -> skorArmrest(?s, ?z)
```

**A08_sandaran_netral**

```text
Staf(?s) ^ sudutSandaran(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 95) ^ swrlb:lessThanOrEqual(?v, 110) -> skorSandaran(?s, 1)
```

**A09_sandaran_maju**

```text
Staf(?s) ^ sudutSandaran(?s, ?v) ^ swrlb:lessThan(?v, 95) -> skorSandaran(?s, 2)
```

**A10_sandaran_mundur**

```text
Staf(?s) ^ sudutSandaran(?s, ?v) ^ swrlb:greaterThan(?v, 110) -> skorSandaran(?s, 2)
```

**A11_sumbu**

```text
Staf(?s) ^ skorTinggi(?s, ?h) ^ skorDudukan(?s, ?d) ^ skorArmrest(?s, ?a) ^ skorSandaran(?s, ?b) ^ swrlb:add(?y, ?h, ?d) ^ swrlb:add(?x, ?a, ?b) -> sumbuAX(?s, ?x) ^ sumbuAY(?s, ?y)
```

#### 7b. Tambahan durasi lima komponen — 15 aturan

Untuk total harian `d`: `0 ≤ d < 1 → -1`; `1 ≤ d ≤ 4 → 0`; `d > 4 → 1`. Semua aturan ditulis lengkap agar langsung dapat ditempel tanpa mengganti nama property.

**D_Kursi_singkat**

```text
Staf(?s) ^ durasiKursi(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 0) ^ swrlb:lessThan(?v, 1) -> tambahanDurasiKursi(?s, -1)
```

**D_Kursi_sedang**

```text
Staf(?s) ^ durasiKursi(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 1) ^ swrlb:lessThanOrEqual(?v, 4) -> tambahanDurasiKursi(?s, 0)
```

**D_Kursi_lama**

```text
Staf(?s) ^ durasiKursi(?s, ?v) ^ swrlb:greaterThan(?v, 4) -> tambahanDurasiKursi(?s, 1)
```

**D_Monitor_singkat**

```text
Staf(?s) ^ durasiMonitor(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 0) ^ swrlb:lessThan(?v, 1) -> tambahanDurasiMonitor(?s, -1)
```

**D_Monitor_sedang**

```text
Staf(?s) ^ durasiMonitor(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 1) ^ swrlb:lessThanOrEqual(?v, 4) -> tambahanDurasiMonitor(?s, 0)
```

**D_Monitor_lama**

```text
Staf(?s) ^ durasiMonitor(?s, ?v) ^ swrlb:greaterThan(?v, 4) -> tambahanDurasiMonitor(?s, 1)
```

**D_Telepon_singkat**

```text
Staf(?s) ^ durasiTelepon(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 0) ^ swrlb:lessThan(?v, 1) -> tambahanDurasiTelepon(?s, -1)
```

**D_Telepon_sedang**

```text
Staf(?s) ^ durasiTelepon(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 1) ^ swrlb:lessThanOrEqual(?v, 4) -> tambahanDurasiTelepon(?s, 0)
```

**D_Telepon_lama**

```text
Staf(?s) ^ durasiTelepon(?s, ?v) ^ swrlb:greaterThan(?v, 4) -> tambahanDurasiTelepon(?s, 1)
```

**D_Keyboard_singkat**

```text
Staf(?s) ^ durasiKeyboard(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 0) ^ swrlb:lessThan(?v, 1) -> tambahanDurasiKeyboard(?s, -1)
```

**D_Keyboard_sedang**

```text
Staf(?s) ^ durasiKeyboard(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 1) ^ swrlb:lessThanOrEqual(?v, 4) -> tambahanDurasiKeyboard(?s, 0)
```

**D_Keyboard_lama**

```text
Staf(?s) ^ durasiKeyboard(?s, ?v) ^ swrlb:greaterThan(?v, 4) -> tambahanDurasiKeyboard(?s, 1)
```

**D_Mouse_singkat**

```text
Staf(?s) ^ durasiMouse(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 0) ^ swrlb:lessThan(?v, 1) -> tambahanDurasiMouse(?s, -1)
```

**D_Mouse_sedang**

```text
Staf(?s) ^ durasiMouse(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 1) ^ swrlb:lessThanOrEqual(?v, 4) -> tambahanDurasiMouse(?s, 0)
```

**D_Mouse_lama**

```text
Staf(?s) ^ durasiMouse(?s, ?v) ^ swrlb:greaterThan(?v, 4) -> tambahanDurasiMouse(?s, 1)
```

#### 7c. Lookup kursi dan tambahan durasi — 2 aturan

Variabel `?t` mencari individual sel yang **sekaligus** memiliki baris dan kolom sesuai staf. Tidak diperlukan fungsi array khusus.

**A12_lookup**

```text
Staf(?s) ^ sumbuAX(?s, ?x) ^ sumbuAY(?s, ?y) ^ SelA(?t) ^ kolom(?t, ?x) ^ baris(?t, ?y) ^ nilai(?t, ?z) -> skorA(?s, ?z)
```

**A13_durasi**

```text
Staf(?s) ^ skorA(?s, ?a) ^ tambahanDurasiKursi(?s, ?d) ^ swrlb:add(?z, ?a, ?d) -> skorKursi(?s, ?z)
```

#### 7d. Postur monitor dan telepon — 12 aturan

Monitor memakai satu kategori dasar (1/2/3), lalu tambahan jarak, putaran, dan dokumen. Ekstensi leher karena layar tinggi sudah tercakup dalam dasar 3 dan tidak ditambah lagi sebagai putaran.

Telepon memakai dasar **1** untuk headset/pegangan netral dalam jangkauan, atau **2** untuk jangkauan lebih dari 30 cm. Angka 2 menggantikan dasar 1 pada kategori itu; bukan `1+2`. Jepitan bahu dan ketiadaan opsi hands-free merupakan tambahan terpisah.

**B_monitor_netral**

```text
Staf(?s) ^ posisiMonitor(?s, "netral") -> dasarMonitor(?s, 1)
```

**B_monitor_rendah**

```text
Staf(?s) ^ posisiMonitor(?s, "rendah") -> dasarMonitor(?s, 2)
```

**B_monitor_tinggi**

```text
Staf(?s) ^ posisiMonitor(?s, "tinggi") -> dasarMonitor(?s, 3)
```

**B_monitor_jauh**

```text
Staf(?s) ^ jarakMonitor(?s, ?v) ^ swrlb:greaterThan(?v, 75) -> tambahanJarakMonitor(?s, 1)
```

**B_monitor_dekat**

```text
Staf(?s) ^ jarakMonitor(?s, ?v) ^ swrlb:lessThanOrEqual(?v, 75) -> tambahanJarakMonitor(?s, 0)
```

**B_leher_berputar**

```text
Staf(?s) ^ putaranLeher(?s, ?v) ^ swrlb:greaterThan(?v, 30) -> tambahanPutaran(?s, 1)
```

**B_leher_netral**

```text
Staf(?s) ^ putaranLeher(?s, ?v) ^ swrlb:lessThanOrEqual(?v, 30) -> tambahanPutaran(?s, 0)
```

**B01_monitor**

```text
Staf(?s) ^ dasarMonitor(?s, ?b) ^ tambahanJarakMonitor(?s, ?j) ^ tambahanPutaran(?s, ?p) ^ dokumenTanpaHolder(?s, ?h) ^ swrlb:add(?z, ?b, ?j, ?p, ?h) -> posturMonitor(?s, ?z)
```

**B02_headset**

```text
Staf(?s) ^ pakaiHeadset(?s, 1) -> dasarTelepon(?s, 1)
```

**B03_telepon_dekat**

```text
Staf(?s) ^ pakaiHeadset(?s, 0) ^ jarakTelepon(?s, ?j) ^ swrlb:lessThanOrEqual(?j, 30) -> dasarTelepon(?s, 1)
```

**B04_telepon_jauh**

```text
Staf(?s) ^ pakaiHeadset(?s, 0) ^ jarakTelepon(?s, ?j) ^ swrlb:greaterThan(?j, 30) -> dasarTelepon(?s, 2)
```

**B05_telepon_postur**

```text
Staf(?s) ^ dasarTelepon(?s, ?b) ^ teleponDijepit(?s, ?j) ^ tanpaHandsFree(?s, ?h) ^ swrlb:multiply(?p, 2, ?j) ^ swrlb:add(?z, ?b, ?p, ?h) -> posturTelepon(?s, ?z)
```

**BC_kiri**

```text
Staf(?s) ^ skorB(?s, ?a) ^ skorC(?s, ?b) ^ swrlb:greaterThanOrEqual(?a, ?b) -> skorPeriferal(?s, ?a)
```

**BC_kanan**

```text
Staf(?s) ^ skorB(?s, ?a) ^ skorC(?s, ?b) ^ swrlb:lessThan(?a, ?b) -> skorPeriferal(?s, ?b)
```

#### 7e. Postur mouse dan keyboard — 3 aturan

Mouse netral memiliki dasar 1, menjangkau mengubahnya menjadi 2 melalui `1 + mouseMenjangkau`; permukaan berbeda menambah 2, pinch grip menambah 1, dan palmrest di depan mouse menambah 1. Keyboard berekstensi lebih dari 15° mendapat dasar 2; selain itu dasar 1 dalam lingkup kasus ini.

**C01_mouse**

```text
Staf(?s) ^ mouseMenjangkau(?s, ?m) ^ bedaPermukaan(?s, ?b) ^ pinchGrip(?s, ?g) ^ palmrest(?s, ?p) ^ swrlb:multiply(?d, 2, ?b) ^ swrlb:add(?z, 1, ?m, ?d, ?g, ?p) -> posturMouse(?s, ?z)
```

**C02_keyboard_netral**

```text
Staf(?s) ^ ekstensiPergelangan(?s, ?v) ^ swrlb:lessThanOrEqual(?v, 15) -> posturKeyboard(?s, 1)
```

**C03_keyboard_ekstensi**

```text
Staf(?s) ^ ekstensiPergelangan(?s, ?v) ^ swrlb:greaterThan(?v, 15) -> posturKeyboard(?s, 2)
```

#### 7f. Tambahkan durasi ke monitor, telepon, keyboard, dan mouse — 4 aturan

**D_total_Monitor**

```text
Staf(?s) ^ posturMonitor(?s, ?p) ^ tambahanDurasiMonitor(?s, ?d) ^ swrlb:add(?z, ?p, ?d) -> skorMonitor(?s, ?z)
```

**D_total_Telepon**

```text
Staf(?s) ^ posturTelepon(?s, ?p) ^ tambahanDurasiTelepon(?s, ?d) ^ swrlb:add(?z, ?p, ?d) -> skorTelepon(?s, ?z)
```

**D_total_Keyboard**

```text
Staf(?s) ^ posturKeyboard(?s, ?p) ^ tambahanDurasiKeyboard(?s, ?d) ^ swrlb:add(?z, ?p, ?d) -> skorKeyboard(?s, ?z)
```

**D_total_Mouse**

```text
Staf(?s) ^ posturMouse(?s, ?p) ^ tambahanDurasiMouse(?s, ?d) ^ swrlb:add(?z, ?p, ?d) -> skorMouse(?s, ?z)
```

#### 7g. Lookup tabel B dan C — 2 aturan

**B_lookup**

```text
Staf(?s) ^ skorMonitor(?s, ?x) ^ skorTelepon(?s, ?y) ^ SelB(?t) ^ kolom(?t, ?x) ^ baris(?t, ?y) ^ nilai(?t, ?z) -> skorB(?s, ?z)
```

**C_lookup**

```text
Staf(?s) ^ skorMouse(?s, ?x) ^ skorKeyboard(?s, ?y) ^ SelC(?t) ^ kolom(?t, ?x) ^ baris(?t, ?y) ^ nilai(?t, ?z) -> skorC(?s, ?z)
```

#### 7h. Gabungkan B/C dan kursi; tentukan kategori — 7 aturan

Pada **dua matriks penggabungan terakhir di worksheet soal**, setiap sel sama dengan nilai terbesar dari kedua sumbunya. Karena itu digunakan dua cabang pembanding untuk masing-masing penggabungan. Ini hasil pembacaan matriks yang terlampir, bukan alasan untuk mengganti tabel A/B/C dengan maksimum.

Cabang kiri memakai `≥`, cabang kanan memakai `<`, sehingga saat kedua nilai sama hanya cabang kiri yang dipakai. `skorPeriferal = max(skorB, skorC)`, kemudian `skorFinal = max(skorKursi, skorPeriferal)`.

**BC_kiri**

```text
Staf(?s) ^ skorB(?s, ?a) ^ skorC(?s, ?b) ^ swrlb:greaterThanOrEqual(?a, ?b) -> skorPeriferal(?s, ?a)
```

**BC_kanan**

```text
Staf(?s) ^ skorB(?s, ?a) ^ skorC(?s, ?b) ^ swrlb:lessThan(?a, ?b) -> skorPeriferal(?s, ?b)
```

**FINAL_kiri**

```text
Staf(?s) ^ skorKursi(?s, ?a) ^ skorPeriferal(?s, ?b) ^ swrlb:greaterThanOrEqual(?a, ?b) -> skorFinal(?s, ?a)
```

**FINAL_kanan**

```text
Staf(?s) ^ skorKursi(?s, ?a) ^ skorPeriferal(?s, ?b) ^ swrlb:lessThan(?a, ?b) -> skorFinal(?s, ?b)
```

**R_rendah**

```text
Staf(?s) ^ skorFinal(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 1) ^ swrlb:lessThanOrEqual(?v, 3) -> kategoriRisiko(?s, "rendah")
```

**R_sedang**

```text
Staf(?s) ^ skorFinal(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 4) ^ swrlb:lessThanOrEqual(?v, 5) -> kategoriRisiko(?s, "sedang")
```

**R_tinggi**

```text
Staf(?s) ^ skorFinal(?s, ?v) ^ swrlb:greaterThanOrEqual(?v, 6) ^ swrlb:lessThanOrEqual(?v, 10) -> kategoriRisiko(?s, "tinggi")
```

**Hasil yang harus terlihat:** semua 56 aturan tersimpan tanpa kesalahan parser. Tidak perlu mengurutkan eksekusi secara manual; mesin melakukan forward chaining ketika fakta baru memenuhi aturan berikutnya.

**Jika bermasalah / langkah cadangan:**

- `Invalid SWRL atom predicate`: periksa ejaan dan keberadaan class/property dari langkah 3–4.
- `Unknown built-in`: pakai `swrlb:equal` (tanpa `s`), serta prefix `swrlb:`. `sqwrl:` dipakai untuk query, bukan menggantikan `swrlb:` pada aritmetika.
- Variabel pada hasil belum dikenal: bind terlebih dahulu di badan aturan, misalnya `swrlb:add(?z, ?a, ?b)` sebelum `skorKursi(?s, ?z)`.
- Rule tidak tersimpan: jangan tempel dua blok sekaligus, nama aturan, nomor urut, tanda pagar Markdown, atau backtick.
- Jika editor kesulitan dengan label entitas, gunakan short form nama teknis persis seperti tabel; periksa bahwa satu nama tidak dipakai sekaligus untuk class, property, dan variabel.
- Bila banyak aturan terlewat, buka berkas cadangan. Jangan memperbaikinya dengan mengisi `skorFinal` secara manual.

### Langkah 8 — Jalankan mesin aturan dan periksa hasil antara

1. Simpan ontologi sebelum menjalankan aturan.
2. Pada area kontrol **SWRLTab**, klik tombol bertuliskan **OWL+SWRL → Drools** atau label sejenis untuk menerjemahkan fakta dan aturan ke engine.
3. Klik **Run Drools**. Periksa konsol; jangan lanjut jika ada exception.
4. Buka subtab **Inferred Axioms** untuk melihat fakta baru, misalnya `skorFinal(Melati, 6)`.
5. Jika ingin melihat hasil sebagai **Data property assertions** pada individual, klik **Drools → OWL**. Tombol ini memindahkan hasil inferensi ke ontologi. Simpan hasilnya dengan nama berbeda, misalnya `rosa-hasil.owl`, agar berkas masukan tetap bersih.

Nama tombol memakai nama engine; yang penting urutannya **transfer → run → transfer hasil ke OWL**. Menjalankan **Reasoner → HermiT → Start** bukan pengganti eksekusi built-in SWRLAPI/Drools dan SQWRL pada panduan ini.

**Hasil yang harus terlihat:** Melati memiliki `skorA = 3`, `skorKursi = 4`, `skorB = 6`, `skorC = 4`, `skorFinal = 6`. Mawar memiliki `skorFinal = 2`.

**Jika bermasalah / langkah cadangan:**

- Inferred Axioms kosong: periksa aktivasi aturan, class `Staf`, datatype angka, dan sel matriks minimum. Jalankan kembali transfer lalu Run.
- Hasil ada di engine tetapi tidak di Entities: gunakan tombol transfer hasil **→ OWL**, atau langsung periksa dengan SQWRL pada langkah 9.
- Setelah mengubah input, skor lama masih muncul: hasil yang telah dipindahkan ke OWL menjadi assertion. **Buka kembali salinan input bersih**, ubah masukan di sana, lalu jalankan ulang. SWRL menambah fakta dan bukan mekanisme penimpaan nilai lama.
- Pesan inkonsistensi: periksa dahulu tipe literal, domain yang keliru, atau nilai ganda; jangan mengubah fakta hanya agar cocok dengan jawaban.

### Langkah 9 — Buat dan jalankan query SQWRL

1. Buka **SQWRLTab**.
2. Buat query menggunakan **New**, isi nama query, lalu tempel blok kodenya. Jika layout menempatkan editor bersama tabel aturan SWRL, buat query di sana; query dikenali oleh kepala `sqwrl:...` dan kemudian dipilih dari SQWRLTab.
3. Pilih query pada tabel, klik **Run**, lalu buka subtab hasil. SQWRL dapat membaca hasil aturan; menjalankan query sendiri tidak memindahkan hasil menjadi assertion OWL. [Dokumentasi SQWRL](https://github.com/protegeproject/swrlapi/wiki/SQWRL), [kontrol SQWRLTab](https://github.com/protegeproject/swrlapi/wiki/SQWRLQueryTab).

#### Q_Input — periksa apakah 10 staf terbaca

```text
Staf(?s) ^ sudutLutut(?s, ?v) -> sqwrl:select(?s, ?v) ^ sqwrl:orderBy(?s)
```

Harus ada 10 baris. Ini query diagnosis pertama jika query hasil akhir kosong.

#### Q_Final — skor final dan kategori setiap staf

```text
Staf(?s) ^ skorFinal(?s, ?f) ^ kategoriRisiko(?s, ?r) -> sqwrl:select(?s, ?f, ?r) ^ sqwrl:orderBy(?s)
```

Kolomnya berurutan: **staf, skor final, kategori risiko**. Harus ada 10 baris, satu per staf.

#### Q_Jejak — audit seluruh penggabungan skor

```text
Staf(?s) ^ skorA(?s, ?a) ^ skorKursi(?s, ?k) ^ skorMonitor(?s, ?m) ^ skorTelepon(?s, ?t) ^ skorB(?s, ?b) ^ skorMouse(?s, ?o) ^ skorKeyboard(?s, ?y) ^ skorC(?s, ?c) ^ skorPeriferal(?s, ?p) ^ skorFinal(?s, ?f) -> sqwrl:select(?s, ?a, ?k, ?m, ?t, ?b, ?o, ?y, ?c, ?p, ?f) ^ sqwrl:orderBy(?s)
```

Kolomnya berurutan: **staf, A sebelum durasi, kursi sesudah durasi, monitor, telepon, B, mouse, keyboard, C, periferal, final**.

#### Q_Tinggi — staf dengan skor minimal 6

```text
Staf(?s) ^ skorFinal(?s, ?f) ^ swrlb:greaterThanOrEqual(?f, 6) -> sqwrl:select(?s, ?f) ^ sqwrl:orderByDescending(?f)
```

Harus menghasilkan satu baris: **Melati, 6**, dengan asumsi yang dinyatakan pada langkah 5.

**Jika bermasalah / langkah cadangan:**

- Query belum muncul: simpan terlebih dahulu dan pastikan ada `-> sqwrl:select(...)` pada kepala query.
- `Q_Input` kosong: ontologi aktif salah, individual belum bertipe `Staf`, atau input belum lengkap.
- `Q_Input` berisi 10 baris tetapi `Q_Final` kosong: cari tahap terakhir yang sudah menghasilkan fakta dengan query di bawah, lalu periksa aturan tahap setelahnya.

  ```text
  Staf(?s) ^ skorA(?s, ?v) -> sqwrl:select(?s, ?v)
  ```

  Ulangi diagnosis dengan **mengganti property** `skorA` menjadi `skorKursi`, `skorB`, `skorC`, `skorPeriferal`, kemudian `skorFinal`.
- `skorFinal` ada tetapi `Q_Final` tidak lengkap: query tersebut juga mensyaratkan `kategoriRisiko`; periksa ketiga aturan kategori.
- Hasil ganda: cari beberapa masukan/sel dengan pasangan baris-kolom yang sama, atau skor lama yang sudah menjadi assertion OWL. Gunakan kembali input bersih.
- Prefix `sqwrl:` tidak dikenali: periksa plugin dan namespace pada langkah 7; jangan menggantinya dengan query SPARQL pada tab yang berbeda.

### Langkah 10 — Simpan bukti pengerjaan

1. Simpan `rosa-latihan.owl` sebagai versi input; bila hasil telah ditransfer, simpan terpisah sebagai `rosa-hasil.owl`.
2. Simpan hasil query ke CSV menggunakan fasilitas simpan pada subtab hasil bila tersedia.
3. Ambil tangkapan layar sendiri untuk: empat class, assertion salah satu staf, contoh sel matriks, aturan SWRL, hasil `Q_Final`, dan hasil `Q_Jejak`.
4. Baru setelah langkah-langkah tersebut selesai, gunakan **Bagian B** untuk menyusun jawaban tertulis. Tuliskan asumsi bersama hasil, bukan hanya angka finalnya.

**Hasil yang harus terlihat:** ontologi dapat dibuka kembali, query final memuat 10 staf, dan jejak skor sesuai tabel jawaban berikut.

**Jika bermasalah / langkah cadangan:** bila penyimpanan gagal, gunakan **Save As…** ke folder yang dapat ditulis. Jika ekspor CSV tidak tersedia, salin tabel hasil atau ambil tangkapan layar. Jika hasil berbeda, perbaiki fakta/aturan dengan urutan diagnosis langkah 9; jangan mengedit tabel hasil agar tampak sesuai.

## B. Jawaban pertanyaan pada soal

### B1. Apa saja fakta hasil assessment?

Fakta observasi berasal dari tabel PDF halaman 3. Ada 10 staf dengan ukuran sudut, jarak, kondisi komponen workstation, dan durasi harian. Angka `0/1` serta kategori string pada langkah 5 adalah **normalisasi** fakta untuk mesin aturan; asumsi pengisi kondisi yang tidak dilaporkan sudah dijelaskan terpisah.

Berikut kondisi kualitatif yang mendasari normalisasi tersebut; angka pengukurannya lengkap pada tabel langkah 5a–5d.

| Staf | Armrest/siku | Monitor | Telepon | Mouse |
| --- | --- | --- | --- | --- |
| Melati | Siku dan bahu terangkat. | 80 cm; layar tinggi, leher ekstensi. | 35 cm; dijepit bahu. | Menjangkau; palmrest di depan mouse. |
| Mawar | Siku tersangga; bahu rileks. | 60 cm; setinggi mata. | Headset; leher netral. | Dekat keyboard. |
| Kanaka | Siku tidak tersangga; bahu rileks. | 50 cm; layar rendah. | 35 cm; tanpa hands-free. | Menjangkau; permukaan berbeda. |
| Seruni | Armrest terlalu rendah; lengan tidak tersangga. | 85 cm; layar tinggi, leher ekstensi. | Headset; leher netral. | Menjangkau mouse. |
| Kenanga | Armrest terlalu tinggi; bahu terangkat. | 65 cm; setinggi mata; tanpa document holder. | 25 cm; telepon di tangan. | Dekat keyboard; palmrest di depan mouse. |
| Cempaka | Siku tersangga; bahu rileks. | 55 cm; layar rendah. | Headset; leher netral. | Menjangkau; permukaan berbeda. |
| Teratai | Siku tersangga; bahu rileks. | 45 cm; leher berputar 35°. | 40 cm; dijepit bahu. | Dekat keyboard. |
| Padma | Armrest terlalu tinggi; bahu terangkat. | 60 cm; setinggi mata; dokumen tanpa holder. | Headset; leher netral. | Menjangkau; palmrest di depan mouse. |
| Raflesia | Siku tidak tersangga; bahu rileks. | 75 cm; layar rendah. | 35 cm; tanpa hands-free. | Menjangkau; pinch grip. |
| Edelweis | Siku tersangga; bahu rileks. | 60 cm; setinggi mata. | Headset; leher netral. | Dekat keyboard. |

Contoh fakta terstruktur Melati sebelum reasoning:

```text
Staf(Melati)
sudutLutut(Melati, 105)
jarakDudukanLutut(Melati, 1)
armrestBermasalah(Melati, 1)
sudutSandaran(Melati, 115)
jarakMonitor(Melati, 80)
posisiMonitor(Melati, "tinggi")
jarakTelepon(Melati, 35)
teleponDijepit(Melati, 1)
ekstensiPergelangan(Melati, 20)
mouseMenjangkau(Melati, 1)
palmrest(Melati, 1)
durasiKursi(Melati, 8)
durasiMonitor(Melati, 7)
durasiTelepon(Melati, 2)
durasiKeyboard(Melati, 7)
durasiMouse(Melati, 7)
```

Blok ini adalah notasi fakta untuk penjelasan, bukan satu aturan yang ditempel ke SWRLTab. Fakta dimasukkan melalui assertion pada langkah 5. Skor merupakan **fakta turunan**, bukan hasil observasi langsung.

#### Fakta turunan: komponen kursi

Tinggi, dudukan, armrest, dan sandaran berikut adalah skor postur. A adalah hasil lookup sebelum durasi. Semua staf memiliki durasi kursi >4 jam sehingga tambahan kursi = 1.

| Staf | Tinggi | Dudukan | Armrest | Sandaran | X | Y | A | Kursi |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Melati | 2 | 2 | 2 | 2 | 4 | 4 | 3 | 4 |
| Mawar | 1 | 1 | 1 | 1 | 2 | 2 | 1 | 2 |
| Kanaka | 2 | 2 | 2 | 2 | 4 | 4 | 3 | 4 |
| Seruni | 2 | 1 | 2 | 1 | 3 | 3 | 2 | 3 |
| Kenanga | 2 | 2 | 2 | 2 | 4 | 4 | 3 | 4 |
| Cempaka | 1 | 1 | 1 | 1 | 2 | 2 | 1 | 2 |
| Teratai | 2 | 1 | 1 | 1 | 2 | 3 | 2 | 3 |
| Padma | 2 | 2 | 2 | 2 | 4 | 4 | 3 | 4 |
| Raflesia | 2 | 2 | 2 | 2 | 4 | 4 | 3 | 4 |
| Edelweis | 1 | 1 | 1 | 1 | 2 | 2 | 1 | 2 |

#### Fakta turunan: postur, durasi, dan skor akhir komponen perangkat

P = skor postur sebelum durasi; Δ = tambahan durasi; S = P + Δ. Nilai S menjadi masukan tabel B/C.

| Staf | Monitor P/Δ/S | Telepon P/Δ/S | Mouse P/Δ/S | Keyboard P/Δ/S |
| --- | --- | --- | --- | --- |
| Melati | 4 / +1 / 5 | 4 / +0 / 4 | 3 / +1 / 4 | 2 / +1 / 3 |
| Mawar | 1 / +1 / 2 | 1 / +0 / 1 | 1 / +1 / 2 | 1 / +1 / 2 |
| Kanaka | 2 / +1 / 3 | 3 / +0 / 3 | 4 / +1 / 5 | 2 / +1 / 3 |
| Seruni | 4 / +1 / 5 | 1 / +0 / 1 | 2 / +1 / 3 | 1 / +1 / 2 |
| Kenanga | 2 / +0 / 2 | 1 / +0 / 1 | 2 / +0 / 2 | 1 / +0 / 1 |
| Cempaka | 2 / +1 / 3 | 1 / -1 / 0 | 4 / +1 / 5 | 2 / +1 / 3 |
| Teratai | 2 / +1 / 3 | 4 / +0 / 4 | 1 / +1 / 2 | 1 / +1 / 2 |
| Padma | 2 / +1 / 3 | 1 / +0 / 1 | 3 / +1 / 4 | 1 / +1 / 2 |
| Raflesia | 2 / +1 / 3 | 3 / +0 / 3 | 3 / +1 / 4 | 2 / +1 / 3 |
| Edelweis | 1 / +1 / 2 | 1 / +0 / 1 | 1 / +1 / 2 | 1 / +1 / 2 |

#### Fakta turunan: hasil assessment lengkap

| Staf | Kursi | Monitor | Telepon | B | Mouse | Keyboard | C | Periferal | Final | Risiko |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Melati | 4 | 5 | 4 | 6 | 4 | 3 | 4 | 6 | 6 | tinggi |
| Mawar | 2 | 2 | 1 | 2 | 2 | 2 | 2 | 2 | 2 | rendah |
| Kanaka | 4 | 3 | 3 | 3 | 5 | 3 | 5 | 5 | 5 | sedang |
| Seruni | 3 | 5 | 1 | 4 | 3 | 2 | 3 | 4 | 4 | sedang |
| Kenanga | 4 | 2 | 1 | 2 | 2 | 1 | 2 | 2 | 4 | sedang |
| Cempaka | 2 | 3 | 0 | 2 | 5 | 3 | 5 | 5 | 5 | sedang |
| Teratai | 3 | 3 | 4 | 4 | 2 | 2 | 2 | 4 | 4 | sedang |
| Padma | 4 | 3 | 1 | 2 | 4 | 2 | 3 | 3 | 4 | sedang |
| Raflesia | 4 | 3 | 3 | 3 | 4 | 3 | 4 | 4 | 4 | sedang |
| Edelweis | 2 | 2 | 1 | 2 | 2 | 2 | 2 | 2 | 2 | rendah |

Kategori mengikuti **PDF soal halaman 4**: 1–3 rendah, 4–5 sedang, dan 6–10 tinggi. Dengan asumsi yang dipakai, terdapat **2 staf berisiko rendah, 7 sedang, dan 1 tinggi**. Melati menjadi prioritas tindakan menurut kategori soal.

#### Contoh jejak perhitungan Melati

1. Tinggi kursi: lutut 105° >90° → 2. Dudukan: 1 inci <3 → 2. Armrest bermasalah → 2. Sandaran 115° >110° → 2.
2. Y = 2+2 = 4; X = 2+2 = 4; tabel A `[baris 4, kolom 4]` → 3. Durasi kursi 8 jam → +1, sehingga kursi = **4**.
3. Monitor tinggi → 3; jarak 80 cm → +1; postur = 4. Durasi 7 jam → +1, sehingga monitor = **5**.
4. Telepon 35 cm → dasar 2; dijepit bahu → +2; postur = 4. Durasi 2 jam → 0, sehingga telepon = **4**.
5. Tabel B `[baris telepon 4, kolom monitor 5]` → **6**.
6. Mouse menjangkau → dasar 2; palmrest → +1; postur = 3. Durasi 7 jam → +1, sehingga mouse = **4**.
7. Ekstensi keyboard 20° >15° → postur 2. Durasi 7 jam → +1, sehingga keyboard = **3**.
8. Tabel C `[baris keyboard 3, kolom mouse 4]` → **4**.
9. Matriks periferal: gabungan B=6 dan C=4 → **6**. Matriks final: kursi=4 dan periferal=6 → **6**, risiko **tinggi**.

#### Kasus batas yang menjelaskan perbedaan hasil

- **Cempaka:** telepon postur 1 + durasi harian 0.5 jam (−1) = **0**. Ini valid sebagai masukan tabel B; tidak perlu dipaksa menjadi 1.
- **Kenanga:** monitor, keyboard, dan mouse tepat 4 jam/hari → tambahan **0**, bukan +1. Skor kursi 4 tetap menentukan final 4.
- **Teratai:** lutut 92° masuk `>90°`; putaran leher 35° menambah 1; telepon tepat 4 jam → tambahan 0. Final 4.
- **Raflesia:** jarak monitor tepat 75 cm belum melewati batas >75 cm, sehingga tidak ada tambahan jarak.
- **Melati dan Teratai:** bila informasi tambahan memastikan *tidak tersedia opsi hands-free*, ubah `tanpaHandsFree` menjadi 1 pada salinan input bersih. Melati akan berubah dari final **6 ke 7**; Teratai dari **4 ke 5**. Ini menunjukkan mengapa asumsi tidak boleh disembunyikan.

### B2. Knowledge representation apa yang dipilih dan apa pertimbangannya?

**Pilihan: ontologi OWL untuk struktur dan fakta, ditambah aturan produksi SWRL untuk inferensi, serta SQWRL untuk mengambil hasil.**

| Bagian | Representasi | Alasan |
| --- | --- | --- |
| Entitas | Class `Staf`, `SelA`, `SelB`, `SelC`; individual staf dan sel. | Membedakan objek penilaian dari pengetahuan tabel. |
| Pengukuran dan kondisi | Data property bertipe numerik/string. | Satuan dan kategori jelas; angka dapat diproses built-in. |
| Pengetahuan skoring | Individual sel matriks dan aturan SWRL. | Angka kombinasi mengikuti worksheet; aturan dapat diperiksa satu per satu. |
| Hasil | Property skor antara, skor final, dan kategori. | Jejak alasan tetap tersedia, bukan hanya satu angka akhir. |
| Pengambilan informasi | Query SQWRL. | Menghasilkan tabel staf, skor, dan kategori langsung dari ontologi. |

OWL mengatur vocabulari dan tipe data. SWRL mengekspresikan hubungan IF–THEN, perbandingan, aritmetika, dan pencocokan tabel. Pemisahan fakta, tabel pengetahuan, dan aturan membuat kesalahan lebih mudah dilacak. Dalam model ini, angka pengamatan tidak diubah menjadi skor final secara manual.

Keterbatasannya: OWL menggunakan open-world assumption sehingga data hilang tidak otomatis dianggap 0. SWRL bersifat monotonik sehingga hasil yang sudah menjadi assertion harus dibersihkan saat input berubah. Model ini menempelkan satu assessment pada satu staf karena soal hanya memberi satu snapshot; untuk assessment berulang, pisahkan entitas `Assessment` dari `Staf` dan tambahkan hubungan serta tanggal.

### B3. Aturan inferensi apa yang dibuat untuk reasoning?

Aturan lengkap yang dapat dieksekusi terdapat pada langkah 7. Secara konseptual, reasoning melakukan rangkaian berikut:

```text
Fakta pengamatan
  -> skor postur kursi + sumbu X/Y
  -> lookup A + durasi kursi -> skorKursi

Fakta monitor/telepon -> postur + durasi -> lookup B -> skorB
Fakta mouse/keyboard -> postur + durasi -> lookup C -> skorC

skorB dan skorC -> matriks periferal -> skorPeriferal
skorKursi dan skorPeriferal -> matriks final -> skorFinal
skorFinal -> kategoriRisiko
```

Contoh aturan: **jika** staf mempunyai sudut lutut >90°, **maka** skor tinggi kursi 2. **Jika** postur keyboard 2 dan tambahan durasi 1, **maka** skor keyboard 3. **Jika** skor final berada pada 6–10, **maka** kategori tinggi.

Mesin menjalankan **forward chaining**: fakta baru hasil suatu aturan menjadi prasyarat aturan berikutnya sampai tidak ada hasil baru. Tabel A/B/C adalah lookup dua dimensi, bukan jumlah semua faktor. Maksimum hanya dipakai pada dua matriks penggabungan terakhir yang memang memiliki pola tersebut dalam worksheet soal.

### B4. Query untuk memperoleh skor final ROSA setiap staf

```text
Staf(?s) ^ skorFinal(?s, ?f) ^ kategoriRisiko(?s, ?r) -> sqwrl:select(?s, ?f, ?r) ^ sqwrl:orderBy(?s)
```

`Staf(?s)` memilih staf, `skorFinal` mengambil angka hasil inferensi, `kategoriRisiko` mengambil kategorinya, `sqwrl:select` menentukan tiga kolom, dan `sqwrl:orderBy` mengurutkan nama staf. Hasil terverifikasi, disajikan tanpa prefix IRI agar mudah dibaca:

| Staf | Skor final | Kategori |
| --- | --- | --- |
| Cempaka | 5 | sedang |
| Edelweis | 2 | rendah |
| Kanaka | 5 | sedang |
| Kenanga | 4 | sedang |
| Mawar | 2 | rendah |
| Melati | 6 | tinggi |
| Padma | 4 | sedang |
| Raflesia | 4 | sedang |
| Seruni | 4 | sedang |
| Teratai | 4 | sedang |

Jika hanya diminta staf dan angkanya, gunakan bentuk minimal berikut. Ini tetap mengharuskan reasoning menghasilkan `skorFinal` terlebih dahulu.

```text
Staf(?s) ^ skorFinal(?s, ?f) -> sqwrl:select(?s, ?f) ^ sqwrl:orderBy(?s)
```

## C. Silabus ringkas dan referensi sintaks yang digunakan

Bagian ini menjelaskan cara menulis konstruksi dan fungsi yang benar-benar muncul pada solusi. Nama seperti `skorFinal` adalah **data property buatan kita**, bukan fungsi bawaan Protégé. `swrlb:*` adalah built-in untuk komputasi/pengujian, sedangkan `sqwrl:*` mengatur hasil query.

### C1. Urutan materi dan kemampuan yang dituju

| Urutan | Materi | Kemampuan setelah mempelajarinya | Latihan pada tugas |
| --- | --- | --- | --- |
| 1 | OWL: IRI, class, individual, data property, domain/range. | Membedakan entitas, nilai, dan skema. | Buat `Staf` serta assertion Melati. |
| 2 | Literal dan satuan. | Menulis angka, pecahan, string, dan flag dengan tepat. | `0.5` jam/hari; `"tinggi"`; jarak dalam cm/inci. |
| 3 | Atom, variabel, konjungsi, implikasi. | Membaca dan menulis aturan IF–THEN. | Aturan lutut dan sandaran. |
| 4 | Perbandingan numerik. | Membagi interval tanpa tumpang tindih. | Batas 90°, 15°, 1 jam, dan 4 jam. |
| 5 | Aritmetika dan binding. | Menghitung keluaran pada variabel pertama. | Skor postur + durasi; penalti permukaan ×2. |
| 6 | Pencocokan sel matriks. | Menggabungkan dua nilai sumbu ke satu hasil tabel. | Lookup A/B/C memakai `?t`, `?x`, dan `?y`. |
| 7 | Forward chaining dan penyimpanan inferensi. | Menjalankan engine dan menghindari skor lama. | Transfer → Run → transfer hasil bila diperlukan. |
| 8 | Query SQWRL. | Memilih kolom, mengurutkan, dan mengaudit hasil. | `Q_Final`, `Q_Jejak`, `Q_Input`, `Q_Tinggi`. |

### C2. Bentuk dasar aturan dan parameter

```text
AtomKondisi1 ^ AtomKondisi2 ^ BuiltIn(...) -> AtomHasil
```

- **Badan/kiri:** semua atom harus terpenuhi. **Kepala/kanan:** fakta yang disimpulkan; kepala query berisi operator SQWRL.
- `?s`, `?v`, dan `?z` adalah variabel, bukan nama property. Variabel berlaku lokal di satu aturan. Nilai keluaran harus sudah diperoleh/dihitung di badan sebelum dipakai di kepala.
- `Staf(?s)`: satu argumen individual; mengecek keanggotaan class.
- `sudutLutut(?s, ?v)`: dua argumen, **individual lalu literal/variabel nilai**; membaca fakta.
- `skorTinggi(?s, 2)` pada kepala: menambahkan fakta skor 2 ke individual yang sama.
- `posisiMonitor(?s, "tinggi")`: mencocokkan string persis. `"Tinggi"` berbeda dari `"tinggi"`.
- `^` berarti DAN; `->` berarti jika kondisi kiri terpenuhi, simpulkan bagian kanan. Keduanya bukan fungsi dan tidak memiliki parameter.
- `Staf(Melati)` memakai nama individual tertentu. Dalam aturan umum, `Staf(?s)` dapat mencocokkan seluruh staf.

Untuk input assertion di GUI, masukkan angka `90` sebagai literal numerik. Dalam teks SWRL, `90` juga literal numerik; `"90"` adalah string. Bentuk eksplisit seperti `"0.5"^^xsd:decimal` dapat dipakai jika perlu menentukan tipe pada teks aturan. Nilai flag 0/1 dalam model ini adalah angka, bukan literal boolean `true/false`.

### C3. Fungsi pembanding: parameter dan hasil

Semua fungsi berikut menerima **dua nilai yang sudah terikat**, `a` dan `b`, dan menguji kondisi. Jika benar, pencocokan aturan berlanjut; jika salah, kombinasi fakta itu tidak menghasilkan kepala aturan. Fungsi pembanding tidak menciptakan nilai baru. Definisi built-in bersumber dari [SWRL Member Submission, bagian 8](https://www.w3.org/submissions/SWRL/#8).

| Fungsi/signature | Jumlah/tipe parameter dalam tugas | Kondisi berhasil | Contoh | Pemakaian |
| --- | --- | --- | --- | --- |
| `swrlb:equal(a, b)` | 2 angka | a = b | `swrlb:equal(?v, 90)` | Lutut netral; dudukan 3 inci. |
| `swrlb:lessThan(a, b)` | 2 angka | a < b | `swrlb:lessThan(?v, 1)` | Durasi singkat; cabang maksimum kanan. |
| `swrlb:greaterThan(a, b)` | 2 angka | a > b | `swrlb:greaterThan(?v, 15)` | Ekstensi keyboard; durasi >4 jam. |
| `swrlb:lessThanOrEqual(a, b)` | 2 angka | a ≤ b | `swrlb:lessThanOrEqual(?v, 4)` | Batas atas durasi sedang. |
| `swrlb:greaterThanOrEqual(a, b)` | 2 angka | a ≥ b | `swrlb:greaterThanOrEqual(?v, 6)` | Risiko tinggi; cabang maksimum kiri. |

**Kesalahan dan pemulihan:** literal string atau variabel yang belum memiliki nilai dapat menyebabkan kegagalan tipe/binding. Baca property lebih dulu, misalnya `durasiTelepon(?s, ?v)`, lalu panggil pembanding. Jika dua kategori aktif sekaligus pada nilai batas, perbaiki operator `<`, `≤`, `>`, atau `≥`.

### C4. Fungsi aritmetika: keluaran berada di argumen pertama

#### `swrlb:add(result, a, b, ...)`

- Parameter pertama `result`: variabel hasil yang dapat belum terikat, atau nilai terikat yang akan diuji.
- Parameter berikutnya: suku numerik yang sudah terikat. Contoh solusi menggunakan dua atau lebih suku.
- Efek: mengikat `result` ke jumlah suku jika belum terikat; bila sudah terikat, memeriksa kecocokan nilainya.

```text
swrlb:add(?z, 3, 1)
```

Menghasilkan binding `?z = 4`. Pemakaian banyak suku dalam solusi:

```text
swrlb:add(?z, ?b, ?j, ?p, ?h)
```

Menghitung dasar monitor + tambahan jarak + tambahan putaran + tambahan dokumen. Sintaks `?z = ?b + ?j` tidak dipakai dalam editor aturan.

#### `swrlb:multiply(result, a, b, ...)`

- Parameter pertama: variabel/nilai hasil.
- Parameter berikutnya: faktor numerik yang telah terikat; contoh solusi memakai dua faktor.
- Efek: mengikat/menguji hasil perkalian.

```text
swrlb:multiply(?d, 2, ?b)
```

Jika flag beda permukaan `?b = 1`, maka `?d = 2`; jika 0, maka hasilnya 0. Demikian pula `teleponDijepit × 2` menghasilkan tambahan 0 atau 2.

Perilaku pengikatan argumen keluaran pada SWRLAPI dijelaskan dalam [SWRL Language FAQ](https://github.com/protegeproject/swrlapi/wiki/SWRLLanguageFAQ). Aritmetika dijalankan di badan aturan, lalu property hasil ditulis di kepala.

**Kesalahan dan pemulihan:** pastikan urutan hasil di depan, semua suku/faktor masukan sudah tersedia, dan jangan menjumlahkan string. Tambahan durasi `-1` adalah angka sah; jangan mengganti tipe skor dengan `xsd:positiveInteger` karena beberapa hasil antara dapat 0.

### C5. Lookup matriks bukan fungsi bawaan

```text
Staf(?s) ^ skorMonitor(?s, ?x) ^ skorTelepon(?s, ?y) ^
SelB(?t) ^ kolom(?t, ?x) ^ baris(?t, ?y) ^ nilai(?t, ?z)
-> skorB(?s, ?z)
```

| Nama | Argumen | Makna |
| --- | --- | --- |
| `SelB(?t)` | 1 individual sel | Batasi pencarian ke tabel B. |
| `kolom(?t, ?x)` | sel, angka kolom | Kolom sel harus sama dengan skor monitor staf. |
| `baris(?t, ?y)` | sel, angka baris | Baris sel harus sama dengan skor telepon staf. |
| `nilai(?t, ?z)` | sel, angka hasil | Ambil isi sel yang cocok. |
| `skorB(?s, ?z)` | staf, angka hasil | Simpan hasil sebagai skor B staf. |

Variabel yang sama memaksa kecocokan nilai: `?x` pada skor monitor dan `?x` pada kolom harus sama. Ini adalah pencocokan/join fakta. Jika sel tidak ditemukan, aturan tidak menghasilkan skor; hasilnya bukan otomatis 0.

Untuk matriks penggabungan terakhir, dua aturan pembanding memodelkan maksimum. Tidak ada pemanggilan `max(...)` dalam aturan solusi, dan tidak ada fungsi ROSA bawaan yang dapat dipanggil langsung.

### C6. Operator SQWRL: signature, parameter, dan keluaran

Operator berikut ditulis pada **kepala query**, sesudah `->`. Argumennya berasal dari variabel badan query. Hasil query adalah tabel; operator ini tidak menulis assertion baru pada ontologi.

| Operator | Parameter | Hasil/perilaku | Contoh |
| --- | --- | --- | --- |
| `sqwrl:select(v1, v2, ...)` | Satu atau lebih nilai/variabel terikat. Urutan menentukan urutan kolom. | Memilih kolom untuk setiap kecocokan. | `sqwrl:select(?s, ?f, ?r)` |
| `sqwrl:orderBy(v1, v2, ...)` | Satu atau lebih variabel kolom yang juga dipilih. | Urutan naik, misalnya nama staf alfabetis. | `sqwrl:orderBy(?s)` |
| `sqwrl:orderByDescending(v1, v2, ...)` | Satu atau lebih variabel kolom yang juga dipilih. | Urutan turun, misalnya skor terbesar dahulu. | `sqwrl:orderByDescending(?f)` |

Gabungkan operator pada kepala dengan `^`, misalnya `sqwrl:select(?s, ?f) ^ sqwrl:orderBy(?s)`. Untuk menyaring skor minimal 6, letakkan `swrlb:greaterThanOrEqual(?f, 6)` di badan, lalu pilih kolom di kepala. Contoh pada langkah 9 telah dieksekusi pada engine versi terpasang.

**Kesalahan dan pemulihan:** query kosong bukan bukti skornya 0; periksa fakta yang disyaratkan badan. Jangan menaruh `sqwrl:select` dalam aturan yang seharusnya menghasilkan property skor. Tipe dan urutan kolom ditentukan variabel yang dipilih, bukan nama query.

### C7. Kamus keluaran dan invariant pemeriksaan

| Property/kelompok | Arti dan nilai yang diharapkan dalam lingkup solusi |
| --- | --- |
| `skorTinggi`, `skorDudukan`, `skorArmrest`, `skorSandaran` | Skor postur kursi sebelum matriks; masing-masing 1 atau 2 pada data soal. |
| `sumbuAX`, `sumbuAY` | Jumlah dua subkomponen kursi sesuai label sumbu worksheet. |
| `skorA` | Hasil tabel A sebelum durasi; jangan samakan dengan `skorKursi`. |
| `tambahanDurasi*` | −1, 0, atau 1; dihitung dari jam/hari. |
| `dasarMonitor`, `dasarTelepon` | Kategori dasar sebelum tambahan faktor. |
| `tambahanJarakMonitor`, `tambahanPutaran` | Penalti 0 atau 1. |
| `posturMonitor`, `posturTelepon`, `posturMouse`, `posturKeyboard` | Skor komponen sebelum tambahan durasi. |
| `skorMonitor`, `skorTelepon`, `skorMouse`, `skorKeyboard` | Skor komponen sesudah durasi; digunakan untuk lookup B/C. |
| `skorB`, `skorC` | Hasil tabel B/C, tanpa penambahan durasi lagi. |
| `skorPeriferal` | Hasil matriks gabungan B/C. |
| `skorFinal` | Hasil matriks kursi/periferal; skala akhir 1–10. |
| `kategoriRisiko` | String `rendah`, `sedang`, atau `tinggi`, sesuai interval PDF. |

Setiap staf seharusnya memiliki **satu** nilai setiap keluaran yang diperlukan dan **satu** kategori. Hasil akhir yang hilang menunjukkan rantai prasyarat belum lengkap. Hasil ganda menunjukkan masukan, sel, atau assertion hasil lama perlu diperiksa.

## D. Sumber dan batas verifikasi

1. [PDF soal ETS RSBP](<ETS RSBP A_2026_AL.pdf>), halaman 2–5. Sumber data observasi, matriks, penalti postur/durasi, dan kategori risiko. Bila ada aturan khusus perkuliahan yang berbeda dari gambar, sesuaikan aturan serta hitung ulang; hasil di sini adalah hasil berdasarkan gambar terlampir dan asumsi yang sudah dinyatakan.
2. [Repositori resmi SWRLTab Plugin](https://github.com/protegeproject/swrltab-plugin). Acuan ketersediaan plugin dan aktivasi tab.
3. [SWRLAPI presentation syntax](https://github.com/protegeproject/swrlapi/wiki/SWRLAPISWRLSyntax). Acuan variabel, atom, literal, serta simbol aturan.
4. [W3C SWRL Member Submission](https://www.w3.org/submissions/SWRL/). Acuan semantik aturan dan fungsi pembanding/aritmetika; ini berstatus Member Submission.
5. [SWRL Language FAQ](https://github.com/protegeproject/swrlapi/wiki/SWRLLanguageFAQ). Acuan binding argumen built-in pada implementasi SWRLAPI.
6. [SQWRL](https://github.com/protegeproject/swrlapi/wiki/SQWRL) dan [SQWRLQueryTab](https://github.com/protegeproject/swrlapi/wiki/SQWRLQueryTab). Acuan pengambilan hasil aturan dan eksekusi query.

Verifikasi mencakup pemuatan ontologi, parsing ulang teks seluruh 56 aturan dan 4 query yang dicontohkan, eksekusi melalui engine yang sama dengan plugin terpasang, dan kecocokan seluruh skor antara pada 10 staf. Hasil query terverifikasi: `Q_Input` = 10 baris, `Q_Final` = 10 baris, `Q_Jejak` = 10 baris, dan `Q_Tinggi` = 1 baris. Verifikasi tersebut tidak menggantikan bukti tangkapan layar pengerjaan pengguna di GUI dan tidak memastikan kondisi ergonomi yang tidak dicatat pada soal.
