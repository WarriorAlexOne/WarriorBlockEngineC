#ifndef WBE_WINDOW_H
#define WBE_WINDOW_H

#include <SDL3/SDL.h>
#include "WBE/Util/WBE_Vec2D.h"
#include "WBE/WBE_Instance_Types.h"

#define WBE_MAX_TITLE_LENGTH 256
#define WBE_MAX_ICONPATH_LENGTH 260

typedef struct {
    int id;

    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    int sdl_id;

    SDL_Color sdl_backgroundColor;

    char title[WBE_MAX_TITLE_LENGTH];
    char iconPath[WBE_MAX_ICONPATH_LENGTH];

    WBE_Vec2d pos;
    WBE_Vec2d size;

    WBE_Vec2d defaultPos;
    WBE_Vec2d defaultSize;

    int displayCount;
    WBE_Vec2i displaySize;
    float displayRate;

    bool isFullscreen;
    bool isBorderless;
    bool isHidden;
    bool isResizable;

    bool quitWindow;
    bool wasWindowQuit;

    bool debug;
} WBE_Window;

WBE_Window* WBE_CreateWindow (WBE_Instance* instance, char title[], double width, double height);
void CloseWindow (WBE_Instance* instance);
void WBE_SetWindowIcon (WBE_Window* window, char iconPath[]);

#endif