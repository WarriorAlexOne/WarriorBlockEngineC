#include "WBE/Input/WBE_Keyboard.h"


void WBE_UpdateKeys (WBE_Keys* keys) {
    const bool* keyStates = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
        keys->isKeyDown[i] = keyStates[i];

        if (!keys->isKeyDown[i]) {
            if (keys->isKeyReleased[i]) keys->isKeyReleased[i] = false;
            if (keys->wasKeyPressed[i]) keys->isKeyReleased[i] = true;
            keys->wasKeyPressed[i] = false;
            keys->isKeyPressed[i] = false;
            continue;
        }

        if (!keys->wasKeyPressed[i] && keys->isKeyDown[i]) {
            keys->wasKeyPressed[i] = true;
            keys->isKeyPressed[i] = true;
            continue;
        }

        if (keys->wasKeyPressed[i]) keys->isKeyPressed[i] = false;
    }
}

bool WBE_IsKeyDown (WBE_Keys* keys, int sdl_scancode) {
    return keys->isKeyDown[sdl_scancode];
}
bool WBE_IsKeyUp (WBE_Keys* keys, int sdl_scancode) {
    return !keys->isKeyDown[sdl_scancode];
}
bool WBE_IsKeyPressed (WBE_Keys* keys, int sdl_scancode) {
    return keys->isKeyPressed[sdl_scancode];
}
bool WBE_IsKeyReleased (WBE_Keys* keys, int sdl_scancode) {
    return keys->isKeyReleased[sdl_scancode];
}
