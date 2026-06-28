#include "WBE/Input/WBE_Input.h"
#include <SDL3/SDL.h>
#include "WBE/WBE_Instance.h"
#include "WBE/WBE_Window.h"
#include "WBE/WBE_Clock.h"


void WBE_UpdateInput (WBE_Instance* instance) {
    while (SDL_PollEvent(&instance->event)) {
        if (instance->event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            for (int i = 0; i < instance->windowCount; i++) {
                WBE_Window* getWindow = instance->windows[i];
                if (getWindow->sdl_id == instance->event.window.windowID) {
                    getWindow->quitWindow = true;
                }
                CloseWindow(instance);
            }
        }
        if (instance->event.type == SDL_EVENT_QUIT) {
            WBE_QuitInstance(instance);
        }
        WBE_UpdateKeys(instance);
    }
    WBE_FrameUpdateKeys(instance);
}
