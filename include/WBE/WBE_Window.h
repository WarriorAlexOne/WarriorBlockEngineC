#ifndef WBE_WINDOW_H
#define WBE_WINDOW_H

#include <SDL3/SDL.h>
#include "WBE/Util/WBE_Vec2.h"

#define WBE_MAX_WINDOW_COUNT 64
#define WBE_MAX_TITLE_LENGTH 1024
#define WBE_MAX_ICONPATH_LENGTH 1024

typedef struct {
    int id;

    SDL_Window* window;
    SDL_Renderer* renderer;
    int sdl_id;

    SDL_Color backgroundColor;

    char title[WBE_MAX_TITLE_LENGTH];
    char iconPath[WBE_MAX_ICONPATH_LENGTH];

    WBE_Vec2_D pos;
    WBE_Vec2_D size;

    WBE_Vec2_D defaultPos;
    WBE_Vec2_D defaultSize;

    bool isFullscreen;
    bool isBorderless;

    bool isHidden;

} WBE_Window;

#endif