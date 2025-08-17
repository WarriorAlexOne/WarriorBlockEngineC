#ifndef WAO_CAMERA_H
#define WAO_CAMERA_H

#include "Utils/WBE_Vec2.h"

typedef struct {
    WBE_Vec2_D pos;
    WBE_Vec2_D prevPos;
    WBE_Vec2_D worldGridPos;
    WBE_Vec2_D cameraSize;   // Can't be changed. It is used to get the current width/height of the camera to allow the user to limit the camera's movement with a function.
    double zoom;
    double prevZoom;
    double zoomSpeed;
    double zoomMin;
    double zoomMax;
} WBE_Camera;

// WBE_Camera* WBE_CreateCamera ();
// void WBE_InitCamera (WBE_Camera* camera);
// void zoomTempFunc (Wao_Camera* camera, struct Wao_World* world);   // Put in world module

#endif