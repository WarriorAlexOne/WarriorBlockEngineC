#ifndef INPUTS_H
#define INPUTS_H

#include <stdio.h>

#include <SDL2/SDL.h>

#include "../utils/clock.h"
#include "../main/window.h"


SDL_Event event;  //Handles various inputs.

void initInputs ();
void updateInputs ();


void initInputs () {
    addFrameFunction(updateInputs);

    printf("Input Updater Initialized!\n");
}

void updateInputs () {
    SDL_PollEvent(&event);  //Start checking for events such as inputs.
    if (event.type == SDL_QUIT) windows[0].quit = 1;
}

#endif