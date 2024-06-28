#ifndef LEVELGEN_H
#define LEVELGEN_H

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
#include "../maps/tiles.h"


#define LEVEL_W 512
#define LEVEL_H 512


int levelWidth = LEVEL_W;
int levelHeight = LEVEL_H;

fnl_state noise;
double* noiseData;
double roughness = 8.0;
double noiseGate = -0.1;

int levelData[LEVEL_W][LEVEL_H];


void initLevelGen ();
void initSeeds (int seed);
void createLevel ();
void readAndRenderLevel ();
// void getNoise ();


void initLevelGen () {
    noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
    // worldSeed = 1092834;
    initSeeds(12948537);
}

void initSeeds (int seed) {
  if (!seed) {
    srand(time(NULL));
    worldSeed = rand();
  }
  else {
    worldSeed = seed;
  }
  srand(worldSeed);
  perlinSeed = rand() % 1000000 + 1000000;
}

void createLevel () {
    for (int x = 0; x < levelWidth; x++) {
        for (int y = 0; y < levelHeight; y++) {
            if (y >= 0 && y <= 512) {
                levelData[x][y] = DIRT;
            }
            if (fnlGetNoise3D(&noise, x * roughness, y * roughness, (int)perlinSeed) < noiseGate) levelData[x][y] = AIR;
        }
    }
}

            // if (y >= 0 && y <= 8) {
            //     levelData[x][y] = AIR;
            // }
            
            // if (y >= 15) {
            //     levelData[x][y] = STONE;
            // }

void readAndRenderLevel () {
    for (int x = 0; x < levelWidth; x++) {
        for (int y = 0; y < levelHeight; y++) {
            for (short tileID = 0; tileID < numberOfTiles; tileID++) {
                if (levelData[x][y] == tileID) {
                    tiles[tileID].tileDimensions.x = (x * DEFAULT_TILE_SIZE) * gameScale;
                    tiles[tileID].tileDimensions.y = (y * DEFAULT_TILE_SIZE) * gameScale;
                    tiles[tileID].tileDimensions.w = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    tiles[tileID].tileDimensions.h = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    SDL_RenderCopy(renderer, tiles[tileID].texture, NULL, &tiles[tileID].tileDimensions);
                    break;
                }
            }
        }
    }
}

// void getNoise () {
//     // Create and configure noise state

//     // Gather noise data
//     noiseData = malloc(256 * 256 * sizeof(double));
//     int index = 0;

//     for (int x = 0; x < 256; x++) {
//         for (int y = 0; y < 256; y++) {
//             noiseData[index] = fnlGetNoise2D(&noise, x, y);
//             printf("%f\n", (noiseData[index]));
//             index++;
//         }
//     }
// }

#endif