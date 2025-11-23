#include "raylib.h"
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;
int panjang = 800;
int lebar = 600;
int centerX = 400;
int centerY = 300;
int speedX = 4;
int speedY = 5;
void circlemovement(int &speedx, int &speedy, int radius, int &centerX, int &centerY){
        centerX += speedx;
        centerY += speedy;
    DrawCircle (centerX, centerY, radius, RED);
}

void BoundaryCircle(int &centerX, int &centerY, int &speedx, int &speedy, int radius){
    if (centerX + radius >= panjang || centerX - radius <= 0){
        speedx = -speedx;
    }
    if (centerY + radius >= lebar || centerY - radius <= 0){
        speedy = -speedy;
    }
}


int main (){
    InitWindow(panjang, lebar, "Collision Detection");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        circlemovement(speedX, speedY, 50, centerX, centerY);
        BoundaryCircle(centerX, centerY, speedX, speedY, 50);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}