# Simulasi Komunikasi Dua Arah dengan DES

Program ini terdiri dari dua proses terpisah yang bertukar ciphertext melalui TCP. Enkripsi DES dibuat manual dalam C++ tanpa library kriptografi. Mode yang digunakan adalah DES-CBC dengan padding PKCS#7.

> DES memiliki key efektif 56 bit dan sudah tidak aman untuk sistem modern. Implementasi ini hanya untuk pembelajaran.

## Struktur singkat

- `server`: mendengarkan koneksi dan menerima pesan pertama.
- `client`: menghubungi server dan mengirim pesan pertama.
- `src/des.cpp`: implementasi manual DES dan CBC.
- `src/protocol.cpp`: framing TCP, IV, pengiriman, dan penerimaan.
- `tests/des_test.cpp`: known-answer test dan round-trip CBC.

Shared key `KunciDES` tersedia secara lokal pada kedua program melalui `include/protocol.hpp`. Key tidak dikirim lewat jaringan.

## Build dan test di Ubuntu/WSL

```bash
cd /mnt/c/Users/maula/Documents/Code/college/information_security
make
make test
make integration-test
```

## Menjalankan

Terminal WSL pertama:

```bash
./server 8080
```

Terminal WSL kedua:

```bash
./client 127.0.0.1 8080
```

Client mengirim lebih dahulu, kemudian server membalas. Percakapan berlangsung bergantian. Ketik `/quit` untuk mengirim perintah keluar secara terenkripsi dan menutup koneksi.

## Format data jaringan

```text
[4 byte panjang payload][8 byte IV][ciphertext DES-CBC]
```

Length-prefix dan IV tidak rahasia. Plaintext dan key tidak pernah dikirim. Ciphertext selalu memiliki panjang kelipatan 8 byte.

## Demo Wireshark

1. Mulai capture pada interface yang menampilkan trafik WSL/loopback.
2. Gunakan display filter:

   ```text
   tcp.port == 8080
   ```

3. Kirim pesan dari client dan balas dari server.
4. Pilih paket terkait, lalu **Follow > TCP Stream**.
5. Bandingkan stream dengan plaintext dan ciphertext hexadecimal yang dicetak program. Plaintext dan key tidak akan terlihat sebagai payload.

Nama interface Wireshark dapat berbeda menurut konfigurasi WSL. Jika paket tidak tampak, mulai capture pada semua interface, kirim satu pesan, lalu lihat interface mana yang memuat koneksi port 8080.

## Materi penjelasan demo

Enkripsi satu blok DES menjalankan initial permutation, pembentukan 16 subkey, 16 putaran Feistel, pertukaran bagian kiri/kanan, dan final permutation. Dalam CBC, setiap blok plaintext di-XOR dengan ciphertext sebelumnya; blok pertama menggunakan IV. Receiver menjalankan proses kebalikannya dan membuang padding setelah validasi.
