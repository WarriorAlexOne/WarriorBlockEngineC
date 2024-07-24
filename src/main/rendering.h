#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../main/window.h"
#include "../map/proceduralChunkGenerator.h"
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

    // renderChunks(currentLevel);
    renderStaticLevel();
    SDL_SetRenderDrawColor(windows[0].renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(windows[0].renderer, &(SDL_Rect){mainCamera.coords.x - 16/2, mainCamera.coords.y - 16/2, 16, 16});
    SDL_SetRenderDrawColor(windows[0].renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(windows[0].renderer, &(SDL_Rect){(windows[0].size.x/2)-8, (windows[0].size.y/2)-8, 16, 16});
    playerRender();
    renderText();

    SDL_RenderPresent(windows[0].renderer);
}

void screenSaver () {  //Add fun screen saver that activates after 10 minutes of no player inputs.

}

#endif