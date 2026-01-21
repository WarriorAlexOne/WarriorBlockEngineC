#ifndef WBE_MOUSE_H
#define WBE_MOUSE_H

#include "WBE/WBE_Defines.h"
#include "WBE/Util/WBE_Vec2D.h"
#include <SDL3/SDL.h>


typedef enum {
    WBE_MOUSE_LEFT,
    WBE_MOUSE_MIDDLE,
    WBE_MOUSE_RIGHT,
    WBE_MOUSE_FORWARD,
    WBE_MOUSE_BACKWARD
} WBE_MouseButtons;

typedef struct {
    int ID;
    int mouseState;

    bool click[5];
    WBE_Vec2f pos;
    WBE_Vec2f lastPos;
    WBE_Vec2f vel;
} WBE_Mouse;


void WBE_InitMouse ();
void WBE_UpdateMouse ();

bool WBE_IsMouseDown (WBE_MouseButtons mouseButton);

WBE_Vec2f WBE_GetMousePos ();
WBE_Vec2f WBE_GetMouseVelocity ();

#endif