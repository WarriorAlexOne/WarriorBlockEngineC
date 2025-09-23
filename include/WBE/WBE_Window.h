#ifndef WBE_WINDOW_H
#define WBE_WINDOW_H

#include <SDL3/SDL.h>
#include "WBE/Util/WBE_Vec2D.h"

#define WBE_MAX_WINDOW_COUNT 64
#define WBE_MAX_TITLE_LENGTH 1024
#define WBE_MAX_ICONPATH_LENGTH 1024

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

    WBE_Vec2d speed;
    WBE_Vec2d vel;

    int displayNumber;
    WBE_Vec2i displaySize;
    float displayRate;

    bool isFullscreen;
    bool isBorderless;
    bool isHidden;
    bool isResizable;
} WBE_Window;

WBE_Window WBE_CreateWindow (char title[], double width, double height);
void WBE_CleanupWindows ();
void WBE_UpdateWindows (WBE_Window* window);
void WBE_SetWindowIcon (WBE_Window* window, char iconPath[]);
void WBE_SetWindowVelocity (WBE_Window* window, double x, double y);

#endif