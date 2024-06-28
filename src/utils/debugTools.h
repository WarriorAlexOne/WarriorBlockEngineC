#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

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


bool debug = false;    //Toggles debug mode, which pauses the program upon exit to more easily review the console logs.
bool tickOnce = true;  //Set to false after running some code in an if statement.


void initDebugTools ();
void updateDebugTools ();


void initDebugTools () {
    if (debug) {
        addFrameFunction(updateDebugTools);
        printf("Debugging Tools Initialized!\n");
    }
}

void updateDebugTools () {
    
}

#endif