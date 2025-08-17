#ifndef WAO_KEY_H
#define WAO_KEY_H

#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct {
    int lastKeyDown;
    int lastKeyUp;

    bool keyDown[SDL_SCANCODE_COUNT];
    bool keyUp[SDL_SCANCODE_COUNT];

    bool keyPressed[SDL_SCANCODE_COUNT];
    bool keyReleased[SDL_SCANCODE_COUNT];

    bool wasPressed[SDL_SCANCODE_COUNT];
    bool wasReleased[SDL_SCANCODE_COUNT];
} Wao_KeyCheck;

Wao_KeyCheck* Wao_CreateKeyChecker ();
void Wao_InitKeyCheck (Wao_KeyCheck* keyCheckObject);
void Wao_UpdateKeyCheck (Wao_KeyCheck* keyCheckObject, SDL_Event event);
bool Wao_IsKeyDown (Wao_KeyCheck* keyCheckObject, int sdl_scancode);
bool Wao_IsKeyUp (Wao_KeyCheck* keyCheckObject, int sdl_scancode);
bool Wao_IsKeyPressed (Wao_KeyCheck* keyCheckObject, int sdl_scancode);
bool Wao_IsKeyReleased (Wao_KeyCheck* keyCheckObject, int sdl_scancode);

#endif