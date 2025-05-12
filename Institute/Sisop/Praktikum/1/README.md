[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ph837wyE)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241132 | Jeihan Shawmy Prasetya |
| 5025241141 | Rafi Attar Maulana |
| 5025241163 | Maulana Ikhsan |
| 5025241176 | Shifa Alya Dewi |

# Praktikum Modul 1 _(Module 1 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - New Jeans Global Teratas _(Top Global New Jeans)_](/task-1/)

- [Task 2 - Liburan Bersama Rudi _(Holiday with Rudi)_](/task-2/)

- [Task 3 - Ignatius Si Cloud Engineer _(Ignatius The Cloud Engineer)_](/task-3/)

- [Task 4 - Proxy Terbaik di New Eridu _(Best Proxy in New Eridu)_](/task-4/)

### Laporan Resmi Praktikum Modul 1 _(Module 1 Lab Work Report)_

Tulis laporan resmi di sini!

_Write your lab work report here!_


- Task 1

    a. Newjeans-a
    soal:
      
   bantulah Minji untuk mendapatkan username yang sesuai dengan kriterianya (terdapat angka 2 dan tidak terdapat underscore) dan tampilkan jumlahnya. Pastikan username yang ditampilkan berurutan berdasarkan ASCII Table (dari kecil ke besar).
    code :
```sh
        
awk -F',' '{print $2}' Documents/NewJeans/newjeans_analysis/DataStreamer.csv | sort | grep "2" | grep -v "_" | awk '{print; ++n} END { print "Total :", n }'

```

  penjelasan code :
`awk` merupakan suatu command yang bisa digunakan untuk mengambil catatan/record tertentu dalam suatu file dan melakukan operasi pada catatan/record tersebut. Sedangkan `-F` digunakan untuk mendefinisikan separator yang dituju, dalam code tersebut `-F','` digunakan untuk menentukan koma (,) sebagai pemisah field. Terdapat pula `'{print $2}'` yang digunakan untuk mencetak kolom ke-2 pada catatan/record dari 
`Documents/NewJeans/newjeans_analysis/DataStreamer.csv`.

`sort` digunakan untuk mengurutkan baris-baris yang telah dihasilkan oleh fungsi sebelumnya, dimana pada fungsi ini baris-baris tersebut diurutkan berdasarkan ASCII. `grep` merupakan command untuk mencari sebuah kata, pada kode tersebut terdapat `grep "2"` yang berarti digunakan untuk mencari record yang terdapat angka 2 di dalamnya. Adapun `gep-v"_"` , terdapat options `-v` yang digunakan untuk membalikkan pencocokan sehingga baris-baris yang tidak cocok/memiliki `"_"` yang akan diteruskan.

Terakhir, untuk command `awk`  dengan perintah `{print ++n}` untuk mencetak output dari perintah sebelumnya dan melakukan increment variabel n. `END { print "Total :", n }` akan dieksekusi setelah semua baris tersebut diproses yang akan menampilkan jumlah baris yang diproses.


   output :
```sh
  ...
uccstudio2
usul2000
valon22beauty
verdy254
VGBootCamp2
volley21145
W2S
waleed2
waveafterwave2ndlife
Wolfy2032
Wolv21
x2Twins
YOURNEWS2
Zolik22
Total : 200

```


