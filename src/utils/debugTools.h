#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/clock.h"

void initDebugTools ();
void updateDebugTools ();


bool debug = false;    //Toggles debug mode, which pauses the program upon exit to more easily review the console logs.
bool tickOnce = true;  //Set to false after running some code in an if statement.

void initDebugTools () {
    addFrameFunction(updateDebugTools);
}

void updateDebugTools () {
    
}

#endif