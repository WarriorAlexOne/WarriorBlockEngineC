#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#define FNL_IMPL

#define byte char
#define ubyte unsigned char

#define PI 3.14159265358979323846


//Game Variables
byte gamePaused = 0;
double gameScale = 1.0;  //Other values are multiplied by this.
double worldRotation = 0.0;
const double DEFAULT_TILE_SIZE = 16.0;
int currentLevel = 0;
int worldSeed;
double perlinSeed;
int fps = 0;
int tps = 0;

#endif