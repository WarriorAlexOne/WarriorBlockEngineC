#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>

#include <SDL2/SDL.h>

#include "../utils/clock.h"
#include "../main/window.h"
#include "../map/levelGen.h"
#include "../entity/player.h"


void initRenderer ();
void updateRenderer ();


void initRenderer () {
    addFrameFunction(updateRenderer);
    printf("Renderer Has Started!\n");
}

void updateRenderer () {
    SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);  //Pretty Navy Blue.
    // SDL_SetRenderDrawColor(renderer, 117, 151, 251, 255);  //Slome Sky Color
    SDL_RenderClear(renderer);

    readAndRenderLevel();
    playerRender();

    SDL_RenderPresent(renderer);
}

#endif