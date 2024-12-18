#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "../utils/clock.h"

#define SDL_NUM_MOUSE_BUTTONS 5


typedef enum {
    MOUSE_LEFT = 1,
    MOUSE_MIDDLE = 2,
    MOUSE_RIGHT = 3
} MouseButtons;

bool mouseHeld[SDL_NUM_MOUSE_BUTTONS];
bool mousePressed[SDL_NUM_MOUSE_BUTTONS];
bool mouseReleased[SDL_NUM_MOUSE_BUTTONS];

int mouseX = 0;
int mouseY = 0;


bool checkMouseHeld (short scancode);
bool checkMousePressed (short scancode);
bool checkMouseReleased (short scancode);
void initMouseInput ();
void updateMouseInput ();


bool checkMouseHeld (short scancode) {  // Checks if a key is being held. Use in an if statement with the key-to-be-detected as an argument.
    return mouseHeld[scancode];
}
bool checkMousePressed (short scancode) {  //Checks if a key was quickly pressed. Use in an if statement with the key-to-be-detected as an argument.
    return mousePressed[scancode];
}
bool checkMouseReleased (short scancode) {  //Checks if a key was released. Use in an if statement with the key-to-be-detected as an argument.
    return mouseReleased[scancode];
}

//Called at runtime to setup the keyboard input.
void initMouseInput () {
    for (short i = 0; i < SDL_NUM_MOUSE_BUTTONS; i++) {
        mouseHeld[i] = 0;
        mousePressed[i] = 0;
        mouseReleased[i] = 0;
    }
    addFrameFunction(updateMouseInput);
    printf("Mouse Input Initialized!\n");
}

// Called every frame to update detected keys.
void updateMouseInput () {
    const Uint32 state = SDL_GetMouseState(&mouseX, &mouseY);
    for (short i = 0; i < SDL_NUM_MOUSE_BUTTONS; i++) {
        if (state & SDL_BUTTON(i)) {
            if (!mouseHeld[i]) {
                mousePressed[i] = 1;
            }
            else {
                mousePressed[i] = 0;
            }
            mouseHeld[i] = 1;
        }
        else {
            if (mouseHeld[i]) {
                mouseReleased[i] = 1;
            }
            else {
                mouseReleased[i] = 0;
            }
            mouseHeld[i] = 0;
        }
    }
}

#endif