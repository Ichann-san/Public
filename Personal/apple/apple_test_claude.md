# Latihan Soal — Persiapan Entry Test Apple Developer Academy

Berisi 25 soal Tes Logika (gaya TIU CPNS / PU & PK UTBK) dan 25 soal Programming (pseudocode, OOP, dynamic programming, konsep umum).

Kerjakan dulu tanpa melihat jawaban. Kalau sudah selesai, kembali ke chat dan kirim jawabanmu — nanti aku berikan kunci jawaban, review jawabanku, dan analisa jawabanmu.

---

## Bagian 1 — Tes Logika (TIU / PU / PK)

### Deret

**1.** Lanjutkan deret berikut: 2, 6, 12, 20, 30, ... ?

**2.** Lanjutkan deret berikut: 1, 1, 2, 3, 5, 8, ... ?

**3.** Lanjutkan deret berikut: 100, 95, 85, 70, 50, ... ?

**4.** Lanjutkan deret berikut: 3, 7, 15, 31, 63, ... ?

**5.** Lanjutkan deret huruf berikut: A, C, F, J, O, ... ?

### Analogi Kata

**6.** DOKTER : PASIEN = GURU : ...
A. Sekolah B. Murid C. Buku D. Kelas E. Pelajaran

**7.** API : PANAS = ES : ...
A. Air B. Beku C. Dingin D. Cair E. Kristal

**8.** BURUNG : SARANG = MANUSIA : ...
A. Pohon B. Rumah C. Kota D. Keluarga E. Tanah

**9.** PADI : BERAS = ... : TEPUNG
A. Sawah B. Gandum C. Roti D. Jagung E. Kue

### Silogisme & Penalaran Logis

**10.** Semua mahasiswa Informatika ITS mahir logika. Budi adalah mahasiswa Informatika ITS. Apa kesimpulan yang sah?

**11.** Sebagian programmer suka kopi. Semua yang suka kopi sulit tidur malam. Apa kesimpulan yang sah?

**12.** Jika hujan turun, maka jalan basah. Jalan tidak basah. Apa kesimpulan yang sah?

**13.** Ani berkata, "Beni berbohong." Beni berkata, "Cici berbohong." Cici berkata, "Ani dan Beni berbohong." Jika hanya **satu orang** yang berkata jujur, siapakah orang itu? Jelaskan alasannya.

**14.** Lima orang — P, Q, R, S, T — berdiri dalam satu baris.
- P berada tepat di sebelah kiri Q.
- R berada di ujung kanan.
- S berada di antara T dan P.
- T berada di ujung kiri.

Tentukan urutan kelimanya dari kiri ke kanan.

### Penalaran Kuantitatif (PK)

**15.** Mana yang lebih besar: Kuantitas A = 3/7, atau Kuantitas B = 5/11?

**16.** Rata-rata dari 8 angka adalah 15. Jika salah satu angka diganti dari 10 menjadi 26, berapa rata-rata barunya?

**17.** Sebuah mobil menempuh 180 km dalam 3 jam, lalu menempuh 120 km lagi dalam 2 jam. Berapa rata-rata kecepatan mobil untuk seluruh perjalanan?

**18.** Harga sebuah barang naik 20% menjadi Rp 180.000. Berapa harga awal barang tersebut?

**19.** Dalam sebuah kotak terdapat 4 bola merah dan 6 bola biru. Jika diambil 1 bola secara acak, berapa probabilitas terambil bola merah?

### Penalaran Umum (PU)

**20.** Semua pegawai yang disiplin datang tepat waktu. Sebagian pegawai di kantor X tidak datang tepat waktu. Apa kesimpulan yang sah tentang pegawai tersebut?

**21.** "Penjualan online toko ABC meningkat 50% setelah toko tersebut menggunakan iklan media sosial. Maka, iklan media sosial adalah penyebab utama meningkatnya penjualan." Manakah pernyataan berikut yang paling **melemahkan** argumen tersebut?
A. Pada periode yang sama, toko ABC juga menurunkan harga produk hingga 30%.
B. Toko ABC juga menjual produk baru.
C. Followers media sosial toko ABC meningkat.
D. Iklan menghabiskan biaya besar.
E. Toko kompetitor tidak beriklan.

**22.** Tiga rapat (A, B, C) dijadwalkan pada hari Senin, Selasa, Rabu (satu rapat per hari).
- Rapat A tidak bisa diadakan hari Senin.
- Rapat B harus diadakan tepat satu hari sebelum Rapat C.
- Rapat A diadakan hari Rabu.

