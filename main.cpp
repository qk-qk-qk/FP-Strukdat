#include "raylib.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

int panjang = 800;
int lebar = 600;
const int radius = 5;
int ballCount = 5000;
bool useQuadtree = true;
bool started = false;
char inputText[10] = "";

void circlemovement(int &speedx, int &speedy, int radius, Vector2 &loc){
    loc.x += speedx;
    loc.y += speedy;
    DrawCircle(loc.x, loc.y, radius, RED);
}

void BoundaryCircle(Vector2 &loc, int &speedx, int &speedy, int radius){
    if (loc.x + radius >= panjang || loc.x - radius <= 0){
        speedx = -speedx;
    }
    if (loc.y + radius >= lebar || loc.y - radius <= 0){
        speedy = -speedy;
    }
}

struct AABB {
    float x, y, w, h;

    bool contains(Vector2 p) {
        return (p.x >= x && p.x <= x + w &&
                p.y >= y && p.y <= y + h);
    }

    bool intersects(AABB range) {
        return !(range.x > x + w || 
                 range.x + range.w < x ||
                 range.y > y + h ||
                 range.y + range.h < y);
    }
};

struct Quadtree {
    static const int capacity = 4;
    AABB boundary;
    vector<int> points;   // SIMPAN INDEX bola
    bool divided = false;

    Quadtree *nw, *ne, *sw, *se;

    Quadtree(AABB b) : boundary(b) {}

    void subdivide() {
        float x = boundary.x;
        float y = boundary.y;
        float w = boundary.w / 2;
        float h = boundary.h / 2;

        nw = new Quadtree({x, y, w, h});
        ne = new Quadtree({x+w, y, w, h});
        sw = new Quadtree({x, y+h, w, h});
        se = new Quadtree({x+w, y+h, w, h});

        divided = true;
    }

    void insert(int index, Vector2 pos) {
        if (!boundary.contains(pos)) return;

        if (points.size() < capacity) {
            points.push_back(index);
        } else {
            if (!divided) subdivide();
            nw->insert(index, pos);
            ne->insert(index, pos);
            sw->insert(index, pos);
            se->insert(index, pos);
        }
    }

    void query(AABB range, vector<int> &found) {
        if (!boundary.intersects(range)) return;

        for (int i : points) found.push_back(i);

        if (divided) {
            nw->query(range, found);
            ne->query(range, found);
            sw->query(range, found);
            se->query(range, found);
        }
    }
};


void CircleCollision(Vector2 &loc1, Vector2 &loc2, int &speedx1, int &speedy1,
                     int &speedx2, int &speedy2, int radius) 
{
    float dx = loc2.x - loc1.x;
    float dy = loc2.y - loc1.y;
    float distance = sqrt(dx*dx + dy*dy);
    float mindistance = radius * 2;
    if (distance == 0) return;

    if (distance < mindistance) {

        int tempX = speedx1;
        int tempY = speedy1;

        speedx1 = speedx2;
        speedy1 = speedy2;

        speedx2 = tempX;
        speedy2 = tempY;

        float overlap = mindistance - distance;

        float nx = dx / distance;
        float ny = dy / distance;

        loc1.x -= nx * (overlap / 2);
        loc1.y -= ny * (overlap / 2);

        loc2.x += nx * (overlap / 2);
        loc2.y += ny * (overlap / 2);
    }
}


int main(){
    InitWindow(panjang, lebar, "Collision Detection");
    SetTargetFPS(60);


    vector<Vector2> loc;
    vector<int> speedX;
    vector<int> speedY;

    // for (int i = 0; i < ballCount; i++){
    //     // randomize posisi
    //     Vector2 tempPos = {
    //         (float)GetRandomValue(radius, panjang - radius),
    //         (float)GetRandomValue(radius, lebar - radius)
    //     };
    //     loc.push_back(tempPos);

    //     // randomize speed
    //     speedX.push_back(GetRandomValue(-5, 5));
    //     speedY.push_back(GetRandomValue(-5, 5));

    //     if (speedX[i] == 0) speedX[i] = 2;
    //     if (speedY[i] == 0) speedY[i] = 2;
    // }


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!started) {
    DrawText("Masukkan jumlah bola:", 250 , 200, 20, WHITE);
    DrawRectangleLines(300, 240, 200, 40, WHITE);
    DrawText(inputText, 310, 250, 20, WHITE);
    DrawText("Tekan ENTER untuk mulai", 260, 300, 20, WHITE);

    int key = GetKeyPressed();
    if (key >= KEY_ZERO && key <= KEY_NINE) {
        int len = strlen(inputText);
        if (len < 6) {
            inputText[len] = (char)('0' + key - KEY_ZERO);
            inputText[len + 1] = '\0';
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(inputText);
        if (len > 0) inputText[len - 1] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER)) {
        ballCount = atoi(inputText);
        started = true;

        // INIT DATA BOLA (PINDAH DARI MAIN SEBELUMNYA)
        loc.clear();
        speedX.clear();
        speedY.clear();

        for (int i = 0; i < ballCount; i++) {
            Vector2 tempPos = {
                (float)GetRandomValue(radius, panjang - radius),
                (float)GetRandomValue(radius, lebar - radius)
            };
            loc.push_back(tempPos);

            speedX.push_back(GetRandomValue(-5, 5));
            speedY.push_back(GetRandomValue(-5, 5));

            if (speedX[i] == 0) speedX[i] = 2;
            if (speedY[i] == 0) speedY[i] = 2;
        }
    }

    EndDrawing();
    continue; 
}

        if (IsKeyPressed(KEY_Q)) useQuadtree = true;
        if (IsKeyPressed(KEY_B)) useQuadtree = false;
        DrawText(useQuadtree ? "Mode: Quadtree" : "Mode: Brute Force", 10, 10, 20, WHITE);

        //Brute Force
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

        EndDrawing();
    }

    CloseWindow();
    return 0;
}