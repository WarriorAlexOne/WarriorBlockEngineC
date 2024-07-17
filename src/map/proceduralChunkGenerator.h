#ifndef PROCEDURALCHUNKGENERATOR_H
#define PROCEDURALCHUNKGENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/FastNoiseLite/FastNoiseLite.h"
#include "../main/window.h"
#include "../entity/camera.h"
#include "../map/tiles.h"


#define LEVEL_W 128
#define LEVEL_H 64
#define LEVEL_AMOUNT 1

int levelWidth = LEVEL_W - 1;
int levelHeight = LEVEL_H - 1;
int levelAmount = LEVEL_AMOUNT;

byte screenWidth = 24;
byte screenHeight = 14;

int screenPosX = 0;
int screenPosY = 0;

byte screenRenderMaxX = 1;  //How many screens will render after the main screen. Render distance, in other words.
byte screenRenderMaxY = 1;

fnl_state noise;
double noiseData;
double roughness = 8.0;
double noiseGate = -0.1;

double surfaceRoughness = 0.6;

int chunkData[LEVEL_AMOUNT][LEVEL_W][LEVEL_H];

//Level Info
int groundLevel = 32;


void initLevelGen ();
void initSeeds (int seed);
void createLevel0 ();
void Level0_GenerateSurface (int tileID);
void Level0_SetDirt ();
void Level0_SetGrass ();


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

void createLevel0 () {
    Level0_GenerateSurface(STONE);
    // Level0_SetDirt();
    // Level0_SetGrass();
}

void Level0_GenerateSurface (int tileID) {
    int noise_Height = 7;
    double perlin_scale = 10;
    for (int x = 0; x <= levelWidth; x++) {
        double noise_gate_multiplier = (fnlGetNoise2D(&noise, x/60.0, worldSeed)+1)/2;
        for (int y = 0; y <= levelHeight; y++) {
            double perlin_height = (fnlGetNoise3D(&noise, x * perlin_scale, y  * perlin_scale, perlinSeed)+1)/2;
            double local_noise_gate = y/(groundLevel*2.0) * noise_Height - noise_Height/2.0 + noise_gate_multiplier/2.0;
            if (perlin_height > local_noise_gate) {
                chunkData[0][x][levelHeight - y] = tileID;
            }
        }
    }
}

void Level0_SetDirt () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= groundLevel+10; y++) {  //10 block downwards buffer
            for (byte i = 1; i <= 3; i++) {  //3 layers of dirt
                if (chunkData[0][x][y] == STONE && chunkData[0][x][y-i] == AIR) {
                    chunkData[0][x][y] = DIRT;
                }
            }
        }
    }
}

void Level0_SetGrass () {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= groundLevel+10; y++) {  //10 block downwards buffer
            if (chunkData[0][x][y] == DIRT && chunkData[0][x][y-1] == AIR) {
                chunkData[0][x][y] = GRASS;
            }
        }
    }
}

#endif