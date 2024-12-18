#ifndef DRAWING_TOOLS_H
#define DRAWING_TOOLS_H

#include <SDL2/SDL.h>

#include "../../include/util/global_variables.h"


void setColor (int windowID, ubyte r, ubyte g, ubyte b, ubyte a);
void drawRect (int windowID, double x, double y, double w, double h);
void drawCircle (SDL_Renderer *renderer, int centerX, int centerY, int radius);
void drawFilledCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);

#endif