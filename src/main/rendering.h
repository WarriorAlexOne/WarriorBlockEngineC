#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../main/window.h"
#include "../map/tiles.h"
#include "../entity/items.h"
#include "../map/proceduralChunkGenerator.h"
#include "../entity/player.h"
#include "../gui/text.h"


void initRenderUpdater ();
void updateRenderer ();
void screenSaver ();


void initRenderUpdater () {
    addFrameFunction(updateRenderer);

    for (int x = 0; x < windows[0].size.x/(DEFAULT_TILE_SIZE/gameScale); x++) {
        for (int y = 0; y < windows[0].size.y/(DEFAULT_TILE_SIZE/gameScale); y++) {
            SDL_RenderCopy(windows[0].renderer, tiles[DIRT].texture, NULL, &(SDL_Rect){x*(16*gameScale), y*(16*gameScale), DEFAULT_TILE_SIZE*gameScale, DEFAULT_TILE_SIZE*gameScale});
        }
    }
    
    SDL_RenderPresent(windows[0].renderer);
    printf("Renderer Has Started!\n");
}

void updateRenderer () {
    // SDL_SetRenderDrawColor(windows[0].renderer, 25, 51, 153, 255);  //Pretty Navy Blue.
    SDL_SetRenderDrawColor(windows[0].renderer, 117, 151, 251, 255);  //Slome Sky Color
    SDL_RenderClear(windows[0].renderer);

    // renderChunks(currentLevel);
    renderStaticBGLevel();
    renderStaticLevel();
    // SDL_SetRenderDrawColor(windows[0].renderer, 255, 255, 0, 255);
    // SDL_RenderFillRect(windows[0].renderer, &(SDL_Rect){mainCamera.coords.x - 16/2, mainCamera.coords.y - 16/2, 16, 16});
    // SDL_SetRenderDrawColor(windows[0].renderer, 0, 255, 0, 255);
    // SDL_RenderFillRect(windows[0].renderer, &(SDL_Rect){(windows[0].size.x/2)-8, (windows[0].size.y/2)-8, 16, 16});
    // SDL_RenderFillRect(windows[0].renderer, &(SDL_Rect){500, 500, 200, 200});
    SDL_RenderCopy(windows[0].renderer, selectedTile != 0 ? tiles[selectedTile].texture : items[IRON_PICKAXE].texture, NULL, &(SDL_Rect){windows[0].size.x-4-72, 12, 64, 64});
    playerRender();
    loopTexts();
    SDL_RenderPresent(windows[0].renderer);
}

void screenSaver () {  //Add fun screen saver that activates after 10 minutes of no player inputs.

}

#endif