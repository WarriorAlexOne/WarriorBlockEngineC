#include "WBE/Input/WBE_Input.h"
#include <SDL3/SDL.h>


void WBE_UpdateInput (WBE_Instance* instance) {
    while (SDL_PollEvent(&instance->event)) {
        if (instance->event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            SDL_DestroyWindow(SDL_GetWindowFromID(instance->event.window.windowID));
        }
        if (instance->event.type == SDL_EVENT_QUIT) {
            instance->quitProgram = true;
        }
        WBE_UpdateKeys(instance);
    }
    WBE_FrameUpdateKeys(instance);
}
