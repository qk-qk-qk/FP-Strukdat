<h1 align="center">Collision Simulator</h1>

Program ini merupakan simulasi tabrakan antar objek untuk memenuhi Final Project mata kuliah Struktur Data dan Algotima (Data Structure and Algorithm), yang membandingkan penggunaan dua algoritma, yaitu Brute Force dan Quadtree. Bahasa keseluruhan menggunakan C++ dan library raylib.

## Deskripsi Algoritma
1. Brute Force:
Digunakan untuk melakukan pengecekan collision dari bola1 dengan semua bola lainnya yang berada dalam window, selanjutnya antara bola2 dengan semua bola pula. Kompleksitas waktu dalam algoritma ini adalah _O(n^2)_, sehingga ia boros dan tidak efisien apabila bola dalam window dalam jumlah besar yang dapat menyebabkan frame drop.
3. Quadtree:
Digunakan untuk melakukan pengecekan collision dari bola1 hanya dengan bola lain dalam area yang sama. Ia berbentuk pohon (tree) yang digunakan untuk membagi ruang 2D window menjadi bagian-bagian yang lebih kecil. Prinsipnya adalah "Divide and Conquer" (Bagi dan Taklukan). Setiap node dalam Quadtree memiliki empat anak (children): Barat Laut (NW), Timur Laut (NE), Barat Daya (SW), dan Timur Daya (SE). Kompleksitas waktu dalam Quadtree adalah _O(n \log n)_, sehingga membuatnya lebih efisien dan cepat dibanding Brute Force.



## Screen Recording
Berikut adalah screen recording saat kode dijalankan.

https://github.com/user-attachments/assets/722d09f7-edde-42af-993a-3b7814beaeb8

## Code Snippet
Berikut beberapa bagian dari program yang menjadi dasar berjalannya program tersebut,
1. Pemilihan Algoritma  
   Berikut adalah bagian untuk menentukan algoritma apa yang akan digunakan. Untuk default, menggunakan algoritma Quadtree dan dapat diubah oleh user.
```cpp
bool useQuadtree = true;
if (IsKeyPressed(KEY_Q)) useQuadtree = true;
if (IsKeyPressed(KEY_B)) useQuadtree = false;
DrawText(useQuadtree ? "Mode: Quadtree" : "Mode: Brute Force", 10, 10, 20, WHITE);
```

2. Penggunaan Brute Force  
   Berikut adalah penggunaan algoritma Brute Force dalam program.
```cpp
        if(!useQuadtree){for (int i = 0; i < ballCount; i++){
            circlemovement(speedX[i], speedY[i], radius, loc[i]);
            BoundaryCircle(loc[i], speedX[i], speedY[i], radius);
        }
        for (int i = 0; i < ballCount; i++) {
            for (int j = i + 1; j < ballCount; j++) {
                CircleCollision(
                    loc[i], loc[j],
                    speedX[i], speedY[i],
                    speedX[j], speedY[j],
                    radius
                );
            }
        }
    }
```

3. Penggunaan Quadtree  
   Berikut adalah penggunaan algoritma Quadtree dalam program.
```cpp
    else {
    // Quad Tree
    for (int i = 0; i < ballCount; i++){
        circlemovement(speedX[i], speedY[i], radius, loc[i]);
        BoundaryCircle(loc[i], speedX[i], speedY[i], radius);
    }
    Quadtree qt({0, 0, (float)panjang, (float)lebar});

    for (int i = 0; i < ballCount; i++) {
        qt.insert(i, loc[i]);
    }

    for (int i = 0; i < ballCount; i++) {
        AABB range = {
            loc[i].x - radius*2,
            loc[i].y - radius*2,
            radius*4,
            radius*4
        };

        vector<int> candidates;
        qt.query(range, candidates);

        for (int j : candidates) {
            if (i != j && i < j) {
                CircleCollision(
                    loc[i], loc[j],
                    speedX[i], speedY[i],
                    speedX[j], speedY[j],
                    radius
                );
            }
        }
    }
}
```

