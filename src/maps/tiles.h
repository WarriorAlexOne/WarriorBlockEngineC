#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../entity/player.h"


typedef struct {
    SDL_Texture* texture;
    short ID;
    char tileName[];
} Tile;

typedef enum {
    GRASS,
    DIRT,
    STONE,
    OAK_LOG,
    OAK_PLANK
} TileNames;

Tile grass;
Tile dirt;
Tile stone;
Tile oak_log;
Tile oak_plank;


void initTiles ();
Tile createTile (short ID, string tileName[100]);
SDL_Texture* createTileTexture (SDL_Texture* texture, string tileName[]);


void initTiles () {
    grass = createTile(GRASS, "grass");
    dirt = createTile(DIRT, "dirt");
    stone = createTile(STONE, "stone");
    oak_log = createTile(OAK_LOG, "oak_log");
    oak_plank = createTile(OAK_PLANK, "oak_plank");
}

Tile createTile (short ID, string tileName[100]) {
    Tile temp;
    temp.ID = ID;
    tileName;
}

SDL_Texture* createTileTexture (SDL_Texture* texture, string tileName[]) {

}



#endif