#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../main/window.h"


const char IMG_FORMAT[8] = ".png";
const char TILE_FILE_PATH[24] = "assets/textures/tiles/";

typedef struct {
    SDL_Texture* texture;
    Vec2 coords;
    Vec2 size;
    short ID;
    char name[64];
} Tile;

typedef enum {
    AIR,
    GRASS,
    DIRT,
    STONE,
    OAK_LOG,
    OAK_LEAVES
} TileNames;

Tile tiles[16];

short numberOfTiles = 0;


void initTiles ();
Tile createTile (short ID, char tileName[]);
SDL_Texture* createTileTexture (SDL_Texture* texture, char texturePath[]);
void setFoliageColor (Tile tile);


void initTiles () {
    tiles[1] = createTile(GRASS, "Ground Overworld Top");
    tiles[2] = createTile(DIRT, "Ground Overworld Middle");
    tiles[3] = createTile(STONE, "Ground Overworld TR Corner");
    tiles[4] = createTile(OAK_LOG, "Ground Overworld Right");
    tiles[5] = createTile(OAK_LEAVES, "Ground Overworld TR In Corner");
    tiles[6] = createTile(6, "Ground Overworld TL Corner");
    tiles[7] = createTile(7, "Ground Overworld Left");
    tiles[8] = createTile(8, "Ground Overworld TL In Corner");
    tiles[9] = createTile(9, "Question Block");
    printf("Tiles Initialized!\n");
}

Tile createTile (short ID, char tileName[]) {
    char texturePath[128];
    Tile newTile;
    newTile.ID = ID;
    newTile.coords.x = 0;
    newTile.coords.y = 0;
    newTile.size.x = DEFAULT_TILE_SIZE * gameScale;
    newTile.size.y = DEFAULT_TILE_SIZE * gameScale;
    sprintf(newTile.name, "%s", tileName);

    sprintf(texturePath, "%s%s%s", TILE_FILE_PATH, tileName, IMG_FORMAT);
    newTile.texture = createTileTexture(newTile.texture, texturePath);
    // setFoliageColor(newTile);

    numberOfTiles++;

    return newTile;
}

SDL_Texture* createTileTexture (SDL_Texture* texture, char texturePath[]) {
    texture = IMG_LoadTexture(windows[0].renderer, texturePath);
    return texture;
}

void setFoliageColor (Tile tile) {
    if (
        tile.ID == GRASS ||
        tile.ID == OAK_LEAVES
        ) {
        SDL_SetTextureColorMod(tile.texture, 0, 191, 0);  //Green
    }
}

void destroyTileTextures (Tile tiles[], int tileAmount) {
    for (int i = 0; i < tileAmount; i++) {
        SDL_DestroyTexture(tiles[i].texture);
    }
}

#endif