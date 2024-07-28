#ifndef MINING_H
#define MINING_H

#include <stdio.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../entity/camera.h"
#include "../map/tiles.h"
#include "../map/proceduralChunkGenerator.h"
#include "../entity/player.h"


int selectedTile = 1;
double adjustedMouseX;
double adjustedMouseY;


void initBlockManipulation ();
void actionKeyPressed ();
void interactionKeyPressed ();
void selectTile ();


void initBlockManipulation () {
    addFrameFunction(actionKeyPressed);
    addFrameFunction(interactionKeyPressed);
    addFrameFunction(selectTile);
}

void actionKeyPressed () {
    adjustedMouseX = (mainCamera.tileCoords.x/gameScale) + (((mouseX+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    adjustedMouseY = (mainCamera.tileCoords.y/gameScale) + (((mouseY+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    if (
        players[0].pressed.actionKey &&
        players[0].pressed.pickaxe &&
        adjustedMouseX >= 0 &&
        adjustedMouseX < staticLevelData.size.x &&
        adjustedMouseY >= 0 &&
        adjustedMouseY < staticLevelData.size.y
    ) {
        if (staticLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] != 0) {
            staticLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] = 0;
        }
        else {
            staticBGLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] = 0;
        }
    }
    else if (
        players[0].pressed.actionKey &&
        !players[0].pressed.pickaxe &&
        adjustedMouseX >= 0 &&
        adjustedMouseX < staticLevelData.size.x &&
        adjustedMouseY >= 0 &&
        adjustedMouseY < staticLevelData.size.y
    ) {
        if (staticLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] == 0) {
            staticLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] = selectedTile;
        }
    }
}

void interactionKeyPressed () {
    adjustedMouseX = (mainCamera.tileCoords.x/gameScale) + (((mouseX+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    adjustedMouseY = (mainCamera.tileCoords.y/gameScale) + (((mouseY+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    if (
        players[0].pressed.interactionKey &&
        !players[0].pressed.pickaxe &&
        adjustedMouseX >= 0 &&
        adjustedMouseX < staticLevelData.size.x &&
        adjustedMouseY >= 0 &&
        adjustedMouseY < staticLevelData.size.y
    ) {
        if (staticBGLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] == 0) {
            staticBGLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] = selectedTile;
        }
    }
}

void selectTile () {
    if (selectedTile != 0) {
        players[0].pressed.pickaxe = false;
    }
    if (checkKeyPressed(SDL_SCANCODE_1)) {
        selectedTile = 0;
        players[0].pressed.pickaxe = true;
    }
    if (checkKeyPressed(SDL_SCANCODE_2)) selectedTile = GRASS;
    if (checkKeyPressed(SDL_SCANCODE_3)) selectedTile = DIRT;
    if (checkKeyPressed(SDL_SCANCODE_4)) selectedTile = STONE;
    if (checkKeyPressed(SDL_SCANCODE_5)) selectedTile = OAK_LOG;
    if (checkKeyPressed(SDL_SCANCODE_6)) selectedTile = OAK_LEAVES;
    if (checkKeyPressed(SDL_SCANCODE_7)) selectedTile = OAK_PLANKS;
    if (checkKeyPressed(SDL_SCANCODE_8)) selectedTile = COBBLESTONE;
    if (checkKeyPressed(SDL_SCANCODE_9)) selectedTile = GLASS;
    if (checkKeyPressed(SDL_SCANCODE_0)) selectedTile = BEDROCK;
}

#endif