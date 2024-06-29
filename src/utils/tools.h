#ifndef TOOLS_H
#define TOOLS_H

#include <SDL2/SDL.h>


SDL_Rect makeRect (int x, int y, int w, int h);


SDL_Rect makeRect (int x, int y, int w, int h) {
    SDL_Rect temp = {x, y, w, h};
    return temp;
}

#endif