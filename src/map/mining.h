#ifndef MINING_H
#define MINING_H

#include <stdio.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../entity/camera.h"
#include "../map/tiles.h"
#include "../map/levelGenerator.h"


void initBlockManipulation ();
void destroyBlock ();


void initBlockManipulation () {
    addFrameFunction(destroyBlock);
}

void destroyBlock () {
    // if (checkMousePressed(MOUSE_LEFT)) {
    //     levelData[0]
    //     [((mouseX - (int)mainCamera.coords.x) / (int)((int)DEFAULT_TILE_SIZE * gameScale))]
    //     [((mouseY - (int)mainCamera.coords.y) / (int)((int)DEFAULT_TILE_SIZE * gameScale))] = AIR;

    //     printf("X: %i\n", ((mouseX - (int)mainCamera.coords.x) / (int)((int)DEFAULT_TILE_SIZE * gameScale)));
    //     printf("---Y: %i\n", ((mouseY - (int)mainCamera.coords.y) / (int)((int)DEFAULT_TILE_SIZE * gameScale)));
    // }
}

#endif