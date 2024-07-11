#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../main/window.h"
#include "../map/levelGenerator.h"
#include "../entity/player.h"


void initRenderUpdater ();
void updateRenderer ();
void screenSaver ();


void initRenderUpdater () {
    addFrameFunction(updateRenderer);

    printf("Renderer Has Started!\n");
}

void updateRenderer () {
    SDL_SetRenderDrawColor(windows[0].renderer, 25, 51, 153, 255);  //Pretty Navy Blue.
    // SDL_SetRenderDrawColor(renderer, 117, 151, 251, 255);  //Slome Sky Color
    SDL_RenderClear(windows[0].renderer);

    readAndRenderLevel(currentLevel);
    playerRender();

    SDL_RenderPresent(windows[0].renderer);
}

void screenSaver () {  //Add fun screen saver that activates after 10 minutes of no player inputs.

}

#endif