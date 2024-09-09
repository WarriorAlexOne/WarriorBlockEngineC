#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#define min min  //VS Code was angry with this name, so this is defined.
#define max max  //VS Code was angry with this name, so this is defined.


SDL_Rect makeRect (int x, int y, int w, int h);
double min (double num1, double num2);
double max (double num1, double num2);
bool checkCollision (double x1, double y1, double sizeX1, double sizeY1, double x2, double y2, double sizeX2, double sizeY2);


SDL_Rect makeRect (int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    return rect;
}

double min (double num1, double num2) {
    return num1 < num2 ? num1 : num2;
}

double max (double num1, double num2) {
    return num1 > num2 ? num1 : num2;
}

bool checkCollision (double x1, double y1, double sizeX1, double sizeY1, double x2, double y2, double sizeX2, double sizeY2) {
    return x1 + sizeX1 >= x2 && x1 <= x2 + sizeX2 && y1 + sizeY1 >= y2 && y1 <= y2 + sizeY2;
}

#endif