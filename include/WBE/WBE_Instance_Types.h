#ifndef WBE_INSTANCE_TYPES_H
#define WBE_INSTANCE_TYPES_H

#include <SDL3/SDL.h>
#include "WBE/WBE_Defines.h"
#include "WBE/Input/WBE_Scancodes.h"

typedef struct {
    bool isKeyDown[WBE_SCANCODE_COUNT];

    bool isKeyPressed[WBE_SCANCODE_COUNT];
    bool wasKeyPressed[WBE_SCANCODE_COUNT];

    bool isKeyReleased[WBE_SCANCODE_COUNT];
} WBE_Keyboard;

typedef struct {
    bool isInitialized;

    void** clocks;
    void** windows;

    SDL_Event event;
    WBE_Keyboard keyboard;  // Windows can't detect individual keyboard inputs, so there is only 1 per WBE Instance.

    int clockCount;
    int windowCount;

    bool doesClockExist;
    bool doesWindowExist;

    bool quitProgram;
} WBE_Instance;

#endif