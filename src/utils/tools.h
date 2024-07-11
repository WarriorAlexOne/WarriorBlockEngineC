#ifndef TOOLS_H
#define TOOLS_H

#include <SDL2/SDL.h>


#define min min  //To Make VS Code happy and not give false errors.
#define max max  //To Make VS Code happy and not give false errors.


SDL_Rect makeRect (int x, int y, int w, int h);
double min (double num1, double num2);
double max (double num1, double num2);


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

#endif