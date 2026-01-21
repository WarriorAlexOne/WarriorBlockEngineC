#include "WBE/Util/WBE_Vec2D.h"

WBE_Vec2f WBE_Vec2fAdd (WBE_Vec2f a, WBE_Vec2f b) {
    WBE_Vec2f newVec2f;
    newVec2f.x = a.x + b.x;
    newVec2f.y = a.y + b.y;
    return newVec2f;
}

WBE_Vec2f WBE_Vec2fSubtract (WBE_Vec2f a, WBE_Vec2f b) {
    WBE_Vec2f newVec2f;
    newVec2f.x = a.x - b.x;
    newVec2f.y = a.y - b.y;
    return newVec2f;
}
