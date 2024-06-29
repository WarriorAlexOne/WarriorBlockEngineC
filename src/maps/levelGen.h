#ifndef LEVELGEN_H
#define LEVELGEN_H

#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/FastNoiseLite/FastNoiseLite.h"
#include "../main/window.h"
#include "../maps/tiles.h"


#define LEVEL_W 10240
#define LEVEL_H 10240


long long int levelWidth = LEVEL_W;
long long int levelHeight = LEVEL_H;

fnl_state noise;
double noiseData;
double roughness = 8.0;
double noiseGate = -0.1;

long long int levelData[LEVEL_W][LEVEL_H];
bool levelCreated = false;


long long int testNum = 0;


void initLevelGen ();
void initSeeds (int seed);
void createLevel ();
void readAndRenderLevel ();


void initLevelGen () {
    noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
    // worldSeed = 1092834;
    initSeeds(1294853);
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
    for (long long int x = 0; x < levelWidth; x++) {
        for (long long int y = 0; y < levelHeight; y++) {
            noiseData = fnlGetNoise3D(&noise, x * roughness, y * roughness, (int)perlinSeed);
            if (y >= 0 && y < levelHeight) levelData[x][y] = DIRT;
            // if (y >= 0 && y <= 8) levelData[x][y] = AIR;
            // if (y >= 15) levelData[x][y] = STONE;
            if (noiseData < noiseGate) {
                
                // levelData[x][y+3] = GRASS;
                levelData[x][y] = AIR;
                // testNum++;
                // printf("%i. %f\n", x, noiseData);
            }
        }
    }
    // levelCreated = true;
}

void readAndRenderLevel () {
    for (int x = (((int)(players[0].x)/DEFAULT_TILE_SIZE)/gameScale); /*gameScale is temp. Will need changing when camera added*/ x < (((int)(players[0].x)/DEFAULT_TILE_SIZE)/gameScale) + 50; x++) {
        for (int y = (((int)(players[0].y)/DEFAULT_TILE_SIZE)/gameScale); y < (((int)(players[0].y)/DEFAULT_TILE_SIZE)/gameScale) + 50; y++) {
            for (long long int tileID = 0; tileID < numberOfTiles; tileID++) {
                if (levelData[x][y] == tileID) {
                    tiles[tileID].tileDimensions.x = ((x * DEFAULT_TILE_SIZE) * gameScale) - cameraX;
                    tiles[tileID].tileDimensions.y = ((y * DEFAULT_TILE_SIZE) * gameScale) - cameraY;
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