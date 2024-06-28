#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../utils/FastNoiseLite/FastNoiseLite.h"
#include "../maps/tiles.h"
#include "../maps/levelGen.h"
#include "../entity/player.h"


void initRenderer ();
void updateRenderer ();


void initRenderer () {
    addFrameFunction(updateRenderer);
    printf("Renderer Has Started!\n");
}

void updateRenderer () {
    SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);  //Pretty Navy Blue.
    SDL_RenderClear(renderer);

    readAndRenderLevel();
    playerRender();

    SDL_RenderPresent(renderer);
}

#endif