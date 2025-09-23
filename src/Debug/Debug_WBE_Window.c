#include "WBE/Debug/Debug_WBE_Window.h"
#include "WBE/WBE_Names.h"

void Debug_WBE_CreateWindow (WBE_Window window) {
    SDL_Log("%s Window WBE ID: %i\n", NAME_Debug_WBE_CreateWindow, window.id);

    SDL_Log("%s Is SDL_Window NULL: %s\n", NAME_Debug_WBE_CreateWindow, (window.sdl_window == NULL ? "True" : "False"));
    SDL_Log("%s Is SDL_Renderer NULL: %s\n", NAME_Debug_WBE_CreateWindow, (window.sdl_renderer == NULL ? "True" : "False"));
    SDL_Log("%s Window SDL ID: %i\n", NAME_Debug_WBE_CreateWindow, window.sdl_id);
    SDL_Log("%s Window Background Color: %i, %i, %i, %i\n", NAME_Debug_WBE_CreateWindow,
            window.sdl_backgroundColor.r, window.sdl_backgroundColor.g, window.sdl_backgroundColor.b, window.sdl_backgroundColor.a);

    SDL_Log("%s Window Title: %s\n", NAME_Debug_WBE_CreateWindow, window.title);
    SDL_Log("%s Window Icon Path: %s\n", NAME_Debug_WBE_CreateWindow, window.iconPath);

    SDL_Log("%s Window Position: X: %f   Y: %f\n", NAME_Debug_WBE_CreateWindow, window.pos.x, window.pos.y);
    SDL_Log("%s Window Size: W: %f   H: %f\n", NAME_Debug_WBE_CreateWindow, window.size.x, window.size.y);

    SDL_Log("%s Window Default Position: X: %f   Y: %f\n", NAME_Debug_WBE_CreateWindow, window.defaultPos.x, window.defaultPos.y);
    SDL_Log("%s Window Default Size: W: %f   H: %f\n", NAME_Debug_WBE_CreateWindow, window.defaultSize.x, window.defaultSize.y);

    SDL_Log("%s Display Number: %i\n", NAME_Debug_WBE_CreateWindow, window.displayNumber);
    SDL_Log("%s Display Size: W: %i   H: %i\n", NAME_Debug_WBE_CreateWindow, window.displaySize.x, window.displaySize.y);
    SDL_Log("%s Display Refresh Rate: %f\n", NAME_Debug_WBE_CreateWindow, window.displayRate);
    
    SDL_Log("%s Window Is Fullscreen: %s\n", NAME_Debug_WBE_CreateWindow, (window.isFullscreen == 1 ? "True" : "False"));
    SDL_Log("%s Window Is Borderless: %s\n", NAME_Debug_WBE_CreateWindow, (window.isBorderless == 1 ? "True" : "False"));
    SDL_Log("%s Window Is Hidden: %s\n", NAME_Debug_WBE_CreateWindow, (window.isHidden == 1 ? "True" : "False"));
    SDL_Log("%s Window Is Resizable: %s\n", NAME_Debug_WBE_CreateWindow, (window.isResizable == 1 ? "True" : "False"));
}