#ifndef CONTROLS_H
#define CONTROLS_H

#include "constants.h"
#include "variables.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Forward Declarations
int checkPressed (int scancode);
int checkJustPressed (int scancode);
int checkJustReleased (int scancode);
void initControls ();
void updateControls ();

int pressed[SDL_NUM_SCANCODES];

int justPressed[SDL_NUM_SCANCODES];

int justReleased[SDL_NUM_SCANCODES];

// Checks if a key is pressed, justPressed, or justReleased.
int checkPressed (int scancode) {
    return pressed[scancode];
}
int checkJustPressed (int scancode) {
    return justPressed[scancode];
}
int checkJustReleased (int scancode) {
    return justReleased[scancode];
}

//This function is called once at the start of the program.
void initControls () {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        pressed[i] = 0;
        justPressed[i] = 0;
        justReleased[i] = 0;
    }
}

//This function is called every frame.
void updateControls () {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        if (state[i]) {
            if (!pressed[i]) {
                justPressed[i] = 1;
            }
            else {
                justPressed[i] = 0;
            }
            pressed[i] = 1;
        }
        else {
            if (pressed[i]) {
                justReleased[i] = 1;
            }
            else {
                justReleased[i] = 0;
            }
            pressed[i] = 0;
        }
    }
} 


#endif