#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"


SDL_Rect makeRect (int x, int y, int w, int h);


SDL_Rect makeRect (int x, int y, int w, int h) {
    SDL_Rect temp = {x, y, w, h};
    return temp;
}

#endif