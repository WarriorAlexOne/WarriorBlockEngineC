#ifndef LEVELGEN_H
#define LEVELGEN_H

#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/FastNoiseLite/FastNoiseLite.h"
#include "../main/window.h"
#include "../map/tiles.h"


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
void Level_GenerateSurface (int tileID);
void Level_SetDirt ();
void Level_SetGrass ();


void Level_FillAll (int tileID);
void Level_AddHills ();
void Level_AddCaves ();


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
    levelData[0][0] = GRASS;
    Level_GenerateSurface(STONE);
    Level_SetDirt();
    Level_SetGrass();
    levelCreated = true;
}

void readAndRenderLevel () {
    int offset = 0;
    for (
        int x = offset + (cameraX >= offset ? (((int)cameraX/DEFAULT_TILE_SIZE)/gameScale) : offset);
        x <= (((windowW/DEFAULT_TILE_SIZE) + ((int)cameraX/DEFAULT_TILE_SIZE)) + 512 < levelWidth ?  //If edge of screen + camera offset is less than the level width in tiles
                ((windowW/DEFAULT_TILE_SIZE) + ((int)cameraX/DEFAULT_TILE_SIZE)) + 512 :  //If true, tile render limit is set to window edge + camera offset.
                    levelWidth);  //If false (meaning window edge + camera offset is larger than the level), tile render is set to max level size.
        x++
        ) {
        for (
            int y = offset + (cameraY >= offset ? (((int)cameraY/DEFAULT_TILE_SIZE)/gameScale) : offset);
            y <= (((windowH/DEFAULT_TILE_SIZE) + ((int)cameraY/DEFAULT_TILE_SIZE)) + 256 < levelHeight ?  //If edge of screen + camera offset is less than the level width in tiles
                ((windowH/DEFAULT_TILE_SIZE) + ((int)cameraY/DEFAULT_TILE_SIZE)) + 256 :  //If true, tile render limit is set to window edge + camera offset.
                    levelHeight);  //If false (meaning window edge + camera offset is larger than the level), tile render is set to max level size.
            y++
            ) {
            for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
                if (levelData[x][y] == tileID) {
                    tiles[tileID].tileDimensions.x = ((x * DEFAULT_TILE_SIZE) * gameScale) - (cameraX*gameScale);
                    tiles[tileID].tileDimensions.y = ((y * DEFAULT_TILE_SIZE) * gameScale) - (cameraY*gameScale);
                    tiles[tileID].tileDimensions.w = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    tiles[tileID].tileDimensions.h = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    SDL_RenderCopy(renderer, tiles[tileID].texture, NULL, &tiles[tileID].tileDimensions);
                    break;
                }
            }
        }
    }
}

void Level_GenerateSurface (int tileID) {
    int noise_Height = 7;
    double perlin_scale = 10;
    for (int x = 0; x <= levelWidth; x++) {
        double noise_gate_multiplier = (fnlGetNoise2D(&noise, x/60.0, worldSeed)+1)/2;
        for (int y = 0; y <= levelHeight; y++) {
            double perlin_height = (fnlGetNoise3D(&noise, x * perlin_scale, y  * perlin_scale, perlinSeed)+1)/2;
            double local_noise_gate = y/(groundLevel*2.0) * noise_Height - noise_Height/2.0 + noise_gate_multiplier/2.0;
            if (perlin_height > local_noise_gate) {
                levelData[x][levelHeight - y] = tileID;
            }
        }
    }
}

void Level_SetDirt () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= groundLevel+10; y++) {  //10 block downwards buffer
            for (byte i = 1; i <= 3; i++) {  //3 layers of dirt
                if (levelData[x][y] == STONE && levelData[x][y-i] == AIR) {
                    levelData[x][y] = DIRT;
                }
            }
        }
    }
}

void Level_SetGrass () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= groundLevel+10; y++) {  //10 block downwards buffer
            if (levelData[x][y] == DIRT && levelData[x][y-1] == AIR) {
                levelData[x][y] = GRASS;
            }
        }
    }
}



void Level_FillAll (int tileID) {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            levelData[x][y] = tileID;
        }
    }
}

void Level_AddHills () {
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

void Level_AddCaves () {
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