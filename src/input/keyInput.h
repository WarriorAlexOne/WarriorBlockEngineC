#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/clock.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"

int checkHeldKey (int scancode);
int checkPressedKey (int scancode);
int checkReleasedKey (int scancode);
void initKeyInput ();
void updateKeyInput ();


int keyHeld[SDL_NUM_SCANCODES];
int keyPressed[SDL_NUM_SCANCODES];
int keyReleased[SDL_NUM_SCANCODES];



int checkHeldKey (int scancode) { return keyHeld[scancode]; }  // Checks if a key is being held. Use in an if statement with the key-to-be-detected as an argument.
int checkPressedKey (int scancode) { return keyPressed[scancode]; }  //Checks if a key was quickly pressed. Use in an if statement with the key-to-be-detected as an argument.
int checkReleasedKey (int scancode) { return keyReleased[scancode]; }  //Checks if a key was released. Use in an if statement with the key-to-be-detected as an argument.


//Called at runtime to setup the keyboard input.
void initKeyInput () {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        keyHeld[i] = 0;
        keyPressed[i] = 0;
        keyReleased[i] = 0;
    }
    addFrameFunction(updateKeyInput);
    printf("Key Input Initialized!\n");
}

//Called every frame to update detected keys.
void updateKeyInput () {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        if (state[i]) {
            if (!keyHeld[i]) {
                keyPressed[i] = 1;
            }
            else {
                keyPressed[i] = 0;
            }
            keyHeld[i] = 1;
        }
        else {
            if (keyHeld[i]) {
                keyReleased[i] = 1;
            }
            else {
                keyReleased[i] = 0;
            }
            keyHeld[i] = 0;
        }
    }
}

#endif