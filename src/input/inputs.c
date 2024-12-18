#include <SDL2/SDL.h>

#include "../../include/util/global_variables.h"
#include "../../include/util/clocks.h"
#include "../../include/main/window.h"
#include "../../include/input/inputs.h"


SDL_Event event;  //Handles various inputs


void initInputs () {
    addCycleFunction(updateInputs);

    SDL_Log("Input Updater Initialized!\n");
}

void updateInputs () {
    SDL_PollEvent(&event);  //Start checking for events such as inputs

    for (int i = 0; i < windowsAdded; i++) {
        if (event.window.windowID == windowList[i].sdlID) {
            
            //Handle events for the windows
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                SDL_DestroyRenderer(windowList[i].renderer);
                SDL_DestroyWindow(windowList[i].window);
                windowList[i].renderer = NULL;
                windowList[i].window = NULL;
                windowCount--;
            }
        }
    }
    if (windowCount == 0) quit = true;
}