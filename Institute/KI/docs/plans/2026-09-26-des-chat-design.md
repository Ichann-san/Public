# DES TCP Chat Design

## Tujuan

Membuat simulasi komunikasi dua arah antara dua proses terpisah di Ubuntu/WSL. Isi pesan dienkripsi sebelum dikirim melalui TCP dan baru didekripsi setelah diterima.

## Desain yang disetujui

- Dua executable: `server` dan `client`.
- Socket TCP POSIX pada port 8080 secara default.
- Implementasi DES dibuat manual, tanpa library kriptografi.
- Mode DES-CBC dengan IV 8 byte baru untuk setiap pesan.
- PKCS#7 digunakan agar panjang plaintext menjadi kelipatan 8 byte.
- Key tersedia secara lokal pada kedua program dan tidak dikirim melalui jaringan.
- Paket terdiri dari length-prefix 4 byte, IV 8 byte, dan ciphertext.
- Percakapan berlangsung bergantian; client mengirim lebih dahulu.
- Perintah `/quit` juga dienkripsi sebelum dikirim.

## Validasi

- Known-answer test DES:
  - key `133457799BBCDFF1`
  - plaintext `0123456789ABCDEF`
  - ciphertext `85E813540F0AB405`
- Round-trip CBC untuk berbagai panjang pesan.
- Tes integrasi manual menggunakan dua terminal WSL.
- Wireshark dengan filter `tcp.port == 8080` untuk menunjukkan bahwa plaintext dan key tidak tampak pada stream.

## Batasan

DES hanya digunakan untuk pembelajaran dan tidak aman untuk penggunaan modern. Program tidak mencakup autentikasi pesan, GUI, banyak client, atau mekanisme pertukaran key.
