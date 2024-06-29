#ifndef TOUCHINPUT_H
#define TOUCHINPUT_H

#include <stdio.h>

#include <SDL2/SDL.h>

#include "../utils/clock.h"



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