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
