#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#define FNL_IMPL

#define byte char
#define ubyte unsigned char


//Game Variables
byte gamePaused = 0;
double gameScale = 1.0;  //Other values are multiplied by this.
const double DEFAULT_TILE_SIZE = 16.0;
int currentLevel = 0;
int worldSeed;
double perlinSeed;
int fps = 0;
int tps = 0;

#endif