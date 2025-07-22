#ifndef WBE_WINDOW_H
#define WBE_WINDOW_H

#include <SDL3/SDL.h>
#include "Utils/WBE_Vector2D.h"

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

    WBE_Vector2D_D pos;
    WBE_Vector2D_D size;

    WBE_Vector2D_D defaultPos;
    WBE_Vector2D_D defaultSize;

    bool isFullscreen;
    bool isBorderless;

    bool isHidden;

} WBE_Window;

#endif