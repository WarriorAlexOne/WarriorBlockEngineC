#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>

#include "../utils/vector2D.h"


typedef struct {
    Vec2 coords;
    Vec2 tileCoords;
    bool isStill;
} Camera;

Camera mainCamera;


void initCamera ();
void updateCamera ();
void centerOnPlayers ();


void initCamera () {
    mainCamera.coords.x = 90 * gameScale;
    mainCamera.coords.y = 32 * gameScale;
    mainCamera.tileCoords.x = ((mainCamera.coords.x*gameScale)-(windows[0].size.x/2))/DEFAULT_TILE_SIZE;
    mainCamera.tileCoords.y = ((mainCamera.coords.y*gameScale)-(windows[0].size.y/2))/DEFAULT_TILE_SIZE;
    mainCamera.isStill = false;
    addTickFunction(updateCamera);
}

void updateCamera () {
    mainCamera.tileCoords.x = (((mainCamera.coords.x*gameScale)-(windows[0].size.x/2))/DEFAULT_TILE_SIZE)/gameScale;
    mainCamera.tileCoords.y = (((mainCamera.coords.y*gameScale)-(windows[0].size.y/2))/DEFAULT_TILE_SIZE)/gameScale;
}

void centerOnPlayers () {
    
}


#endif