#include "WBE/WBE_Instance.h"
#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Window.h"
#include "WBE/Input/WBE_Input.h"
#include "WBE/WBE_Names.h"

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

    for (int i = 0; i < 8; i++) {
        newInstance.clocks[i] = NULL;
        newInstance.windows[i] = NULL;
    }

    for (int i = 0; i < WBE_SCANCODE_COUNT; i++) {
        newInstance.keyboard.isKeyDown[i] = 0;

        newInstance.keyboard.isKeyPressed[i] = 0;
        newInstance.keyboard.wasKeyPressed[i] = 0;

        newInstance.keyboard.isKeyReleased[i] = 0;
    }
    for (int i = 0; i < WBE_MAX_KEYLOGGER_LENGTH; i++) {
        newInstance.keyboard.keyLogs[i] = 0;
    }

    return newInstance;
}

void WBE_CleanupInstance (WBE_Instance* instance) {
    // Cleanup Windows and Renderers
    for (int i = 0; i < instance->windowCount; i++) {
        SDL_Log("Freed Window");
        SDL_free(instance->windows[i]);
    }
    SDL_free(instance->windows);
    SDL_Log("%s Cleaned up %i window%s and renderer%s!", WBE_NAME_CleanupInstance, instance->windowCount, (instance->windowCount != 1 ? "s" : ""), (instance->windowCount != 1 ? "s" : ""));

    // Cleanup Clocks
    for (int i = 0; i < instance->clockCount; i++) {
        SDL_free(instance->clocks[i]);
    }
    SDL_free(instance->clocks);
}

// void WBE_CleanupWindows (WBE_Instance* instance) {
//     for (int i = 0; i < 1; i++) {
//         instance->clocks[i];

//     }
// }

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

void WBE_QuitInstance (WBE_Instance* instance) {
    instance->quitProgram = true;
}

bool WBE_GetInstanceQuitState (WBE_Instance* instance) {
    return instance->quitProgram;
}
