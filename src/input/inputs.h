#ifndef INPUTS_H
#define INPUTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"


SDL_Event event;  //Handles various inputs.

//Main Window Exit
byte quit = 0;


void initInputs ();
void updateInputs ();


void initInputs () {
    addFrameFunction(updateInputs);
    printf("Input Updater Initialized!");
}

void updateInputs () {
    SDL_PollEvent(&event);  //Start checking for events such as inputs.
    if (event.type == SDL_QUIT) quit = 1;
}

#endif