b. Newjeans-b
    soal :

   Minji ingin mengetahui lagu apa yang paling banyak di-streaming oleh user yang memiliki username berangka. Beri tahu Minji nama lagu tersebut dan jumlah usernya. Jika jumlah user tersebut tidak mencapai 24, maka berikan pesan kepada Minji “Maaf, Minji, total streamingnya tidak sesuai harapan :(“. Jika jumlah user mencapai atau melebihi 24, berikan pesan kepada Minji “Keren, Minji! Kamu hebat <3!”.
    code :

```sh
awk -F',' '{print $2,$3}' Documents/NewJeans/newjeans_analysis/DataStreamer.csv | awk '$1 ~ /[0-9]/ {print}' | sort |
awk '{ count[$2]++}
END {
    max_count = 0
    top_song = ""
    for (song in count) {
        if (count[song] > max_count) {
            max_count = count[song]
            top_song = song
        }
    }
    if (max_count >= 24) {
        printf "Keren, Minji! Kamu hebat <3!\n"
        printf "Lagu yang paling banyak di-streaming : %s, sebanyak : %d user", top_song, max_count
 } 
        else {
        printf "Maaf, Minji, total streamingnya tidak sesuai harapan :(\n"
        printf "Lagu yang paling banyak di-streaming : %s, sebanyak : %d user", top_song, max_count
    }
}'

```
   penjelasan code :

`awk` merupakan suatu command yang bisa digunakan untuk mengambil catatan/record tertentu dalam suatu file dan melakukan operasi pada catatan/record tersebut. Sedangkan `-F` digunakan untuk mendefinisikan separator yang dituju, dalam code tersebut `-F','` digunakan untuk menentukan koma (,) sebagai pemisah field. `{print$2,$3}` akan mencetak kolom ke-2 dan ke-3 pada record/catatan dari `Documents/NewJeans/newjeans_analysis/DataStreamer.csv`

` awk '$1 ~ /[0-9]/ {print}'` dimana pada `$1` mengacu pada kolom pertama kode yang dieksekusi yaitu `$2` kolom ke-2. Pada awk, operator `~` merupakan operator pencocokan pola, pada code diatas `~ /[0-9]/` kolom pertama dicocokkan dengan suatu angkan 0-9. Kondisi `awk '$1 ~ /[0-9]/` akan bernilai benar jika pada kolom pertama tersebut mengandung setidaknya satu angka. Dilanjutkan dengan `{print}` jika kondisi tersebut telah memenuhi, akan dilanjutkan dengan mencetak baris-baris tersebut untuk dilanjutkan ke perintah setelahnya yaitu `sort` yang akan melakukan pengurutan data berdasarkan ASCII. 

`awk '{ count[$2]++}` Pada code tersebut, diperintahkan untuk menghitung yang dimana terdapat `[$2]` yang berfungsi untuk mendeteksi setiap lagu pada kolom ke-2, sehingga memunculkan jumlah setiap lagu. Kemudian terdapat `END {..}` yang akan yang akan dieksekusi setelah semua baris diproses. 
`max_count = 0; top_song = ""` berfungsi untuk menginisialisasi variabel untuk menyimpan jumlah kemunculan terbanyak dan juga top song. 
```sh
for (song in count) {
        if (count[song] > max_count) {
            max_count = count[song]
            top_song = song
        }
    }
```
Pada code diatas, digunakan untuk mengiterasi semua lagu yang telah dieksekusi pada `count[$2]++`, kemuadian akan memunculkan lagu yang paling sering distreaming dan jumlah streamingnya.

Terakhir, untuk `if (max_count >= 24) {...} else {...}` akan mencetak sesuai jumlah streamingnya, jumlah streaming terbanyak dari top song >= 24 akan mencetak :
```sh
Keren, Minji! Kamu hebat <3!
Lagu yang paling banyak di-streaming : %s, sebanyak : %d user", top_song, max_count
```
Sebaliknya, jika jumlah streaming dari top song < 24, akan mencetak :
```sh
Maaf, Minji, total streamingnya tidak sesuai harapan :(
Lagu yang paling banyak di-streaming : %s, sebanyak : %d user", top_song, max_count
```
denagan menyesuaikan `%s` dari `top_song` juga `%s` dari `max_count`.

output :
```sh
Keren, Minji! Kamu hebat <3!
Lagu yang paling banyak di-streaming : Cookie, sebanyak : 111 user
```

   c. Newjeans-c
     soal :
      Tiba-tiba Minji lupa, di album mana lagu yang paling banyak di-streaming tersebut berada. Carikan Minji nama album dari lagu yang paling banyak di-streaming di platform tersebut, beserta tahun rilisnya!
    code :
```sh
top_song=$(awk -F',' '$2 ~ /[0-9]/ {count[$3]++}
END {
    max_count = 0
    top_song = ""
    for (song in count) {
        if (count[song] > max_count) {
            max_count = count[song]
            top_song = song
        }
    }
print top_song
  }' Documents/NewJeans/newjeans_analysis/DataStreamer.csv)

awk -v top_song="$top_song" -F',' '$2 == top_song {printf "Top song : %s\nAlbum : %s\nRelease year : %s\n", top_song, $1, $3}' Documents/NewJeans/newjeans_analysis/AlbumDetails.csv
```
   penjelasan code :
`top_song=$(...)` merupakan command substitution. Pada code tsb, output dari perintah di dalam $(...) akan disimpan ke dalam variabel top_song. `awk -F',' '$2 ~ /[0-9]/ {count[$3]++} END { ... }' Documents/NewJeans/newjeans_analysis/DataStreamer.csv` pada code ini, `awk` ini membaca file 
`Documents/NewJeans/newjeans_analysis/DataStreamer.csv`. `$2 ~ /[0-9]` ini menyortir pada kolom ke-2 baris-baris tsb mengandung angka. Dilanjutkan dengan ` {count[$3]++}` yang akan menghitung setiap kode unik/lagu yang berada di kolom ke-3.

`END(...)` akan dieksekusi setelah kode sebelimnya diproses.  `max_count = 0 : top_song = ""` untuk menginisialisasi variabel untuk menyimpan jumlah kemunculan terbanyak dan juga top song.
```sh
for (song in count) {
        if (count[song] > max_count) {
            max_count = count[song]
            top_song = song
        }
    }
```
Pada code diatas, digunakan untuk mengiterasi semua lagu yang telah dieksekusi pada `count[$3]++`, kemuadian akan memunculkan lagu yang paling sering distreaming dan jumlah streamingnya.

`print top_song` akan mencetak nilai kolom ke-3 yang akan dimasukkan ke top_song.

`awk -v top_song="$top_song" -F',' '$2 == top_song {printf "Top song : %s\nAlbum : %s\nRelease year : %s\n", top_song, $1, $3}' Documents/NewJeans/newjeans_analysis/AlbumDetails.csv`, pada `awk` ini membaca `Documents/NewJeans/newjeans_analysis/AlbumDetails.csv`. `-v` yang berfungsi mendefinisikan variabel `top_song` ke dalam variabel `$top_song` diatas. Kemudian, `$2 == top_song` mendefinisikan bahwa kolom ke dua dari
Documents/NewJeans/newjeans_analysis/AlbumDetails.csv memiliki perbandingan yang sama dengan nilai top_song.Terakhir, akan di cetak menggunakan format `{printf "Top song : %s\nAlbum : %s\nRelease year : %s\n", top_song, $1, $3}`.
        output :
```sh
Top song : Cookie
Album : New Jeans
Release year : 2022
```
   d. Newjeans-d
       soal :
    1. Hitung berapa banyak pengguna yang menggunakan setiap jenis device (Tablet, Smart TV, Desktop, Mobile) untuk streaming lagu NewJeans.
    2. Hitung total durasi streaming (detik) untuk setiap device.
    3. Tentukan:
        Device paling populer yang punya user terbanyak.
        Device menang durasi yang memiliki total streaming tertinggi.
        Device ter-“loyal” berdasarkan rasio (total durasi / user) tertinggi.

 code :
```sh
awk -F',' '
NR > 1 {
    device = $7
    gsub(/^[ \t\r]+|[ \t\r]+$/, "", device) 
    totdevice[device]++
    totStreamDuration[device] += $4
}
END {
    max_stream = 0
    max_device = 0
    max_ratio = 0

    topstream = ""
    top_device = ""
    top_ratio = ""

    printf "Jumlah pengguna untuk setiap device\n"
    for (device in totdevice) {
        printf "%-10s : %d\n", device, totdevice[device]
    }

    printf "Durasi tiap device\n"
    for (device in totStreamDuration) {
        printf "%-10s : %d\n", device, totStreamDuration[device]
        if (totdevice[device] > max_device) {
            max_device = totdevice[device]
            top_device = device
        }
 if (totStreamDuration[device] > max_stream) {
            max_stream = totStreamDuration[device]
            topstream = device
        }

        ratio = totStreamDuration[device] / totdevice[device]
        if (ratio > max_ratio) {
            max_ratio = ratio
            top_ratio = device
        }
    }

    printf "\nDevice terpopuler (jumlah kemunculan): %s\n", top_device
    printf "Device menang durasi (total durasi): %s\n", topstream
    printf "Device ter-loyal (rasio durasi/kemunculan): %s\n", top_ratio
}' Documents/NewJeans/newjeans_analysis/DataStreamer.csv
```
   penjelasan code:
`awk -F',' '...' Documents/NewJeans/newjeans_analysis/DataStreamer.csv` pada code tersebut menjalankan `awk` pada `Documents/NewJeans/newjeans_analysis/DataStreamer.csv`. `NR > 1 `digunakan agar operasi melawati Number Record 1. Kemudian `device = $7` menyimpan kolom ke-7 sebagai variabel device. `gsub(/^[ \t\r]+|[ \t\r]+$/, "", device)`  digunakan untuk membersihkan string device dari whitespace di awal dan akhir, memastikan konsistensi data. `totdevice[device]++`edigunakan untuk mnghitung jumlah kemunculan setiap jenis perangkat. Kemudian terdapat `totStreamDuration[device] += $4` yang digunakan umtuk menjumlahkan durasi padak kolom keempat untuk setiap devicenya.

`END{...}` dieksekusi ketika kode-kode sebelumnya selesai diproses. `max_stream = 0; max_device = 0; max_ratio = 0` dan juga `topstream = ""
;top_device = ""; top_ratio = ""` berfungsi untuk menginisialisasi variabel yang menyimpan nilai maksimum dan nama perangkat dengan nilai maksimum.
```sh
printf "Jumlah pengguna untuk setiap device\n"
    for (device in totdevice) {
        printf "%-10s : %d\n", device, totdevice[device]
    }
```
 `printf "Jumlah pengguna untuk setiap device\n"` digunakan untuk mencetak judul. Kemudian, `loop for (device in totdevice)` mengiterasi melalui setiap jenis perangkat yang unik di array totdevice, dan untuk setiap perangkat, `printf "%-10s : %d\n", device, totdevice[device]` mencetak nama perangkat dan jumlah kemunculannya dalam format tersebut.
 ```sh
printf "Durasi tiap device\n"
    for (device in totStreamDuration) {
        printf "%-10s : %d\n", device, totStreamDuration[device]
```
Kode ini mencetak durasi streaming untuk setiap jenis perangkat . Pertama, `printf "Durasi tiap device\n"` untuk mencetak judul. Selanjutnya, `loop for (device in totStreamDuration)` mengiterasi melalui setiap jenis perangkat yang unik di array totStreamDuration, dan untuk setiap perangkat, `printf "%-10s : %d\n", device, totStreamDuration[device]` mencetak nama perangkat dan total durasi streamingnya.
```sh
if (totdevice[device] > max_device) {
    max_device = totdevice[device]
    top_device = device
}
```
Kode diatas membandingkan jumlah kemunculan perangkat saat ini `(totdevice[device])` dengan jumlah kemunculan maksimum yang ditemukan saat ini`(max_device)`. Jika jumlah kemunculan perangkat saat ini lebih besar, maka `max_device` akan diperbarui dengan jumlah kemunculan perangkat saat ini, dan `top_device` diperbarui dengan nama perangkat saat ini. Setelah loop selesai, `top_device` akan berisi nama perangkat yang paling sering muncul.

```sh
if (totStreamDuration[device] > max_stream) {
    max_stream = totStreamDuration[device]
    topstream = device
}
```
kode diatas juga membandingkan total durasi streaming perangkat saat ini, sama seperti kode sebelumnya, `totStreamDuration[device)` dengan total durasi streaming maks yang ditemukan sejauh ini `max_stream`. Jika total durasi streaming perangkat saat ini lebih besar, maka max_stream diperbarui dengan total durasi streaming perangkat saat ini, dan topstream diperbarui dengan nama perangkat saat ini.Setelah loop selesai, topstream akan berisi nama perangkat dengan total durasi streaming tertinggi.

```sh
ratio = totStreamDuration[device] / totdevice[device]
if (ratio > max_ratio) {
    max_ratio = ratio
    top_ratio = device
}
```
Kode diatas menghitung rasio durasi streaming terhadap jumlah kemunculan untuk perangkat saat ini. Kemudian, rasio ini dibandingkan dengan rasio maksimum yang ditemukan sejauh ini `max_ratio`. Jika rasio perangkat saat ini lebih besar, maka max_ratio diperbarui dengan rasio perangkat saat ini, dan top_ratio diperbarui dengan nama perangkat saat ini. Setelah loop selesai, top_ratio akan berisi nama perangkat dengan rasio durasi/kemunculan tertinggi.
```sh
printf "\nDevice terpopuler (jumlah kemunculan): %s\n", top_device
printf "Device menang durasi (total durasi): %s\n", topstream
printf "Device ter-loyal (rasio durasi/kemunculan): %s\n", top_ratio
```
Kemudian hasil-hasil diatas akan dicetak menggunakan format diatas.

   output :
```sh
pengguna untuk setiap device
Smart TV   : 1819
Tablet     : 1796
Desktop    : 1757
Mobile     : 1745
Durasi tiap device
Smart TV   : 44656368
Tablet     : 44665571
Desktop    : 42334164
Mobile     : 42474241

Device terpopuler (jumlah kemunculan): Smart TV
Device menang durasi (total durasi): Tablet
Device ter-loyal (rasio durasi/kemunculan): Tablet
```







- Task 2
> Bagian a

Kode keseluruhan:
```
#!/bin/bash

# ip address
awk '
/192.168.1.1/ { ++x }
/192.168.1.2/ { ++y }
/192.168.1.3/ { ++z }
END { print "Total request yang dibuat oleh pengguna dengan IP Address\n192.168.1.1 :", x, "kali\n192.168.1.2 :", y, "kali\n192.168.1.3 :", z, "kali" }' access.log

# status codes
awk '
/200/ { ++a }
/302/ { ++b }
/404/ { ++c }
/500/ { ++d }
END { print "Jumlah Status Code\n200 :", a, "\n302 :", b, "\n404 :", c, "\n500 :", d}' access.log

# path access.log dapat diubah tergantung dengan tempat disimpannya file
```
1. Menampilkan total request yang dibuat oleh setiap IP
```
awk '
/192.168.1.1/ { ++x }
/192.168.1.2/ { ++y }
/192.168.1.3/ { ++z }
END { print "Total request yang dibuat oleh pengguna dengan IP Address\n192.168.1.1 :", x, "kali\n192.168.1.2 :", y, "kali\n192.168.1.3 :", z, "kali" }' access.log
```
Untuk menampilkan total request yang dibuat oleh setiap IP yang ada pada access.log, kode di atas menggunakan AWK dengan meng-increment-kan setiap variabel (x, y, z) untuk setiap IP.
2. Menampilkan jumlah dari setiap status code
```
awk '
/200/ { ++a }
/302/ { ++b }
/404/ { ++c }
/500/ { ++d }
END { print "Jumlah Status Code\n200 :", a, "\n302 :", b, "\n404 :", c, "\n500 :", d}' access.log
```
Dengan menggunakan cara yang sama dari kode sebelumnya untuk menampilkan total request, kode ini juga menggunakan AWK untuk increment variabel (a, b, c, d).
> Bagian b

Kode keseluruhan:
```
#!/bin/bash

# input tanggal dan ip address
echo "Masukkan tanggal yang ingin kamu cari (format: MM/DD/YYYY)"
read tanggal
echo "Masukkan IP Address yang ingin kamu cari"
read ip_address

# cari dan tampilkan data
digit_terakhir="${ip_address##*.}"
nama_pengguna=$(awk -F ',' -v ip="$digit_terakhir" -v tgl="$tanggal" '$2 == ip && $1 == tgl {print $3}' peminjaman_computer.csv)
if [[ -n "$nama_pengguna" ]]
then echo -e "Pengguna saat itu adalah $nama_pengguna\nLog Aktivitas $nama_pengguna"

# simpan backup
mkdir -p backup
waktu=$(date +"%H%M%S")
tanggal_noslash=$(echo "$tanggal" | tr -d '/')
log_file=backup/${nama_pengguna}_${tanggal_noslash}_$waktu.log
awk '{print $4 "]: " substr($6,2) " - " substr($7,2) " - " $9}' access.log > "$log_file"

else echo "Data yang kamu cari tidak ada"
fi

# path peminjaman_computer.csv dan access.log dapat diubah tergantung dengan tempat disimpannya file
```
1. Input tanggal (format: MM/DD/YYYY) dan IP Address (format: 192.168.1.X, karena menggunakan jaringan lokal, di mana X adalah nomor komputer)
```
echo "Masukkan tanggal yang ingin kamu cari (format: MM/DD/YYYY)"
read tanggal
echo "Masukkan IP Address yang ingin kamu cari"
read ip_address
```
Kode ini menggunakan echo untuk meng-output-kan input yang harus dimasukkkan user dan read untuk membaca input.
2. Mengecek lalu memberikan message pengguna dan log aktivitas
```
digit_terakhir="${ip_address##*.}"
nama_pengguna=$(awk -F ',' -v ip="$digit_terakhir" -v tgl="$tanggal" '$2 == ip && $1 == tgl {print $3}' peminjaman_computer.csv)
if [[ -n "$nama_pengguna" ]]
then echo -e "Pengguna saat itu adalah $nama_pengguna\nLog Aktivitas $nama_pengguna"
```
Kode ini mengecek pengguna yang menggunakan komputer melalui tanggal dan IP sesuai input user. AWK digunakan untuk mencari tanggal dan IP pada peminjaman_computer.csv dengan separator file berupa koma (,) dan hanya mengambil digit terakhir IP Address (sesuai data pada file csv).
3. Menyimpan backup
```
mkdir -p backup
waktu=$(date +"%H%M%S")
tanggal_noslash=$(echo "$tanggal" | tr -d '/')

log_file=backup/${nama_pengguna}_${tanggal_noslash}_$waktu.log

awk '{print $4 "]: " substr($6,2) " - " substr($7,2) " - " $9}' access.log > "$log_file"
```
Selanjutnya, Rudi meminta untuk menyimpan hasil pencarian (jika data ditemukan) ke dalam file backup sesuai dengan format yang ia berikan.
4. Data tidak ditemukan
```
else echo "Data yang kamu cari tidak ada"
fi
```
Kode ini dijalankan jika data tidak ditemukan.
> Bagian c

Kode keseluruhan:
```
#!/bin/bash

awk -F'[, ]' '
NR==FNR {
    if(NR > 1) {
        user[$1][$2]=$3
    }
    next
}

{
    if($9 == 500) {
        split($1, ip, ".")
        
        split($4, time, ":")
        gsub(/\[/, "", time[1])

        split(time[1], date, "/")

        bulankenomor["Jan"] = "01"; bulankenomor["Feb"] = "02"; bulankenomor["Mar"] = "03"; bulankenomor["Apr"] = "04"; bulankenomor["May"] = "05"; bulankenomor["Jun"] = "06";
        bulankenomor["Jul"] = "07"; bulankenomor["Aug"] = "08"; bulankenomor["Sep"] = "09"; bulankenomor["Oct"] = "10"; bulankenomor["Nov"] = "11"; bulankenomor["Dec"] = "12";

        date_format=bulankenomor[date[2]] "/" date[1] "/" date[3]

        if (date_format in user && ip[4] in user[date_format]) {
            print user[date_format][ip[4]]
        }

    }
}' peminjaman_computer.csv access.log | sort | uniq -c | sort -r | head -1 | awk -F' ' '{print "Orang yang menemukan Error Code 500 terbanyak: " $2 "\nDengan jumlah Error Code 500 sebanyak: " $1}'

# path peminjaman_computer.csv dan access.log dapat diubah tergantung dengan tempat disimpannya file
```
1. Definisi separator
```
awk -F'[,]'
```
Mendefinisikan "," sebagai separator
2. Menyimpan data setiap user
```
NR==FNR {
    if(NR > 1) {
        user[$1][$2]=$3
    }
    next
}
```
3. Hanya memproses jika Error Code 500
```
    if($9 == 500) 
```
4. Memformat IP dan data tanggal pada access.log
```
split($1, ip, ".")
        
split($4, time, ":")
gsub(/\[/, "", time[1])

split(time[1], date, "/")

bulankenomor["Jan"] = "01"; bulankenomor["Feb"] = "02"; bulankenomor["Mar"] = "03"; bulankenomor["Apr"] = "04"; bulankenomor["May"] = "05"; bulankenomor["Jun"] = "06";
bulankenomor["Jul"] = "07"; bulankenomor["Aug"] = "08"; bulankenomor["Sep"] = "09"; bulankenomor["Oct"] = "10"; bulankenomor["Nov"] = "11"; bulankenomor["Dec"] = "12";

date_format=bulankenomor[date[2]] "/" date[1] "/" date[3]
```
5. Print data user jika tanggal dan IP sesuai
```
if (date_format in user && ip[4] in user[date_format]) {
    print user[date_format][ip[4]]
}
```
6. Mencari dan menampilkan user yang menemukan Error Code 500 terbanyak dan banyaknya Error Code 500 yang ditemukan
```
sort | uniq -c | sort -r | head -1 | awk -F' ' '{print "Orang yang menemukan Error Code 500 terbanyak: " $2 "\nDengan jumlah Error Code 500 sebanyak: " $1}'
```




- Task 3 :
Pengerjaan modulnya done
kalo pengen nge run code nya, itu install ubuntu dulu atau apapun bebas
terus install utility kek zip dsb dulu, soalnya pake utility begituan
nah begitu udha beres, tinggal run
1. register.sh = ini regist akun baru
2. login.sh = ini buat login akun
3. abis register data nya masuk ke user, bisa diliat, log nya jug aada bisa diliat
4. nyalain automation ama cron nya jan lupa
5. udah beres, tinggal diemin aja nanti run sendiri si kode ama programnya itu
hehe boi akhirnya beres task 3
















- task 4 : 

general rules: Karena file log bersifat sensitif, pastikan semua file log hanya dapat dibaca oleh pemilik file.
            Semua file log disimpan di `/home/{user}/metrics`.

1	minute5_log.sh	Script pencatatan metrics setiap 5 menit
Catat semua metrics yang diperoleh dari hasil free -m. 
Untuk hasil du -sh <target_path>, catat ukuran dari path direktori tersebut. 
Direktori yang akan dipantau adalah /home/{user}/
Masukkan semua metrics ke dalam sebuah file log bernama metrics_{YmdHms}.log
{YmdHms} adalah waktu saat script Bash dijalankan. 
contoh: jika dijalankan pada 2025-03-17 19:00:00, maka file log yang akan dibuat adalah metrics_20250317190000.log.

format log:
```
mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size
15949,10067,308,588,5573,4974,2047,43,2004,/home/$USER/test/,74M
```
cara pengerjaan:
pertama kita buat file log terlebih dahulu
time=`date '+%Y%m%d%H%M%S' `
perintah `date '+%Y%m%d%H%M%S' ` digunakan untuk mendapatkan waktu saat script dijalankan lalu disimpan dalam variabel agar mudah untuk digunakan
`cd /home/ubuntu/metrics/` mengganti direktori agar file log berada pada direktori yang benar
`touch metrics_"$time".log` pembuatan file.log dengan memanggil variabel time untuk mendapatkan format {YmdHms}
agar hanya pemilik yang bisa membaca file log maka perintah `chmod 600 metrics_"$time".log` digunakan 

selanjutnya mendapatkan metrics dengan perintah `free -m` dan `du -sh /home/ubuntu/`
output dari `free -m`:
```
                total        used        free      shared  buff/cache   available
Mem:            3868        1008        1543          50        1316        2560
Swap:           2679           0        2679
```
output dari `du -sh /home/ubuntu/` :
```
131M	/home/ubuntu/
```
untuk mendapatkan format seperti `15949,10067,308,588,5573,4974,2047,43,2004,/home/$USER/test/,74M` kita perlu memfilter metrics tersebut dengan melakukan piping `|`
pertama filter teks untuk mendapatkan angka-angka pada `free -m` menggunakan `sed 's/[^0-9 ]//g'` lalu mengganti blankspace menjadi newline agar memudahkan proses selanjutnya (supaya nanti mem dan swap bisa berada pada 1 line)
kedua swap output dari `du -sh` menggunakan awk `awk '{print $2,$1}'` 
ketiga menggabungkan langkah pertama dan kedua 
keempat mengganti newline dan blankspace menjadi koma (,) 
untuk penggantian char disini menggunakan `tr -s '(char berulang yang mau diganti)' '(sigle char pengganti)'`
kelima karena ada , pada awal dan akhir teks maka kita hilangkan menggunakan `sed 's/^,//;s/,$//'` `^,` untuk menghilangkan , di awal `,$` menghilangkan , di akhir

setelah menyelesaikan filter teks kita masukkan headder pada file log dengan menggunakan echo 
`echo mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size > metrics_"$time".log`
lalu tambahkan metrics pada baris berikutnya menggunakan `>>`

![Screenshot 2025-03-28 153809](https://github.com/user-attachments/assets/5b8b15ef-7479-4a71-9dec-d02f2d63187b)


2	agg_5min_to_hour.sh	Script agregasi log per jam
Kemudian, buat satu script untuk membuat aggregasi file log ke satuan jam. 
Script agregasi akan memiliki info dari file-file yang tergenerate tiap menit. 
Dalam hasil file aggregasi tersebut, terdapat nilai minimum, maximum, dan rata-rata dari tiap-tiap metrics. 
File aggregasi akan ditrigger untuk dijalankan setiap jam secara otomatis. 
Berikut contoh nama file hasil aggregasi. Script agregasi akan dijalankan secara otomatis setiap jam. 
Contoh nama file hasil agregasi adalah metrics_agg_2025031719.log dengan format metrics_agg_{YmdH}.log.

format log:
```
type,mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size
minimum,15949,10067,223,588,5339,4626,2047,43,1995,/home/$USER/test/,50M
maximum,15949,10387,308,622,5573,4974,2047,52,2004,/home/$USER/test/,74M
average,15949,10227,265.5,605,5456,4800,2047,47.5,1999.5,/home/$USER/test/,62M
```

langkah pengerjaan: 
dapatkan waktu satu jam yang lalu dan waktu saat ini (format {YmdHms})
buat file log terlebih dahulu
deklarasi array max min sum untuk menyimpan data tiap-tiap metrics dan count untuk mendapatkan jumlah file log metrics dalam 1 jam terakhir
lakukan looping untuk mangakses file-file log metric supaya bisa mendapatkan data masing-masing log 
`for file_log in "$direktori"/metrics_20*.log; do ` 
lalu dapatkan waktu yang ada pada penamaan file tersebut dengan melakukan filtering teks untuk mendapatkan file metrics dalam 1 jam terakhir
`times=$(echo "$file_log" | sed -E 's/[^0-9 ]//g')`
dapatkan data-data metrics pada file dengan rentan waktu 1 jam yang lalu hingga saat ini menggunakan percabangan lalu lakukan operasi aritmatika
`mem_tot=$(awk -F',' 'NR > 1{print $1}' "$file_log")` untuk mendapatkan data pada file metrics
`max[0]=$((mem_tot > max[0] ? mem_tot : max[0]))` untuk mencari value max dari semua file metrics 
`min[0]=$((mem_tot < min[0] ? mem_tot : min[0]))` mencari min
`sum[0]=$((sum[0] + mem_tot))` menjumlahkan data agar bisa mendapatkan average
setiap file yang berhasil dilakukan pendataan di atas, lakukan increment pada count 
setelah keluar dari loop dapatkan average tiap-tiap metric
terakhir masukkan headder,min,max,dan sum pada file log dengan format metrics_agg_{YmdH}.log
`echo "maximum,${max[0]},${max[1]},${max[2]},${max[3]},${max[4]},${max[5]},${max[6]},${max[7]},${max[8]},${path},${maxpath}M" >> metrics_agg_"$ymdh".log`

![Screenshot 2025-03-28 181706](https://github.com/user-attachments/assets/57eacbbf-5f35-4442-a33a-f98aec322be1)

3	uptime_monitor.sh	Script monitoring uptime dan load average setiap jam
Buat script untuk memantau **uptime dan load average server** setiap jam dan menyimpannya dalam file log bernama `uptime_{YmdH}.log`. Uptime harus diambil dari output perintah uptime, sedangkan load average diambil dari `cat /proc/loadavg`.

format log :

```
uptime,load_avg_1min,load_avg_5min,load_avg_15min
17:29:06  up  2:41,0.17,0.12,0.10
```
langkah pengerjaan:
buat file log

Output perintah `uptime`:
```
16:29:19 up  3:18,  1 user,  load average: 0,00, 0,00, 0,00
```
dengan separator `,` kita ambil argumen pertama menggunakan awk

Output perintah `cat /proc/loadavg`:
```
0.01 0.01 0.00 2/542 11003
```
dengan separator ` `(blankspace) kita ambil argumen pertama,kedua,dan ketiga menggunakan awk lalu lakukan pipe untuk mengganti ' ' dengan ','

gabungkan keduanya dengan menambahkan , diantara keduanya
`temp3=$(echo "$temp1,$temp2")`

masukkan headder dan gabungan teks uptime tersebut ke dalam file log bernama `uptime_{YmdH}.log`

![Screenshot 2025-03-28 182447](https://github.com/user-attachments/assets/d27c2110-75fb-4d27-a84d-affa8935ea3b)

![Screenshot 2025-03-28 182035](https://github.com/user-attachments/assets/837cd892-2856-475d-afe0-98910c71a4f5)


4	cleanup_log.sh	Script penghapusan log lama setiap hari
Terakhir, untuk menghemat storage, buatlah script untuk **menghapus** file log agregasi yang lebih lama dari **12 jam pertama** setiap hari. Script ini harus dijalankan setiap hari pada pukul 00:00.

**Contoh Log yang Akan Dihapus pada 2025-03-18 Pukul 00:00**

```
metrics_agg_2025031700.log
metrics_agg_2025031701.log
metrics_agg_2025031702.log
metrics_agg_2025031703.log
metrics_agg_2025031704.log
metrics_agg_2025031705.log
metrics_agg_2025031706.log
metrics_agg_2025031707.log
metrics_agg_2025031708.log
metrics_agg_2025031709.log
metrics_agg_2025031710.log
metrics_agg_2025031711.log
metrics_agg_2025031712.log
```

langkah pengerjaan:
buat file log
dapatkan waktu satu hari yang lalu dan 12 jam yang lalu
`yesterday=$(date -d "yesterday" '+%Y%m%d%H')`
`time_12_hours_ago=$(date -d "12 hours ago" '+%Y%m%d%H')`
lakukan looping untuk mencari file agregasi pada kurun waktu yesterday sampai time_12_hours_ago
lalu remove file tersebut

```
for file in "$directory"/metrics_agg_*.log ; do 
times=$(echo "$file" | sed -E 's/[^0-9 ]//g')
echo "$times $time_12_hours_ago"
if [[ $times -le $time_12_hours_ago && $times -gt $yesterday ]]; then
    #echo working
echo "$file" >> /home/ubuntu/cleanup.log
    rm "$file"
fi
done
```
untuk mengetahui file mana yang terkena dampak maka bisa menambahkan `echo "$file" >> /home/ubuntu/cleanup.log`

![Screenshot 2025-03-28 182156](https://github.com/user-attachments/assets/78a5092a-4579-4eb7-a168-c0470d7ada4d)


crontab : 
untuk menjalankan crontab setiap 5 menit bisa menggunakan `*/5 * * * *`
untuk menjalankan crontab setiap 1 jam bisa menggunakan `*/60 * * * *` atau `0 * * * *` keduanya sama-sama dijalankan pada menit 0 setiap jamnya
untuk menjalankan crontab setiap jam 00:00 bisa menggunakan `00 00 * * *`

    


        
