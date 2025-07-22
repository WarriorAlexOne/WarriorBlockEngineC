#ifndef WAO_WINDOW_H
#define WAO_WINDOW_H

#include <SDL3/SDL.h>
#include "Utils/WAO_Vector2D.h"

#define WAO_MAX_WINDOW_COUNT 64
#define WAO_MAX_TITLE_LENGTH 1024
#define WAO_MAX_ICONPATH_LENGTH 1024

typedef struct {
    int id;

    SDL_Window* window;
    SDL_Renderer* renderer;
    int sdl_id;

    SDL_Color backgroundColor;

    char title[WAO_MAX_TITLE_LENGTH];
    char iconPath[WAO_MAX_ICONPATH_LENGTH];

    Vector2D_D pos;
    Vector2D_D size;

    Vector2D_D defaultPos;
    Vector2D_D defaultSize;

    bool isFullscreen;
    bool isBorderless;

    bool isHidden;

} WAO_Window;

#endif