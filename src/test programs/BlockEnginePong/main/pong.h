#ifndef PONG_H
#define PONG_H

#include "paddle.h"


void pong();
void drawBackground ();


void pong () {
    initClocks();
    updateClocks();
    initDebugTools();
    initWindows();

    createWindow(0, "BlockEngine Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800);
    toggleWindow(0, true);

    initRenderers();
    
    addRenderFunction(0, drawBackground);

    initInputs();
    initKeyInput();
    // addRenderFunction(1, testRenderFunc2);
    // addRenderFunction(2, testRenderFunc3);

    initPaddles();

    //Main Loop
    while (!quit) {
        updateClocks();
        // printf("%i", window_list_initialized);
    }
}

void drawBackground () {
    SDL_SetRenderDrawColor(windowList[0].renderer, 25, 51, 153, 255);
    SDL_RenderClear(windowList[0].renderer);
}

#endif