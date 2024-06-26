#ifndef TOUCHINPUT_H
#define TOUCHINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"


void initTouchInput ();
void updateTouchInput();


void initTouchInput () {
    addFrameFunction(updateTouchInput);
}

void updateTouchInput () {
    if (event.type == SDL_FINGERDOWN) {
        printf("FINGER DETECTED!!!\n");
    }
}

#endif