Kapan Rapat B dan Rapat C masing-masing diadakan?

**23.** Lanjutkan pola berikut: 1A, 3C, 5E, 7G, 9I, ... ?

### Sinonim & Antonim

**24.** Sinonim dari kata **BIJAKSANA** adalah ...
A. Bodoh B. Arif C. Sombong D. Ceroboh E. Pemarah

**25.** Antonim dari kata **GERSANG** adalah ...
A. Kering B. Tandus C. Subur D. Panas E. Tropis

---

## Bagian 2 — Tes Programming (Pseudocode, OOP, DP, Konsep Umum)

### Pseudocode

**1.** Apa output dari pseudocode berikut?
```
SET total = 0
FOR i = 1 TO 5
    total = total + i
END FOR
PRINT total
```

**2.** Apa output dari pseudocode berikut?
```
FUNCTION mystery(n)
    IF n <= 1 THEN RETURN n
    RETURN mystery(n-1) + mystery(n-2)
END FUNCTION
PRINT mystery(6)
```

**3.** Berapa nilai akhir `count` pada pseudocode berikut?
```
SET count = 0
FOR i = 1 TO 4
    FOR j = i TO 4
        count = count + 1
    END FOR
END FOR
PRINT count
```

**4.** Array `[5, 1, 4, 2, 8]` diurutkan menggunakan bubble sort (bandingkan elemen bersebelahan, tukar jika urutan salah, ulangi sampai terurut penuh). Berapa total swap yang terjadi?

**5.** Pseudocode berikut dimaksudkan untuk binary search, tapi mengandung bug. Temukan bug-nya dan jelaskan kapan fungsi ini akan gagal memberi hasil yang benar.
```
FUNCTION binarySearch(arr, target)
    low = 0
    high = LENGTH(arr) - 1
    WHILE low < high
        mid = (low + high) / 2
        IF arr[mid] == target THEN
            RETURN mid
        ELSE IF arr[mid] < target THEN
            low = mid + 1
        ELSE
            high = mid - 1
        END IF
    END WHILE
    RETURN -1
END FUNCTION
```

**6.** Apa isi array `arr` setelah pseudocode berikut dijalankan?
```
SET arr = [3, 7, 1, 9, 4]
SET left = 0
SET right = LENGTH(arr) - 1
WHILE left < right
    SWAP arr[left] AND arr[right]
    left = left + 1
    right = right - 1
END WHILE
PRINT arr
```

**7.** Berapa kompleksitas waktu (Big-O) dari pseudocode berikut, dalam bentuk fungsi dari `n`?
```
FOR i = 1 TO n
    j = 1
    WHILE j < n
        j = j * 2
    END WHILE
END FOR
```

**8.** Pseudocode berikut dimaksudkan untuk menjumlahkan semua elemen array, tapi mengandung bug. Temukan dan jelaskan bug-nya.
```
SET sum = 0
FOR i = 0 TO LENGTH(arr)
    sum = sum + arr[i]
END FOR
PRINT sum
```

### OOP

**9.** Pasangkan masing-masing skenario berikut dengan prinsip OOP yang paling tepat (Encapsulation, Inheritance, Polymorphism, atau Abstraction):
- (a) Class `Shape` punya method `area()`, namun `Circle` dan `Square` mengimplementasikannya secara berbeda.
- (b) Class `BankAccount` menyembunyikan variabel `balance`, hanya bisa diakses lewat method `deposit()`/`withdraw()`.
- (c) Class `Vehicle` punya properti umum yang diturunkan ke `Car` dan `Motorcycle`.
- (d) Sebuah interface/protocol mendefinisikan *apa* yang harus dilakukan class, tanpa menentukan *bagaimana* caranya.

**10.** Apa output dari kode berikut, dan prinsip OOP apa yang ditunjukkan?
```swift
class Animal {
    func makeSound() {
        print("Some sound")
    }
}
class Dog: Animal {
    override func makeSound() {
        print("Bark")
    }
}
let animals: [Animal] = [Dog(), Animal()]
for a in animals {
    a.makeSound()
}
```

**11.** Manakah pernyataan yang **benar** tentang protocol di Swift dibandingkan konsep abstract class di bahasa OOP lain?
A. Class hanya bisa inherit dari satu superclass, tapi bisa conform ke banyak protocol
B. Class bisa inherit dari banyak superclass, tapi hanya satu protocol
C. Protocol tidak pernah bisa memiliki default implementation
D. Abstract class dan protocol di Swift secara fungsional identik
E. Tidak ada yang benar

