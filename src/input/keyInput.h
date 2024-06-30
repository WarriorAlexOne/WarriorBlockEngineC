#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "../utils/clock.h"


bool keyHeld[SDL_NUM_SCANCODES];
bool keyPressed[SDL_NUM_SCANCODES];
bool keyReleased[SDL_NUM_SCANCODES];


bool checkKeyHeld (short scancode);
bool checkKeyPressed (short scancode);
bool checkKeyReleased (short scancode);
void initKeyInput ();
void updateKeyInput ();


bool checkKeyHeld (short scancode) {  // Checks if a key is being held. Use in an if statement with the key-to-be-detected as an argument.
    return keyHeld[scancode];
}
bool checkKeyPressed (short scancode) {  //Checks if a key was quickly pressed. Use in an if statement with the key-to-be-detected as an argument.
    return keyPressed[scancode];
}
bool checkKeyReleased (short scancode) {  //Checks if a key was released. Use in an if statement with the key-to-be-detected as an argument.
    return keyReleased[scancode];
}

//Called at runtime to setup the keyboard input.
void initKeyInput () {
    for (short i = 0; i < SDL_NUM_SCANCODES; i++) {
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
    for (short i = 0; i < SDL_NUM_SCANCODES; i++) {
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