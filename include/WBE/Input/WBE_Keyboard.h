#ifndef WBE_KEY_H
#define WBE_KEY_H

#include <SDL3/SDL.h>


typedef struct {
    bool isKeyDown[SDL_SCANCODE_COUNT];

    bool isKeyPressed[SDL_SCANCODE_COUNT];
    bool wasKeyPressed[SDL_SCANCODE_COUNT];

    bool isKeyReleased[SDL_SCANCODE_COUNT];
} WBE_Keys;


void WBE_UpdateKeys (WBE_Keys* keyCheckObject);
bool WBE_IsKeyDown (WBE_Keys* keyCheckObject, int sdl_scancode);
bool WBE_IsKeyUp (WBE_Keys* keyCheckObject, int sdl_scancode);
bool WBE_IsKeyPressed (WBE_Keys* keyCheckObject, int sdl_scancode);
bool WBE_IsKeyReleased (WBE_Keys* keyCheckObject, int sdl_scancode);

#endif