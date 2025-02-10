#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "../../include/util/common.h"

#include <SDL3/SDL.h>

#define FNL_IMPL

#define byte char
#define ubyte unsigned char

#define PI 3.14159265358979323846


typedef struct {
    int x;
    int y;
    int w;
    int h;
} Rect;

typedef struct {
    double x;
    double y;
    double w;
    double h;
} RectD;

#endif