#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/clock.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"
#include "../entity/player.h"

void initRenderer ();
void updateRenderer ();


void initRenderer () {
    addFrameFunction(updateRenderer);
}

void updateRenderer () {
    SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);  //Pretty Navy Blue.
    SDL_RenderClear(renderer);

    playerRender();

    SDL_RenderPresent(renderer);
}

#endif