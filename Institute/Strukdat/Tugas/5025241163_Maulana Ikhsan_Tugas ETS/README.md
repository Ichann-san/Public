# Laporan Soal ETS Struktur Data


### [Daftar Soal](Soal.pdf)
1. [Evaluasi perintah gerakan robot menggunakan stack](#evaluasi-perintah-gerakan-robot-menggunakan-stack)
2. [Simulasi antrian darurat dengan prioritas unik](#simulasi-antrian-darurat-dengan-prioritas-unik)
3. [Pohon warisan keluarga](#pohon-warisan-keluarga)

- ## Evaluasi perintah gerakan robot menggunakan stack
  1. Deskripsi  
	     Soal ini memerintahkan kita untuk membuat sebuah algoritma penentuan lokasi akhir robot berdasar command arah gerak yg diberikan user.
       - Format input : Sebuah string s tanpa spasi yang berisi command dari user
       - Format output : Lokasi akhir dari robot yang dipetakan pada koordinat (x, y)
       - List command : ('U'=Up), ('D'=Down), ('R'=Right), ('L'=Left), ('B'=Backspace)

  2. Pengerjaan
     - Inisialisasi template stack(ada template dari modul tinggal diubah aja)
     - Inisialisasi titik awal(pair x, y) di lokasi (0, 0)
     - Input string
     - Looping dari awal string sampe selesai untuk perubahan posisi
     - Untuk setiap i:
       - If i adalah 'U', 'D', 'R', atau 'L', maka delta robot berubah
       - If i adalah 'B', maka pop isi stack untuk undo movement
     - Ouput hasil akhir berupa (x, y)
       
  3. Hasil akhir dan testcase  
       Berikut merupakan output dari program berdasar tescases yang diberikan  
       Testcases:
       1. - Input: `UURDBBL`
          - Output: ![image](https://github.com/user-attachments/assets/c0e56cdc-0511-463a-a933-a4356727f642)
       2. - Input: `UIAUUIAUAIUIUIA`
          - Output: ![image](https://github.com/user-attachments/assets/c0e94a33-3ed8-49f6-bc7a-5a7c18ec5450)
       3. - Input: `OKGASOKGASTAMBAHDUATORANGGAS`
          - Output: ![image](https://github.com/user-attachments/assets/74599438-fa8b-4a28-af1f-8801b9b79803)


- ## Simulasi antrian darurat dengan prioritas unik
    1. Deskripsi  
	     Soal ini memerintahkan kita untuk membuat sebuah menu pelayanan panggilan darurat yang bisa memproses semua laporan dll hanya dengan 1 klik.
       - Format input :
           - Sebuah interger x mengindikasikan aksi yang akan dilakukan
           - Input tambahan yang merupakan follow up dari input x
       - Format output : Keterangan penjelas untuk setiap aksi input yang dilakukan
       - Keterangan : Menu interaktif akan terus display hingga user memilih untuk keluar

  2. Pengerjaan
     - Inisialisasi template priority queue berbasis linkedlist(ada template dari modul tinggal diubah aja)
     - Modifikasi pq agar bisa menampung berbagai data
     - Inisialisasi fungsi yang dibutuhkan untuk pemrosesan aksi
     - Input interger x
     - Gunakan do-while(biar jalan dulu) untuk menentukan arah kode
     - while x!=4, lakukan aksi follow up
     - Aksi follow up:
       - `x==1` lakukan aksi bikin laporan
       - `x==2` proses laporan yg sudah tercatat
       - `x==3` display semua laporan dalam queue
       - `x==4` exit
       
  3. Hasil akhir dan testcase  
       Berikut merupakan output dari program berdasar tescases yang diberikan  
       Testcases:
       1. - Input: `1`, follow up dengan `1` -> `Maulana Ikhsan` -> `3`
          - Output: ![image](https://github.com/user-attachments/assets/4d71f657-0cac-4036-b2a7-4a38c32462f5)

       2. - Input: `3`
          - Output: ![image](https://github.com/user-attachments/assets/adcdd0ca-4680-492f-9b6a-f4ff10644998)

       3. - Input: `2`
          - Output: ![image](https://github.com/user-attachments/assets/d748d693-8ab7-4326-bf46-f4cbd0028a8c)

       4. - Input: `4`
          - Output: ![image](https://github.com/user-attachments/assets/8297c4c9-c181-47f0-8a95-dfa0919952df)


- ## Pohon warisan keluarga
  1. Deskripsi  
	     Soal ini memerintahkan kita untuk membuat sebuah simulasi pembagian warisan menggunakan binary tree.
       - Format input :
           - Sebuah interger x mengindikasikan aksi yang akan dilakukan
           - Input tambahan yang merupakan follow up dari input x
       - Format output : Keterangan penjelas untuk setiap aksi input yang dilakukan
       - Keterangan : Menu interaktif akan terus display hingga user memilih untuk keluar

  3. Pengerjaan
     - Inisialisasi template tree(ada template dari modul tinggal diubah aja)
     - Modifikasi tree agar bisa menampung berbagai data
     - Inisialisasi fungsi yang dibutuhkan untuk pemrosesan aksi
     - Input interger x
     - Gunakan do-while(biar jalan dulu) untuk menentukan arah kode
     - while x!=4, lakukan aksi follow up
     - Aksi follow up:
       - `x==1` tambah anggota keluarga
       - `x==2` tampilkan pohon silsilah
       - `x==3` simulasi ada yg mati
       - `x==4` exit
       
  4. Hasil akhir dan testcase  
       Berikut merupakan output dari program berdasar tescases yang diberikan  
       Testcases:
       1. - Input: `1`, follow up dengan `87` -> `Kakek` -> `666`
          - Output: ![image](https://github.com/user-attachments/assets/c2e4770d-cd75-48c2-aa9d-36c6f8d5442b)

       2. - Input: `1`, follow up dengan `46` -> `Bapak` -> `371`
          - Output: ![image](https://github.com/user-attachments/assets/6e2c4453-56bf-41bf-a918-0fbeaf82def3)

       3. - Input: `1`, follow up dengan `42` -> `Ibu` -> `0`
          - Output: ![image](https://github.com/user-attachments/assets/333b55f4-bf51-4f4e-aaa6-a80d6dbeee95)

       4. - Input: `1`, follow up dengan `21` -> `Anak1` -> `0`
          - Output: ![image](https://github.com/user-attachments/assets/d86ed68b-1518-42e4-8674-fe3bb2ff5506)

       5. - Input: `1`, follow up dengan `19` -> `Anak2` -> `0`
          - Output: ![image](https://github.com/user-attachments/assets/72ef98f6-9e7b-477d-a8b6-5981419ecdde)

       6. - Input: `2`
          - Output: ![image](https://github.com/user-attachments/assets/06b1090a-e849-4851-95f8-8ac5556c9a31)
  
       7. - Input: `3`, follow up dengan `46`
          - Output: ![image](https://github.com/user-attachments/assets/c86eff32-b18e-4cfa-9422-36fbc2ebd787)

       8. - Input: `2`
          - Output: ![image](https://github.com/user-attachments/assets/ebcf8ac1-6db2-4c3f-be5b-30ac4bebb37b)

       9. - Input: `3`, follow up dengan `87`
          - Output: ![image](https://github.com/user-attachments/assets/522f0c28-ab24-41bd-9d0c-c62becc92a99)

       10. - Input: `2`
          - Output: ![image](https://github.com/user-attachments/assets/d54e8287-e47b-4c8f-a3ef-c16eb00db21a)
  
       11. - Input: `4`
          - Output: ![image](https://github.com/user-attachments/assets/60feb3e2-d149-49a3-9b0f-0a1301db7b3d)


