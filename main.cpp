#include "raylib.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

int panjang = 800;
int lebar = 600;
const int radius = 5;
int ballCount = 1000;

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

void CircleCollision(Vector2 &loc1, Vector2 &loc2, int &speedx1, int &speedy1,
                     int &speedx2, int &speedy2, int radius) 
{
    float dx = loc2.x - loc1.x;
    float dy = loc2.y - loc1.y;
    float distance = sqrt(dx*dx + dy*dy);
    float mindistance = radius * 2;

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

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
