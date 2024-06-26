#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

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

#define numOfControllersTEMP 10


typedef struct {
    SDL_GameController* SDL_Controller;
    byte ID;
    short lStickX;
    short lStickY;
    short rStickX;
    short rStickY;
    short lTrigger;
    short rTrigger;
} GameController;

GameController controllers[numOfControllersTEMP];
byte controllerCount = 0;


void initControllerInput ();
void updateControllers ();
void detectControllerInput (GameController controller);


void initControllerInput () {
    if (SDL_NumJoysticks()) {
        printf("# Of Controllers Connected: %i\n", SDL_NumJoysticks());
        for (ubyte i = 0; i < SDL_NumJoysticks(); i++) {
            if (SDL_IsGameController(i)) {
                controllers[i].SDL_Controller = SDL_GameControllerOpen(i);
                controllerCount++;
                controllers[i].ID = controllerCount;
                printf("Controller Connected: %s\n", SDL_GameControllerName(controllers[i].SDL_Controller));
            }
        }
    }

    addFrameFunction(updateControllers);
    printf("Controller Input Initialized!\n");
}

void updateControllers () {
    for (ubyte i = 0; i < SDL_NumJoysticks(); i++) {
        
    }
}

void detectControllerInput (GameController controller) {
    // controller.lTrigger = SDL_GameControllerGetAxis(controller.SDL_Controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    // controller.rTrigger = SDL_GameControllerGetAxis(controller.SDL_Controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

    // controller.lStickX = SDL_GameControllerGetAxis(controller.SDL_Controller, SDL_CONTROLLER_AXIS_LEFTX);
    // controller.lStickY = SDL_GameControllerGetAxis(controller.SDL_Controller, SDL_CONTROLLER_AXIS_LEFTY);

    // short rStickX = SDL_GameControllerGetAxis(controller.SDL_Controller, SDL_CONTROLLER_AXIS_RIGHTX);
    // short rStickY = SDL_GameControllerGetAxis(controller.SDL_Controller, SDL_CONTROLLER_AXIS_RIGHTY);

    // //Button Press Detection
    // if (controller.SDL_Controller && event.type == SDL_CONTROLLERBUTTONDOWN) {
    //     printf("Controller: %i Button Pressed: %d\n", SDL_GameControllerName(controller.SDL_Controller), event.cbutton.button);
    // }
    // //Button Release Detection
    // if (controller.SDL_Controller && event.type == SDL_CONTROLLERBUTTONUP) {
    //     printf("Controller: %s Button Released: %d\n", SDL_GameControllerName(controller.SDL_Controller), event.cbutton.button);
    // }
    
    // //Left Trigger Press Detection
    // if (lTrigger > 20000) {
    //     printf("Controller: %i Left Trigger Full Tilt %d\n", SDL_GameControllerName(controller.SDL_Controller), lTrigger);
    // }
    // else if (lTrigger > 128) {
    //     printf("Controller: %i Left Trigger %d\n", SDL_GameControllerName(controller.SDL_Controller), lTrigger);
    // }
    // //Right Trigger Press Detection
    // if (rTrigger > 20000) {
    //     printf("Controller: %i Right Trigger Full Tilt: %d\n", SDL_GameControllerName(controller.SDL_Controller), rTrigger);
    // }
    // else if (rTrigger > 128) {
    //     printf("Controller: %i Right Trigger: %d\n", SDL_GameControllerName(controller.SDL_Controller), rTrigger);
    // }

    // //Left Stick X Detection
    // if (lStickX < -7000 || lStickX > 7000) {
    //     printf("Controller: %i Left Stick X: %i\n", SDL_GameControllerName(controller.SDL_Controller), lStickX);
    // }
    // //Left Stick Y Detection
    // if (lStickY < -7000 || lStickY > 7000) {
    //     printf("Controller: %i Left Stick Y: %i\n", SDL_GameControllerName(controller.SDL_Controller), lStickY);
    // }

    // //Right Stick X Detection
    // if (rStickX < -7000 || rStickX > 7000) {
    //     printf("Controller: %i Right Stick X: %i\n", SDL_GameControllerName(controller.SDL_Controller), rStickX);
    // }
    // //Right Stick Y Detection
    // if (rStickY < -7000 || rStickY > 7000) {
    //     printf("Controller: %i Right Stick Y: %i\n", SDL_GameControllerName(controller.SDL_Controller), rStickY);
    // }
}

#endif