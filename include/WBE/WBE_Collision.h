#ifndef WBE_COLLISION_H
#define WBE_COLLISION_H

#include "WBE/WBE_Defines.h"

bool WBE_IsRectCollided (
    double x1, double y1, double w1, double h1,
    double x2, double y2, double w2, double h2
) {
    return
    x1 <= x2 + w2 &&
    x1 + w1 >= x2 &&
    y1 <= y2 + h2 &&
    y1 + h1 >= y2;
}

#endif