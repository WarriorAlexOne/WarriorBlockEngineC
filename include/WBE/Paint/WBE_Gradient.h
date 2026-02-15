#ifndef WBE_GRADIENT_H
#define WBE_GRADIENT_H

#include <SDL3/SDL.h>
#include "WBE/WBE_Defines.h"

SDL_Texture* WBE_CreateGradient (SDL_Renderer* renderer, unsigned int padding, ubyte alpha, ubyte r1, ubyte g1, ubyte b1, ubyte r2, ubyte g2, ubyte b2);

#endif