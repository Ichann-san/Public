[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9LcL5VTQ)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221000 | Student 1 Name |
| 5025221000 | Student 2 Name |
| 5025221000 | Student 3 Name |
| 5025241163 | Maulana Ikhsan |

# Praktikum Modul 2 _(Module 2 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - Trabowo & Peddy Movie Night](/task-1/)

- [Task 2 - Organize and Analyze Anthony's Favorite Films](/task-2/)

- [Task 3 - Cella’s Manhwa](/task-3/)

- [Task 4 - Pipip's Load Balancer](/task-4/)

### Laporan Resmi Praktikum Modul 2 _(Module 2 Lab Work Report)_

Tulis laporan resmi di sini!

#### Laporan Task 4, by Maulana Ikhsan
 Cara pengerjaan
 File yg terlibat :
 - client.c
 - loadbalancer.c
 - worker.c
 - sistem.log
 
 Langkah pengerjaan :
 1. Baca soalnya
 2. Dari soal nya, kita bisa tau kalo alur nya tuh gini
 	- client ngasih pesan ma jumlahnya
	- loadbalancer ngirim pesan ke pekerja
	- pekerja nyatet pesannya ke log ama ngitung
 3. maka, yg harus kita lakukan adalah
 	- set si client ini buat ngirim koneksi ke loadbalancer pake ipc
	- loadbalancer ngatur siapa nerima berapa pesan pake yg rounding itu
	- nah kan sared memory nya udah ada, si worker tinggal ngitung looping berdasar shared memory itu
 4. udah sih itu, sisanya tinggal di coding aja sama debug sampe selesai
 
 Screenshot hasil jawaban
  1. Client and Load Balancer
     - ![Pic command](https://github.com/Ichann-san/ss_sisop/blob/main/Screenshot%202025-04-24%20055758.png)
    - ![Pic result](https://github.com/Ichann-san/ss_sisop/blob/main/Screenshot%202025-04-24%20055811.png)
 2. Worker
     - ![Pic command](https://github.com/Ichann-san/ss_sisop/blob/main/Screenshot%202025-04-24%20055847.png)
    - ![Pic result](https://github.com/Ichann-san/ss_sisop/blob/main/Screenshot%202025-04-24%20055856.png)
 
 Kendala
 1. shared memorynya gabisa konek bjirr -> ternyata salah key typo
 2. pass memory dari balancer ke workernya tricky cik, ini bisa pake 2 metode:
     - catat semua terus kirim sekaligus -> ini aku bingung load nya gimana, jadi gagal
     - catat and kirim berulang gitu -> akhirnya gini biar gampang
 3. ipc pusing cik -> spam tutor mas mas india dulu jadinya
 4. looping nya tricky, ini berkali kali kejebak di infinite loop -> Taunya gegara pake cara load semua dulu jadi gaberes beres, akhirnya ganti cara dan done
 5. keknya kalo misal input nya aneh, ini kode bakal eror

_Write your lab work report here!_
