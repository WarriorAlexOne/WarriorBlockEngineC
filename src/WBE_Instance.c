#include "WBE/WBE_Instance.h"
#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Window.h"
#include "WBE/Input/WBE_Input.h"

WBE_Clock* currentClock;
WBE_Window* currentWindow;

WBE_Instance WBE_CreateNewInstance () {
    WBE_Instance newInstance = {
        .isInitialized = true,

        .clocks = SDL_malloc(sizeof(void*) * 8),
        .windows = SDL_malloc(sizeof(void*) * 8),

        .event = {0},
        .keyboard = {0},

        .clockCount = 0,
        .windowCount = 0,

        .doesClockExist = false,
        .doesWindowExist = false,

        .quitProgram = false
    };

    return newInstance;
}

// Returns 1 while the WBE Instance is active, or 0 upon Instance quitting.
bool WBE_Update (WBE_Instance* instance) {
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
    WBE_UpdateInput(instance);

    if (instance->quitProgram) return 0;
    return 1;
}

bool WBE_InstanceQuitState (WBE_Instance* instance) {
    return instance->quitProgram;
}
