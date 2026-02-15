#ifndef WBE_INSTANCE_TYPES_H
#define WBE_INSTANCE_TYPES_H

#include <SDL3/SDL.h>
#include "WBE/WBE_Defines.h"

typedef struct {
    bool isKeyDown[SDL_SCANCODE_COUNT];

    bool isKeyPressed[SDL_SCANCODE_COUNT];
    bool wasKeyPressed[SDL_SCANCODE_COUNT];

    bool isKeyReleased[SDL_SCANCODE_COUNT];
} WBE_Keyboard;

typedef struct {
    bool isInitialized;

    void** clocks;
    void** windows;

    SDL_Event event;
    WBE_Keyboard keyboard;

    int clockCount;
    int windowCount;
    int keyCheckerCount;

    bool doesClockExist;
    bool doesWindowExist;
    bool doesKeyCheckerExist;
} WBE_Instance;

#endif