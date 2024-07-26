#ifndef MINING_H
#define MINING_H

#include <stdio.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../entity/camera.h"
#include "../map/tiles.h"
#include "../map/proceduralChunkGenerator.h"
#include "../entity/player.h"


void initBlockManipulation ();
void destroyBlock ();
void placeBlock ();


void initBlockManipulation () {
    addFrameFunction(destroyBlock);
    addFrameFunction(placeBlock);
}

void destroyBlock () {
    double adjustedMouseX = (mainCamera.tileCoords.x/gameScale) + (((mouseX+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    double adjustedMouseY = (mainCamera.tileCoords.y/gameScale) + (((mouseY+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    if (players[0].pressed.mining && adjustedMouseX >= 0 && adjustedMouseX < staticLevelData.size.x && adjustedMouseY >= 0 && adjustedMouseY < staticLevelData.size.y) {
        staticLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] = 0;
    }
}

void placeBlock () {
    double adjustedMouseX = (mainCamera.tileCoords.x/gameScale) + (((mouseX+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    double adjustedMouseY = (mainCamera.tileCoords.y/gameScale) + (((mouseY+(8*gameScale)+((fmod(gameScale, 1) == 0 ? 0 : 0.375)*gameScale))/gameScale)/DEFAULT_TILE_SIZE);
    if (players[0].pressed.placing && adjustedMouseX >= 0 && adjustedMouseX < staticLevelData.size.x && adjustedMouseY >= 0 && adjustedMouseY < staticLevelData.size.y) {
        staticLevelData.data[(int)adjustedMouseX][(int)adjustedMouseY] = 1;
    }
    if (newBlankLevel) {
        generateBlankLevel();
    }
}

#endif