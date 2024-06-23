#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define byte char
#define string char

SDL_Event event;  //Required for various inputs.

#include "../utils/clock.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"
#include "../entity/player.h"
#include "../main/rendering.h"


int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    initClockValues();
    initDebugTools();
    initMainWindow();
    initKeyInput();
    initControllerInput();
    initPlayers();
    initRenderer();
    printf("Initialization Complete!\n\n");


    //Main Loop
    while (!quit) {
        updateClocks();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        
    }
    
    // SDL_DestroyTexture(texture);
    if (controller) {
        SDL_GameControllerClose(controller[0]);
    }
    free(playerList);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if (debug) { printf("DEBUG MODE\nGame Exit Successful\n"); system("pause"); }
    return 0;
}
