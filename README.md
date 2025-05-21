# Simulasi Jejaring Sosial Sederhana C++ (Mini Social Network)

Proyek ini adalah sebuah program konsol C++ yang mengimplementasikan model dasar dari jejaring sosial. Pengguna dapat ditambahkan ke jaringan, dapat membentuk pertemanan, dan program dapat melakukan analisis dasar terhadap koneksi antar pengguna, seperti mencari teman bersama, menghitung jarak pertemanan, dan menyarankan teman baru.

## Deskripsi Proyek

Program ini dirancang untuk mendemonstrasikan penggunaan struktur data Graph untuk memodelkan hubungan dalam jejaring sosial. Interaksi dilakukan melalui antarmuka menu berbasis teks di konsol. Program ini menggunakan pemetaan nama pengguna (string) ke ID internal (integer) untuk kemudahan penggunaan sambil mempertahankan efisiensi operasi graph.

## Fitur Utama

* *Manajemen Pengguna:*
    * Menambahkan pengguna baru ke jaringan.
    * Menampilkan semua pengguna yang terdaftar.
* *Manajemen Pertemanan:*
    * Membuat hubungan pertemanan dua arah antara dua pengguna.
* *Analisis Jaringan:*
    * *Tampilkan Teman:* Melihat daftar teman langsung dari seorang pengguna.
    * *Teman Bersama (Mutual Friends):* Menemukan dan menampilkan pengguna yang berteman dengan dua pengguna yang ditentukan.
    * *Jarak Pertemanan (Degrees of Separation):* Menghitung jumlah "langkah" pertemanan terpendek antara dua pengguna menggunakan Breadth-First Search (BFS).
    * *Saran Teman:* Memberikan saran teman berdasarkan prinsip "teman dari teman" yang belum menjadi teman langsung.

## Struktur Data yang Digunakan

* *Graph (direpresentasikan oleh Adjacency List):* Struktur data inti yang memodelkan jaringan.
    * std::vector<std::list<int>> adj_list;: Digunakan sebagai adjacency list, di mana indeks luar adalah ID pengguna, dan std::list<int> di dalamnya menyimpan ID teman-teman dari pengguna tersebut.
* **std::map<std::string, int> user_to_id;**: Untuk memetakan nama pengguna (tipe std::string) ke ID internal (tipe int) yang unik.
* **std::vector<std::string> id_to_user;**: Untuk memetakan ID internal kembali ke nama pengguna, berguna saat menampilkan hasil.
* **std::queue<std::pair<int, int>>**: Digunakan dalam implementasi algoritma Breadth-First Search (BFS) untuk menghitung jarak pertemanan. Menyimpan pasangan {user_id, distance}.
* **std::set<int>**: Digunakan untuk efisiensi dalam beberapa operasi, seperti:
    * Mencari teman bersama (menyimpan teman dari pengguna pertama untuk pencarian cepat).
    * Mengumpulkan saran teman yang unik dan memastikan tidak ada duplikat.
    * Menyimpan daftar teman langsung untuk perbandingan saat memberikan saran.

## Algoritma yang Digunakan

* *Breadth-First Search (BFS):*
    * Digunakan untuk menghitung jarak pertemanan terpendek (Degrees of Separation).
    * Secara implisit digunakan dalam logika saran teman untuk menjelajahi teman hingga dua tingkat.
* *Operasi Dasar Graph:* Penambahan node (pengguna), penambahan edge (pertemanan), dan traversal adjacency list untuk mendapatkan teman.

## Cara Kompilasi

Pastikan Anda memiliki compiler C++ yang mendukung C++11 atau lebih baru (misalnya, g++).
1.  Simpan kode sebagai file .cpp (contoh: social_network.cpp).
2.  Buka terminal atau command prompt, navigasi ke direktori tempat Anda menyimpan file.
3.  Kompilasi kode menggunakan perintah berikut:

    ```bash
    g++ social_network.cpp -o social_network -std=c++11
    ```

    (Ganti social_network dengan nama eksekusi yang Anda inginkan jika perlu).

## Cara Menjalankan Program

Setelah kompilasi berhasil, jalankan program yang telah dieksekusi dari terminal:

```bash
./social_network
```
(Pada Windows, Anda mungkin menjalankan social_network.exe).
Penggunaan Program
Program akan menampilkan menu berbasis teks dengan beberapa pilihan. Masukkan nomor pilihan yang sesuai untuk melakukan aksi. Anda akan diminta untuk memasukkan nama pengguna saat diperlukan.
Menu Pilihan:
 * Tambah Pengguna
 * Tambah Pertemanan
 * Tampilkan Teman Pengguna
 * Cari Teman Bersama
 * Hitung Jarak Pertemanan (Degrees of Separation)
 * Saran Teman
 * Tampilkan Semua Pengguna
 * Keluar
Program sudah diinisialisasi dengan beberapa contoh pengguna dan pertemanan untuk memudahkan pengujian langsung.
Contoh Interaksi
--- Mini Social Network Menu ---
1. Tambah Pengguna
2. Tambah Pertemanan
3. Tampilkan Teman Pengguna
4. Cari Teman Bersama
5. Hitung Jarak Pertemanan (Degrees of Separation)
6. Saran Teman
7. Tampilkan Semua Pengguna
0. Keluar
Pilihan Anda: 3
Masukkan nama pengguna untuk melihat teman-temannya: Alice
Teman-teman dari 'Alice':
  - Bob
  - Charlie

--- Mini Social Network Menu ---
Pilihan Anda: 5
Masukkan nama pengguna awal: Alice
Masukkan nama pengguna akhir: Fiona
Jarak pertemanan antara 'Alice' dan 'Fiona' adalah: 3
