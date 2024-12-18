#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "../../include/util/common.h"

#include <SDL2/SDL.h>

#define FNL_IMPL

#define byte char
#define ubyte unsigned char

#define PI 3.14159265358979323846


typedef struct {
    int x;
    int y;
    int w;
    int h;
} Rect;

typedef struct {
    double x;
    double y;
    double w;
    double h;
} RectF;

// Window Variables
SDL_DisplayMode displayMode;

// Game Variables
bool gamePaused = false;
double gameScale = 3.0;   // Other values are multiplied by this.
double worldRotation = 0.0;
double DEFAULT_TILE_SIZE = 16.0;
int currentLevel = 0;
int worldSeed;
double perlinSeed;

bool quit = false;

#endif