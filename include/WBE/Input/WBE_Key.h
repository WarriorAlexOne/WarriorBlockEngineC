#ifndef WBE_KEY_H
#define WBE_KEY_H

#include <SDL3/SDL.h>

typedef struct {
    int lastKeyEvent;

    bool isKeyDown[SDL_SCANCODE_COUNT];

    bool keyPressed[SDL_SCANCODE_COUNT];
    bool keyReleased[SDL_SCANCODE_COUNT];

    bool wasPressed[SDL_SCANCODE_COUNT];
    bool wasReleased[SDL_SCANCODE_COUNT];
} WBE_KeyChecker;

WBE_KeyChecker* WBE_CreateKeyChecker ();
void WBE_InitKeyCheck (WBE_KeyChecker* keyCheckObject);
void WBE_UpdateKeyCheck (WBE_KeyChecker* keyCheckObject, SDL_Event event);
bool WBE_IsKeyDown (WBE_KeyChecker* keyCheckObject, int sdl_scancode);
bool WBE_IsKeyUp (WBE_KeyChecker* keyCheckObject, int sdl_scancode);
bool WBE_IsKeyPressed (WBE_KeyChecker* keyCheckObject, int sdl_scancode);
bool WBE_IsKeyReleased (WBE_KeyChecker* keyCheckObject, int sdl_scancode);

#endif