**12.** Apa output dari kode berikut? Jelaskan kenapa hasilnya seperti itu.
```swift
struct Point {
    var x: Int
}
class Box {
    var value: Int
    init(value: Int) { self.value = value }
}

var p1 = Point(x: 5)
var p2 = p1
p2.x = 10

var b1 = Box(value: 5)
var b2 = b1
b2.value = 10

print(p1.x, b1.value)
```

**13.** Apa output dari kode berikut?
```swift
class Shape {
    func area() -> Double { return 0 }
}
class Circle: Shape {
    var radius: Double
    init(radius: Double) { self.radius = radius }
    override func area() -> Double { return 3.14 * radius * radius }
}
class Square: Shape {
    var side: Double
    init(side: Double) { self.side = side }
    override func area() -> Double { return side * side }
}
let shapes: [Shape] = [Circle(radius: 2), Square(side: 3)]
var totalArea = 0.0
for s in shapes {
    totalArea += s.area()
}
print(totalArea)
```

**14.** Apa yang salah dengan kode berikut? Prinsip OOP apa yang sedang dilanggar?
```swift
class Account {
    private var balance: Double = 0
    func deposit(amount: Double) {
        balance += amount
    }
}
let acc = Account()
acc.balance += 100
```

**15.** Kamu mendesain media player dengan tipe `Song`, `Podcast`, dan `Audiobook` yang semuanya butuh fungsi `play()` tapi berperilaku berbeda. Kombinasi konsep OOP apa yang paling tepat digunakan?
A. Inheritance + Polymorphism
B. Hanya Encapsulation
C. Global function untuk setiap tipe
D. Satu class dengan if/else berdasarkan tipe
E. Tidak ada yang tepat

### Dynamic Programming

**16.** Dari soal Pseudocode #2 (`mystery(n)`), tanpa memoization, berapa total panggilan fungsi `mystery()` yang terjadi saat menghitung `mystery(5)`? (Hitung juga panggilan awalnya.)

**17.** Diberikan denominasi koin {1, 3, 4}, berapa jumlah koin minimum untuk membentuk nilai 6? Sebutkan koin apa saja yang dipakai.

**18.** Diberikan barang dengan berat = [1, 3, 4, 5] dan nilai = [1, 4, 5, 7], serta kapasitas tas = 7. Dengan 0/1 knapsack, berapa nilai maksimum yang bisa didapat, dan barang mana yang dipilih?

**19.** Tentukan panjang Longest Common Subsequence (LCS) dari string `"ABCBDAB"` dan `"BDCABA"`.

**20.** Dua pendekatan DP berikut menyelesaikan masalah yang sama. Identifikasi mana yang **top-down (memoization)** dan mana yang **bottom-up (tabulation)**, lalu jelaskan perbedaan utamanya.
```
// Pendekatan 1
FUNCTION fib(n, memo)
    IF n <= 1 THEN RETURN n
    IF memo[n] EXISTS THEN RETURN memo[n]
    memo[n] = fib(n-1, memo) + fib(n-2, memo)
    RETURN memo[n]
END FUNCTION
```
```
// Pendekatan 2
FUNCTION fib(n)
    SET table[0] = 0
    SET table[1] = 1
    FOR i = 2 TO n
        table[i] = table[i-1] + table[i-2]
    END FOR
    RETURN table[n]
END FUNCTION
```

**21.** Sebuah tangga punya `n` anak tangga. Kamu bisa naik 1 atau 2 anak tangga sekaligus. Jika `n = 6`, ada berapa cara berbeda untuk mencapai puncak tangga?

### Konsep Umum

**22.** Urutkan kompleksitas berikut dari yang **paling cepat** ke **paling lambat**: O(n log n), O(2^n), O(log n), O(n²), O(n).

**23.** Jelaskan mengapa fungsi rekursif tanpa base case yang benar akan membuat program crash. Apa istilah untuk error ini?

**24.** Kamu ingin membuat fitur "undo" pada text editor, di mana aksi paling baru harus di-undo lebih dulu. Struktur data apa yang paling tepat: Array, Queue, Stack, atau Hash Map? Jelaskan alasannya.

**25.** Apa yang terjadi saat kode berikut dijalankan, dan bagaimana cara memperbaikinya agar aman?
```swift
var name: String? = nil
print(name!.count)
```

---

*Kerjakan dulu, lalu kembali ke chat dengan jawabanmu untuk kunci jawaban + review + analisa.*
