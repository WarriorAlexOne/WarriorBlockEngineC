#include "WBE/WBE_Instance.h"
#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Window.h"

WBE_Clock* currentClock;
WBE_Window* currentWindow;

WBE_Instance WBE_CreateNewInstance () {
    WBE_Instance newInstance = {
        .isInitialized = true,

        .clocks = SDL_malloc(sizeof(void*) * 8),
        .windows = SDL_malloc(sizeof(void*) * 8),
        .keyCheckers = SDL_malloc(sizeof(void*) * 8),

        .clockCount = 0,
        .windowCount = 0,
        .keyCheckerCount = 0,

        .doesClockExist = false,
        .doesWindowExist = false,
        .doesKeyCheckerExist = false
    };

    return newInstance;
}

void WBE_Update (WBE_Instance* instance) {
    if (instance->doesClockExist) {
        for (int i = 0; i < 1; i++) {
            currentClock = instance->clocks[i];
            WBE_UpdateClock(currentClock);
        }
    }
    if (instance->doesWindowExist) {
        for (int i = 0; i < 1; i++) {
            currentWindow = instance->windows[i];
        }
    }
}
