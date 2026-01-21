// Dependent on World.h
// Dependent on Camera.h

#ifndef WBE_PLAYER_H
#define WBE_PLAYER_H

#include "WBE/Util/WBE_Vec2D.h"
#include "WBE/WBE_Defines.h"

typedef struct {
    WBE_Vec2d pos;
    WBE_Vec2d size;
    WBE_Vec2d velocity;

    bool collidedUp;
    bool collidedLeft;
    bool collidedDown;
    bool collidedRight;

    bool onGround;
} WBE_Player2D;

#endif