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


#define LEVEL_W 512
#define LEVEL_H 256


int levelWidth = LEVEL_W - 1;
int levelHeight = LEVEL_H - 1;

fnl_state noise;
double noiseData;
double roughness = 8.0;
double noiseGate = -0.1;

double surfaceRoughness = 0.6;

int levelData[LEVEL_W][LEVEL_H];
bool levelCreated = false;

//Level Info
int groundLevel = 127;


void initLevelGen ();
void initSeeds (int seed);
void createLevel ();
void readAndRenderLevel ();
void setLevelDirt ();
void setLevelGrass ();


void fillLevel (int tileID);
void addLevelHills ();
void addLevelCaves ();


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
    int noise_Height = 7;
    double perlin_scale = 10;
    for (int x = 0; x <= levelWidth; x++) {
        double noise_gate_multiplier = (fnlGetNoise2D(&noise, x/60.0, worldSeed)+1)/2;
        for (int y = 0; y <= levelHeight; y++) {
            double perlin_height = (fnlGetNoise3D(&noise, x * perlin_scale, y  * perlin_scale, perlinSeed)+1)/2;
            double local_noise_gate = y/(groundLevel*2.0) * noise_Height - noise_Height/2.0 + noise_gate_multiplier/2.0;
            if (perlin_height > local_noise_gate) {
                levelData[x][levelHeight - y] = STONE;
            }
        }
    }
    setLevelDirt();
    setLevelGrass();
    // fillLevel(GRASS);
    // addLevelHills();
    // addLevelCaves();
    levelCreated = true;
}

void readAndRenderLevel () {
    int zoom = 0;
    for (
        int x = zoom + (cameraX >= zoom ? (((int)cameraX/DEFAULT_TILE_SIZE)/gameScale) : zoom);
        x <= (((windowW/DEFAULT_TILE_SIZE) + ((int)cameraX/DEFAULT_TILE_SIZE)) + 512 < levelWidth ?  //If edge of screen + camera offset is less than the level width in tiles
                ((windowW/DEFAULT_TILE_SIZE) + ((int)cameraX/DEFAULT_TILE_SIZE)) + 512 :  //If true, tile render limit is set to window edge + camera offset.
                    levelWidth);  //If false (meaning window edge + camera offset is larger than the level), tile render is set to max level size.
        x++
        ) {
        for (
            int y = zoom + (cameraY >= zoom ? (((int)cameraY/DEFAULT_TILE_SIZE)/gameScale) : zoom);
            y <= (((windowH/DEFAULT_TILE_SIZE) + ((int)cameraY/DEFAULT_TILE_SIZE)) + 256 < levelHeight ?  //If edge of screen + camera offset is less than the level width in tiles
                ((windowH/DEFAULT_TILE_SIZE) + ((int)cameraY/DEFAULT_TILE_SIZE)) + 256 :  //If true, tile render limit is set to window edge + camera offset.
                    levelHeight);  //If false (meaning window edge + camera offset is larger than the level), tile render is set to max level size.
            y++
            ) {
            for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
                if (levelData[x][y] == tileID) {
                    tiles[tileID].tileDimensions.x = ((x * DEFAULT_TILE_SIZE) * gameScale) - (int)cameraX;
                    tiles[tileID].tileDimensions.y = ((y * DEFAULT_TILE_SIZE) * gameScale) - (int)cameraY;
                    tiles[tileID].tileDimensions.w = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    tiles[tileID].tileDimensions.h = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    SDL_RenderCopy(renderer, tiles[tileID].texture, NULL, &tiles[tileID].tileDimensions);
                    break;
                }
            }
        }
    }
}

void setLevelDirt () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            if (levelData[x][y] == STONE && levelData[x][y-1] == AIR) {
                levelData[x][y] = DIRT;
                levelData[x][y+1] = DIRT;
                levelData[x][y+2] = DIRT;
            }
        }
    }
}

void setLevelGrass () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            if (levelData[x][y] == DIRT && levelData[x][y-1] == AIR) {
                levelData[x][y] = GRASS;
            }
        }
    }
}



void fillLevel (int tileID) {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            levelData[x][y] = tileID;
        }
    }
}

void addLevelHills () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            if (y <= 127) {
                noiseData = fnlGetNoise3D(&noise, x * surfaceRoughness, y * surfaceRoughness, (int)perlinSeed);
                if (noiseData < noiseGate) {
                    levelData[x][y] = AIR;
                }
            }
        }
    }
}

void addLevelCaves () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            if (levelData[x][y] == GRASS) {
                noiseData = fnlGetNoise3D(&noise, x * roughness, y * roughness, (int)perlinSeed);
                if (noiseData < noiseGate) {
                    levelData[x][y] = AIR;
                }
            }
        }
    }
}

#endif