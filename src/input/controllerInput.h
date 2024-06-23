#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

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
#include "../input/keyInput.h"

void initControllerInput ();
void updateControllerInput ();


SDL_GameController* controller[10];
SDL_Joystick* controllerInfo[2];

short leftTrigger;
short rightTrigger;


void initControllerInput () {
    if (SDL_NumJoysticks()) {
        printf("# Of Controllers Connected: %i\n", SDL_NumJoysticks());
        for (short i = 0; i < SDL_NumJoysticks(); i++) {
            if (SDL_IsGameController(i)) {
                controller[i] = SDL_GameControllerOpen(i);
                printf("Controller Connected: %s\n", SDL_GameControllerName(controller[i]));
            }
        }
    }

    addFrameFunction(updateControllerInput);
    printf("Controller Input Initialized!\n");
}


void updateControllerInput () {
    leftTrigger = SDL_GameControllerGetAxis(controller[0], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    rightTrigger = SDL_GameControllerGetAxis(controller[0], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

    //Button Press Detection
    if (controller[0] && event.type == SDL_CONTROLLERBUTTONDOWN) {
        printf("Button Pressed: %d\n", event.cbutton.button);
    }
    //Button Release Detection
    if (controller[1] && event.type == SDL_CONTROLLERBUTTONUP) {
        printf("Button Released: %d\n", event.cbutton.button);
    }
    
    //Left Trigger Press Detection
    if (leftTrigger > 20000) {
        printf("Left Trigger Full Tilt %d\n", leftTrigger);
    }
    else if (leftTrigger > 128) {
        printf("Left Trigger %d\n", leftTrigger);
    }

    //Right Trigger Press Detection
    if (rightTrigger > 20000) {
        printf("Right Trigger Full Tilt: %d\n", rightTrigger);
    }
    else if (rightTrigger > 128) {
        printf("Right Trigger: %d\n", rightTrigger);
    }
}

#endif