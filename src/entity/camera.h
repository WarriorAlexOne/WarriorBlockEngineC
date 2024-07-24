#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>

#include "../utils/vector2D.h"


typedef struct {
    Vec2 coords;
    bool isStill;
} Camera;

Camera mainCamera = {0, 0};


void initCamera ();
void updateCamera ();
void centerOnPlayers ();


void initCamera () {
    mainCamera.coords.x = 0;
    mainCamera.coords.y = 0;
    mainCamera.isStill = false;
}

void updateCamera () {

}

void centerOnPlayers () {
    
}


#endif