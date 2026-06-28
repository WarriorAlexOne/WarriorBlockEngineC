#include "WBE/WBE_Window.h"
#include "WBE/Input/WBE_Input.h"
#include "WBE/WBE_Defines.h"
#include "WBE/Debug/Debug_WBE_Window.h"
#include "WBE/WBE_Names.h"
#include "WBE/Util/WBE_String.h"
#include <SDL3_image/SDL_image.h>


// Add isWindowFocused boolean, focuse detection code, and a function that returns that boolean


WBE_Window* WBE_CreateWindow (WBE_Instance* instance, char title[], double width, double height) {
    WBE_Window* newWindow = SDL_malloc(sizeof(WBE_Window));

    newWindow->id = instance->windowCount+1;

    // Store default title.
    newWindow->title[0] = 'W';
    newWindow->title[1] = 'B';
    newWindow->title[2] = 'E';
    // Store true title.
    WBE_strcpy(newWindow->title, title, WBE_MAX_TITLE_LENGTH);

    SDL_CreateWindowAndRenderer(newWindow->title, width, height, SDL_WINDOW_RESIZABLE, &newWindow->sdl_window, &newWindow->sdl_renderer);

    // Store SDL ID.
    newWindow->sdl_id = SDL_GetWindowID(newWindow->sdl_window);

    // Store default icon path.
    WBE_strcpy(newWindow->iconPath, "assets/textures/misc/WBE_Logo.png", WBE_MAX_ICONPATH_LENGTH);
    WBE_SetWindowIcon(newWindow, newWindow->iconPath);

    // Grab display info and store it.
    const SDL_DisplayMode* displayData = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(newWindow->sdl_window));
    newWindow->displayCount = displayData->displayID;
    newWindow->displaySize.x = displayData->w;
    newWindow->displaySize.y = displayData->h;
    newWindow->displayRate = displayData->refresh_rate;

    // Store default values.
    newWindow->defaultSize.x = width;
    newWindow->defaultSize.y = height;
    newWindow->defaultPos.x = (newWindow->displaySize.x/2) - (width/2);
    newWindow->defaultPos.y = (newWindow->displaySize.y/2) - (height/2);

    // Store current values (default values are used).
    newWindow->size.x = width;
    newWindow->size.y = height;
    newWindow->pos.x = newWindow->defaultPos.x;
    newWindow->pos.y = newWindow->defaultPos.y;

    // Store window properties.
    newWindow->isFullscreen = false;
    newWindow->isBorderless = false;
    newWindow->isHidden = false;
    newWindow->isResizable = true;

    newWindow->quitWindow = false;
    newWindow->wasWindowQuit = false;

    // Manually center window position.
    // Attempts to make default values accurate until user is ready to update WBE in a loop and can collect window data.
    SDL_SetWindowPosition(newWindow->sdl_window, newWindow->defaultPos.x, newWindow->defaultPos.y);

    instance->windows[instance->windowCount++] = newWindow;
    instance->doesWindowExist = true;

    // if (debug) Debug_WBE_CreateWindow(window);
    return newWindow;
}

void CloseWindow (WBE_Instance* instance) {
    for (int i = 0; i < instance->windowCount; i++) {
        WBE_Window* getWindow = instance->windows[i];
        if (getWindow->quitWindow) {
            if (getWindow->sdl_renderer != NULL) SDL_DestroyRenderer(getWindow->sdl_renderer);
            if (getWindow->sdl_window != NULL) SDL_DestroyWindow(getWindow->sdl_window);
            getWindow->quitWindow = false;
            getWindow->wasWindowQuit = true;
        }
    }
}

// void WBE_UpdateWindows (WBE_Window* window) {
//     window->pos.x += window->vel.x;
//     window->pos.y += window->vel.y;
//     SDL_SetWindowPosition(window->sdl_window, (int)window->pos.x, (int)window->pos.y);
// }

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
