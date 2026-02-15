#include "WBE/WBE_Window.h"
#include "WBE/Input/WBE_Input.h"
#include "WBE/WBE_Defines.h"
#include "WBE/Debug/Debug_WBE_Window.h"
#include "WBE/WBE_Names.h"
#include "WBE/Util/WBE_String.h"
#include <SDL3_image/SDL_image.h>


bool debug = 0;

int windowCount = 0;

void* windowTracker[WBE_MAX_WINDOW_COUNT];
void* rendererTracker[WBE_MAX_WINDOW_COUNT];


WBE_Window WBE_CreateWindow (char title[], double width, double height) {
    WBE_Window window = {0};

    window.id = ++windowCount;

    // Store default title.
    window.title[0] = 'W';
    window.title[1] = 'B';
    window.title[2] = 'E';
    // Store true title.
    WBE_strcpy(window.title, title, WBE_MAX_TITLE_LENGTH);

    SDL_CreateWindowAndRenderer(window.title, width, height, SDL_WINDOW_RESIZABLE, &window.sdl_window, &window.sdl_renderer);

    // Store SDL ID.
    window.sdl_id = SDL_GetWindowID(window.sdl_window);

    // Store default icon path.
    WBE_strcpy(window.iconPath, "assets/textures/misc/WBE_Logo.png", WBE_MAX_ICONPATH_LENGTH);

    // Grab display info and store it.
    const SDL_DisplayMode* displayData = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window.sdl_window));
    window.displayNumber = displayData->displayID;
    window.displaySize.x = displayData->w;
    window.displaySize.y = displayData->h;
    window.displayRate = displayData->refresh_rate;

    // Store default values.
    window.defaultSize.x = width;
    window.defaultSize.y = height;
    window.defaultPos.x = (window.displaySize.x/2) - (width/2);
    window.defaultPos.y = (window.displaySize.y/2) - (height/2);

    // Store current values (default values are used).
    window.size.x = width;
    window.size.y = height;
    window.pos.x = window.defaultPos.x;
    window.pos.y = window.defaultPos.y;

    // Store movement properties.
    window.speed.x = 0;
    window.speed.y = 0;
    window.vel.x = 0;
    window.vel.y = 0;

    // Store window properties.
    window.isFullscreen = false;
    window.isBorderless = false;
    window.isHidden = false;
    window.isResizable = true;

    // Manually center window position.
    // Attempts to make default values accurate until user is ready to update WBE in a loop and can collect window data.
    SDL_SetWindowPosition(window.sdl_window, window.defaultPos.x, window.defaultPos.y);

    // Stores window and renderer pointers to automatically free later.
    windowTracker[windowCount-1] = window.sdl_window;
    rendererTracker[windowCount-1] = window.sdl_renderer;
    
    if (debug) Debug_WBE_CreateWindow(window);
    return window;
}

// Automatically handles cleanup of all windows when called.
void WBE_CleanupWindows () {
    if (windowCount > 0) {
        for (int i = 0; i < windowCount; i++) {
            SDL_DestroyRenderer(rendererTracker[i]);
            SDL_DestroyWindow(windowTracker[i]);
            rendererTracker[i] = NULL;
            windowTracker[i] = NULL;
            SDL_Log("%s Window %i Cleaned Up!\n", WBE_NAME_CleanupWindows, i+1);
        }
        return;
    }
    SDL_Log("%s No windows were created. All clean.\n", WBE_NAME_CleanupWindows);
}

// Required to update the data of all windows.
void WBE_UpdateWindows (WBE_Window* window) {
    window->pos.x += window->vel.x;
    window->pos.y += window->vel.y;
    SDL_SetWindowPosition(window->sdl_window, (int)window->pos.x, (int)window->pos.y);
}

void WBE_SetWindowIcon (WBE_Window* window, char iconPath[]) {
    char safePath[WBE_MAX_ICONPATH_LENGTH];
    int errorNum = WBE_strcpy(safePath, iconPath, WBE_MAX_ICONPATH_LENGTH); // Copy string and get error num.

    // Ensures that path is valid before use.
    if (errorNum == 1) {
        SDL_Log ("%s Path argument is too long!", WBE_NAME_SetWindowIcon);
        return;
    }
    else if (errorNum == -1) {
        SDL_Log ("%s Path argument is invalid!", WBE_NAME_SetWindowIcon);
        return;
    }

    SDL_Surface* test = IMG_Load(safePath);
    SDL_SetWindowIcon(window->sdl_window, test);
    SDL_DestroySurface(test);
}

void WBE_SetWindowVelocity (WBE_Window* window, double x, double y) {
    window->vel.x = x;
    window->vel.y = y;
}

void* WBE_GetWindowTracker () {
    return windowTracker;
}

int WBE_GetWindowCount () {
    return windowCount;
}
