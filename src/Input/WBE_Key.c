#include <SDL3/SDL.h>

#include "WBE/Input/WBE_Key.h"

WBE_KeyChecker* WBE_CreateKeyChecker () {
    WBE_KeyChecker* keyChecker = (WBE_KeyChecker*)SDL_malloc(sizeof(WBE_KeyChecker));
    if (keyChecker) {
        WBE_InitKeyCheck(keyChecker);
    }
    return keyChecker;
}

void WBE_InitKeyCheck (WBE_KeyChecker* keyCheckObject) {
    keyCheckObject->lastKeyEvent = 0;
    for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
        keyCheckObject->isKeyDown[i] = 0;
        keyCheckObject->keyPressed[i] = 0;
        keyCheckObject->keyReleased[i] = 0;
        keyCheckObject->wasPressed[i] = 0;
        keyCheckObject->wasReleased[i] = 0;
    }
}

void WBE_UpdateKeyCheck (WBE_KeyChecker* keyChecker, SDL_Event event) {
    // for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
    //     // if (event.type == SDL_EVENT_KEY_DOWN) {
    //     //     if (event.key.scancode == i) {
    //     //         keyChecker->isKeyDown[i] = 1;
    //     //     }
    //     // }
    //     // if (event.type == SDL_EVENT_KEY_UP) {
    //     //     if (event.key.scancode == i) {
    //     //         keyChecker->isKeyDown[i] = 0;
    //     //     }
    //     // }
    //     keyChecker->isKeyDown[i] = SDL_GetKeyboardState(NULL)[i];
    // }

    // keyChecker->keyPressed[keyChecker->lastKeyEvent] = false;
    // keyChecker->keyReleased[keyChecker->lastKeyEvent] = false;
    if (event.type == SDL_EVENT_KEY_DOWN) {
        keyChecker->lastKeyEvent = event.key.scancode;
        keyChecker->isKeyDown[keyChecker->lastKeyEvent] = true;
        // if (!keyChecker->wasPressed[keyChecker->lastKeyEvent]) {
        //     keyChecker->keyPressed[keyChecker->lastKeyEvent] = true;
            // keyChecker->wasPressed[keyChecker->lastKeyEvent] = true;
        //     keyChecker->wasReleased[keyChecker->lastKeyEvent] = false;
        // }
    }
    else if (event.type == SDL_EVENT_KEY_UP) {
        keyChecker->lastKeyEvent = event.key.scancode;
        keyChecker->isKeyDown[keyChecker->lastKeyEvent] = false;

        // if (!keyChecker->wasReleased[keyChecker->lastKeyEvent]) {
        //     keyChecker->keyReleased[keyChecker->lastKeyEvent] = true;
            // keyChecker->wasReleased[keyChecker->lastKeyEvent] = true;
        //     keyChecker->wasPressed[keyChecker->lastKeyEvent] = false;
        // }
    }
}

bool WBE_IsKeyDown (WBE_KeyChecker* keyChecker, int sdl_scancode) {
    if (keyChecker->isKeyDown[sdl_scancode]) return true;
    return false;
}
bool WBE_IsKeyUp (WBE_KeyChecker* keyChecker, int sdl_scancode) {
    if (!keyChecker->isKeyDown[sdl_scancode]) return true;
    return false;
}
// bool WBE_IsKeyPressed (WBE_KeyChecker* keyChecker, int sdl_scancode) {
//     if (keyChecker->isKeyDown[sdl_scancode] && !keyChecker->wasPressed[keyChecker->lastKeyEvent]) {
//         keyChecker->keyPressed[keyChecker->lastKeyEvent] = true;
//         keyChecker->wasPressed[keyChecker->lastKeyEvent] = true;
//         keyChecker->wasReleased[keyChecker->lastKeyEvent] = false;
//         return true;
//     }
//     return false;
// }
// bool WBE_IsKeyReleased (WBE_KeyChecker* keyChecker, int sdl_scancode) {
//     if (keyChecker->keyReleased[sdl_scancode]) {
//         keyChecker->wasReleased[keyChecker->lastKeyEvent] = true;
//         return true;
//     }
//     return false;
// }
