#include "../../include/util/common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../include/util/global_variables.h"
#include "../../include/util/clocks.h"
#include "../../include/main/window.h"


Window windowList[MAX_WINDOW_COUNT];
int windowsAdded = 0;
int windowCount = 0;
bool window_list_initialized = false;


void initWindows () {
    if (e_initWindows()) return;

    for (int i = 0; i < MAX_WINDOW_COUNT; i++) {
        windowList[i].id = -1;
        strcpy(windowList[i].title, "NULL");
        strcpy(windowList[i].iconPath, "NULL");
        windowList[i].window = NULL;
        windowList[i].renderer = NULL;
        windowList[i].sdlID = -1;
        windowList[i].isLoaded = false;
        windowList[i].defaultCoords.x = SDL_WINDOWPOS_CENTERED;
        windowList[i].defaultCoords.y = SDL_WINDOWPOS_CENTERED;
        windowList[i].defaultSize.x = 800;
        windowList[i].defaultSize.y = 600;
        windowList[i].coords.x = windowList[i].defaultCoords.x;
        windowList[i].coords.y = windowList[i].defaultCoords.y;
        windowList[i].size.x = windowList[i].defaultSize.x;
        windowList[i].size.y = windowList[i].defaultSize.y;
        windowList[i].enabled = false;
    }

    addFrameFunction(updateWindows);

    window_list_initialized = true;
    SDL_Log("Window List Initialized!\n");
}

void createWindow (int windowID, char title[], int x, int y, int w, int h) {
    if (e_createWindow(windowID, title, x, y, w, h)) return;

    windowList[windowID].id = windowID;

    strcpy(windowList[windowID].title, title);

    windowList[windowID].defaultCoords.x = x;
    windowList[windowID].defaultCoords.y = y;
    windowList[windowID].defaultSize.x = w;
    windowList[windowID].defaultSize.y = h;

    windowList[windowID].coords.x = x;
    windowList[windowID].coords.y = y;
    windowList[windowID].size.x = w;
    windowList[windowID].size.y = h;

    windowList[windowID].isLoaded = true;
    
    windowsAdded++;
    SDL_Log("Window %i Created!\n", windowID);
}

void toggleWindow (int windowID, bool state) {
    if (e_toggleWindow(windowID, state)) return;
    
    if (state) {
        windowList[windowID].window = SDL_CreateWindow(
            windowList[windowID].title,
            windowList[windowID].coords.x,
            windowList[windowID].coords.y,
            windowList[windowID].size.x,
            windowList[windowID].size.y,
            SDL_WINDOW_SHOWN
            | SDL_WINDOW_RESIZABLE
        );
        windowList[windowID].sdlID = SDL_GetWindowID(windowList[windowID].window);
        windowList[windowID].renderer = SDL_CreateRenderer(windowList[windowID].window, -1, SDL_RENDERER_ACCELERATED);

        windowList[windowID].enabled = true;
        
        windowCount++;
        SDL_Log("Window %i Enabled!\n", windowID);
    }
    else if (!state) {
        SDL_DestroyRenderer(windowList[windowID].renderer);
        SDL_DestroyWindow(windowList[windowID].window);

        windowList[windowID].window = NULL;
        windowList[windowID].renderer = NULL;

        windowList[windowID].enabled = false;

        windowCount--;
        SDL_Log("Window %i Disabled!\n", windowID);
    }
}

void updateWindows () {
    for (int i = 0; i < windowsAdded; i++) {
        if (windowList[i].enabled) {
            SDL_GetWindowSize(windowList[i].window, &windowList[i].size.x, &windowList[i].size.y);
        }
    }
}

void setWindowIcon (int windowID, char iconPath[]) {
    if (e_setWindowIcon(windowID, iconPath)) return;

    SDL_Surface* windowIcon = IMG_Load(iconPath);

    if (windowIcon == NULL) {
        SDL_Log("SET WINDOW ICON: No Window Icon found! SDL_image error code: %s.\n", IMG_GetError());
        SDL_FreeSurface(windowIcon);
        return;
    }
    SDL_SetWindowIcon(windowList[windowID].window, windowIcon);
    SDL_FreeSurface(windowIcon);
}

void cleanupWindows () {
    if (e_cleanupWindows()) return;

    for (int i = 0; i < MAX_WINDOW_COUNT; i++) {
        SDL_DestroyRenderer(windowList[i].renderer);
        SDL_DestroyWindow(windowList[i].window);
        windowList[i].renderer = NULL;
        windowList[i].window = NULL;
    }
    SDL_Log("Freed Window List!\n");
}
