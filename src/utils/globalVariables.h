#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define FNL_IMPL

#define byte char
#define ubyte unsigned char
#define string char


//Window
string title[48] = "WarriorBlockEngine 0.0";
string iconPath[64] = "assets/textures/misc/WarriorBlockEngine Logo v1.png";
int windowW;
int windowH;

//Game Variables
byte gamePaused = 0;
double gameScale = 1.0;  //Other values are multiplied by this.
const double DEFAULT_TILE_SIZE = 16.0;
int worldSeed;
double perlinSeed;

#endif