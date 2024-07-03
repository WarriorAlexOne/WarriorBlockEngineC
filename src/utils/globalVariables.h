#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <stdio.h>

#include <SDL2/SDL.h>

#define FNL_IMPL

#define byte char
#define ubyte unsigned char
#define string char

//Window Title
string title[48] = "WarriorBlockEngine 0.0";
string iconPath[64] = "assets/textures/misc/WarriorBlockEngine Logo v1.png";

byte quit = 0; //Main Window Exit
int windowW = 1300;
int windowH = 800;

//Game Variables
byte gamePaused = 0;
double gameScale = 1.0;  //Other values are multiplied by this.
const double DEFAULT_TILE_SIZE = 16.0;
int currentLevel = 0;
int worldSeed;
double perlinSeed;

#endif