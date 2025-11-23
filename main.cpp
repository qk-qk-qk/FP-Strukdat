#include "raylib.h"
#include <vector>
#include <iostream>

using namespace std;

int panjang = 800;
int lebar = 600;
const int radius = 50;
int ballCount = 10;

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

int main(){
    InitWindow(panjang, lebar, "Collision Detection");
    SetTargetFPS(60);


    vector<Vector2> loc;
    vector<int> speedX;
    vector<int> speedY;

    for (int i = 0; i < ballCount; i++){
        // randomize posisi
        Vector2 tempPos = {
            (float)GetRandomValue(radius, panjang - radius),
            (float)GetRandomValue(radius, lebar - radius)
        };
        loc.push_back(tempPos);

        // randomize speed
        speedX.push_back(GetRandomValue(-5, 5));
        speedY.push_back(GetRandomValue(-5, 5));

        if (speedX[i] == 0) speedX[i] = 2;
        if (speedY[i] == 0) speedY[i] = 2;
    }


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < ballCount; i++){
            circlemovement(speedX[i], speedY[i], radius, loc[i]);
            BoundaryCircle(loc[i], speedX[i], speedY[i], radius);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
