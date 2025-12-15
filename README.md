# Collision Simulation

<center> Ini merupakan simulasi tabrakan antar objek untuk memenuhi Final Project mata kuliah Struktur Data dan Algotima (Data Structure and Algorithm), yang membandingkan penggunakan dua algoritma, yaitu Brute Force dan Quadtree

## Deskripsi Algoritma
1. Brute Force: Digunakan untuk melakukan pengecekan collision dari bola1 dengan semua bola lainnya yang berada dalam window, selanjutnya antara bola2 dengan semua bola pula. Kompleksitas waktu dalam algoritma ini adalah _O(n^2)_, sehingga ia boros dan tidak efisien apabila bola dalam window dalam jumlah besar yang dapat menyebabkan frame drop.
2. Quadtree: Digunakan untuk melakukan pengecekan collision dari bola1 hanya dengan bola lain dalam area yang sama. Ia berbentuk pohon (tree) yang digunakan untuk membagi ruang 2D window menjadi bagian-bagian yang lebih kecil. Prinsipnya adalah "Divide and Conquer" (Bagi dan Taklukan). Setiap node dalam Quadtree memiliki empat anak (children): Barat Laut (NW), Timur Laut (NE), Barat Daya (SW), dan Timur Daya (SE). Kompleksitas waktu dalam Quadtree adalah _O(n \log n)_, sehingga membuatnya lebih efisien dan cepat dibanding Brute Force.



## Screen Recording
Berikut adalah screen recording saat kode dijalankan.
https://github.com/user-attachments/assets/722d09f7-edde-42af-993a-3b7814beaeb8


