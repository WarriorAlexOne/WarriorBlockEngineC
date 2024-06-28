#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

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
#include "../utils/FastNoiseLite/FastNoiseLite.h"


const string IMG_FORMAT[8] = ".png";
const string TILE_FILE_PATH[24] = "assets/textures/tiles/";

typedef struct {
    SDL_Texture* texture;
    SDL_Rect tileDimensions;
    short ID;
    char tileName[64];
} Tile;

typedef enum {
    AIR,
    GRASS,
    DIRT,
    STONE,
    OAK_LOG,
    OAK_LEAVES
} TileNames;

Tile tiles[8];

short numberOfTiles = 0;
bool tilesInitialized = false;


void initTiles ();
Tile createTile (short ID, string tileName[]);
SDL_Texture* createTileTexture (SDL_Texture* texture, string texturePath[]);


void initTiles () {
    tiles[1] = createTile(GRASS, "grass");
    tiles[2] = createTile(DIRT, "dirt");
    tiles[3] = createTile(STONE, "stone");
    tiles[4] = createTile(OAK_LOG, "oak_log");
    tiles[5] = createTile(OAK_LEAVES, "oak_leaves");
    tilesInitialized = true;
    printf("Tiles Initialized!\n");
}

Tile createTile (short ID, string tileName[]) {
    string texturePath[128];
    Tile newTile;
    newTile.ID = ID;
    newTile.tileDimensions = makeRect(0, 0, DEFAULT_TILE_SIZE * gameScale, DEFAULT_TILE_SIZE * gameScale);

    sprintf(texturePath, "%s%s%s", TILE_FILE_PATH, tileName, IMG_FORMAT);
    newTile.texture = createTileTexture(newTile.texture, texturePath);

    numberOfTiles++;

    return newTile;
}

SDL_Texture* createTileTexture (SDL_Texture* texture, string texturePath[]) {
    texture = IMG_LoadTexture(renderer, texturePath);
    return texture;
}

void destroyTileTextures (Tile tiles[], int tileAmount) {
    for (int i = 0; i < tileAmount; i++) {
        SDL_DestroyTexture(tiles[i].texture);
    }
}

#endif