#include "WBE/Input/WBE_Keyboard.h"


void WBE_UpdateKeys (WBE_Instance* instance) {
    if (instance->event.key.scancode < 0 || instance->event.key.scancode > SDL_SCANCODE_COUNT) return;
    int scancode = instance->event.key.scancode;

    if (instance->event.type == SDL_EVENT_KEY_DOWN) {
        instance->keyboard.isKeyDown[scancode] = true;
    }
    if (instance->event.type == SDL_EVENT_KEY_UP) {
        instance->keyboard.isKeyDown[scancode] = false;
        instance->keyboard.isKeyReleased[scancode] = true;
    }

    for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
        if (instance->keyboard.isKeyDown[i]) {
            SDL_Log("%s KEY!!!", SDL_GetScancodeName(i));
        }
    }

    // if (!instance->keyboard.isKeyDown[scancode] && instance->event.type == SDL_EVENT_KEY_UP) {
    //     if (instance->keyboard.isKeyReleased[scancode]) instance->keyboard.isKeyReleased[scancode] = false;
    //     if (instance->keyboard.wasKeyPressed[scancode]) instance->keyboard.isKeyReleased[scancode] = true;
    //     instance->keyboard.wasKeyPressed[scancode] = false;
    //     instance->keyboard.isKeyPressed[scancode] = false;
    //     SDL_Log("RELEASED!");
    //     return;
    // }
  
    // if (!instance->keyboard.wasKeyPressed[scancode] && instance->keyboard.isKeyDown[scancode]) {
    //     instance->keyboard.wasKeyPressed[scancode] = true;
    //     instance->keyboard.isKeyPressed[scancode] = true;
    //     SDL_Log("PRESSED!");
    //     return;
    // }

    // if (instance->keyboard.wasKeyPressed[scancode]) instance->keyboard.isKeyPressed[scancode] = false;
}

void WBE_FrameUpdateKeys (WBE_Instance* instance) {
    for (int scancode = 0; scancode < SDL_SCANCODE_COUNT; scancode++) {
        if (!instance->keyboard.isKeyDown[scancode]) {
            if (instance->keyboard.isKeyReleased[scancode]) instance->keyboard.isKeyReleased[scancode] = false;
            if (instance->keyboard.wasKeyPressed[scancode]) instance->keyboard.isKeyReleased[scancode] = true;
            instance->keyboard.wasKeyPressed[scancode] = false;
            instance->keyboard.isKeyPressed[scancode] = false;
            continue;
        }
        if (instance->keyboard.wasKeyPressed[scancode]) {
            instance->keyboard.isKeyPressed[scancode] = false;
            continue;
        }

        instance->keyboard.isKeyPressed[scancode] = true;
        instance->keyboard.wasKeyPressed[scancode] = true;
    }
}

// void WBE_UpdateKeys () {
//     for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
//         keys->isKeyDown[i] = keyStates[i];

//         if (!keys->isKeyDown[i]) {
//             if (keys->isKeyReleased[i]) keys->isKeyReleased[i] = false;
//             if (keys->wasKeyPressed[i]) keys->isKeyReleased[i] = true;
//             keys->wasKeyPressed[i] = false;
//             keys->isKeyPressed[i] = false;
//             continue;
//         }

//         if (!keys->wasKeyPressed[i] && keys->isKeyDown[i]) {
//             keys->wasKeyPressed[i] = true;
//             keys->isKeyPressed[i] = true;
//             continue;
//         }

//         if (keys->wasKeyPressed[i]) keys->isKeyPressed[i] = false;
//     }
// }


//     // const bool* keyStates = SDL_GetKeyboardState(NULL);

bool WBE_IsKeyDown (WBE_Instance* instance, int sdl_scancode) {
    return instance->keyboard.isKeyDown[sdl_scancode];
}
bool WBE_IsKeyUp (WBE_Instance* instance, int sdl_scancode) {
    return !instance->keyboard.isKeyDown[sdl_scancode];
}
bool WBE_IsKeyPressed (WBE_Instance* instance, int sdl_scancode) {
    return instance->keyboard.isKeyPressed[sdl_scancode];
}
bool WBE_IsKeyReleased (WBE_Instance* instance, int sdl_scancode) {
    return instance->keyboard.isKeyReleased[sdl_scancode];
}
