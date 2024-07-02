#ifndef MINING_H
#define MINING_H

#include "../input/mouseInput.h"
#include "../entity/camera.h"
#include "../map/levelGen.h"


void initBlockManipulation ();
void destroyBlock ();


void initBlockManipulation () {
    addFrameFunction(destroyBlock);
}

void destroyBlock () {
    if (checkMousePressed(MOUSE_LEFT)) {
        levelData
        [((mouseX - (int)cameraX) / (int)((int)DEFAULT_TILE_SIZE * gameScale))]
        [((mouseY - (int)cameraY) / (int)((int)DEFAULT_TILE_SIZE * gameScale))] = AIR;

        printf("X: %i\n", ((mouseX - (int)cameraX) / (int)((int)DEFAULT_TILE_SIZE * gameScale)));
        printf("---Y: %i\n", ((mouseY - (int)cameraY) / (int)((int)DEFAULT_TILE_SIZE * gameScale)));
    }
}

#endif