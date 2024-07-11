#ifndef CAMERA_H
#define CAMERA_H

#include "../utils/vector2D.h"


typedef struct {
    Vec2 coords;
} Camera;

Camera mainCamera = {0, 1500};

#endif