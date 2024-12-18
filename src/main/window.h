#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/vector2D.h"
#include "../utils/clock.h"


// char strFPS[16];
// char titleFPS[48];

typedef struct {
    SDL_Window* window;

    char title[128];
    char iconPath[128];

    Vec2_Int defaultCoords;
    Vec2_Int coords;
    Vec2_Int defaultSize;
    Vec2_Int size;

    SDL_Rect squareCoords;

    bool bordered;
    bool quit;
    bool isLoaded;

    SDL_Renderer* renderer;
} Window;

Window* windows = NULL;  //Global Window List
int windowCount = 0;     //Global Window Count


void createWindow (char title[], char iconPath[], int x, int y, int w, int h);
void loadWindow (Window* window);
void initRenderers (Window* window);
void initWindowUpdates ();
void windowUpdate ();
// void fpsToString ();
// void titleFPSString ();


void createWindow (char title[], char iconPath[], int x, int y, int w, int h) {
    windowCount++;

    windows = realloc(windows, windowCount * sizeof(Window));

    //Window Title
    strcpy(windows[windowCount-1].title, title);
    strcpy(windows[windowCount-1].iconPath, iconPath);

    windows[windowCount-1].defaultCoords.x = x;
    windows[windowCount-1].defaultCoords.y = y;
    windows[windowCount-1].defaultSize.x = w;
    windows[windowCount-1].defaultSize.y = h;

    windows[windowCount-1].quit = false;  //Main Window Exit
    windows[windowCount-1].bordered = true;
    windows[windowCount-1].isLoaded = false;

    windows[windowCount-1].coords.x = windows[windowCount-1].defaultCoords.x;
    windows[windowCount-1].coords.y = windows[windowCount-1].defaultCoords.y;
    windows[windowCount-1].size.x = windows[windowCount-1].defaultSize.x;
    windows[windowCount-1].size.y = windows[windowCount-1].defaultSize.y;

    windows[windowCount-1].squareCoords = makeRect(
        windows[windowCount-1].defaultCoords.x,
        windows[windowCount-1].defaultCoords.y,
        windows[windowCount-1].defaultSize.x,
        windows[windowCount-1].defaultSize.y
    );

    printf("Window %i Created & Initialized\n", windowCount);
}

void loadWindow (Window* window) {
    if (!window->isLoaded) {
        window->window = SDL_CreateWindow(
            window->title,
            window->defaultCoords.x,
            window->defaultCoords.y,
            window->size.x,
            window->size.y,
            SDL_WINDOW_SHOWN
            | SDL_WINDOW_RESIZABLE
        );
        window->isLoaded = true;

        initRenderers(window);
        printf("Window %i Loaded!\n", windowCount);
    }
}

void initRenderers (Window* window) {
    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* windowIcon = IMG_Load(window->iconPath);
    if (windowIcon == NULL) {
        printf("SDL_image Error: %s\nUnable To Load Window Icon.\n", IMG_GetError());
        SDL_FreeSurface(windowIcon);
    }
    else {
        SDL_SetWindowIcon(window->window, windowIcon);
        SDL_FreeSurface(windowIcon);
    }

    printf("Renderer For Window %i Initialized!\n", windowCount);
    initWindowUpdates();
}

void initWindowUpdates () {
    addFrameFunction(windowUpdate);
}

void windowUpdate () {
    // SDL_SetWindowTitle(window.window, titleFPS);
    SDL_GetWindowSize(windows[0].window, &windows[0].size.x, &windows[0].size.y);
    // printf("%i, %i\n", windows[0].size.x, windows[0].size.y);
}

// void fpsToString () {
//     if (fps < 100000000 && fps > 0) {
//         sprintf(strFPS, "%s%i", "FPS: ", fps);
//     }
// }
// void titleFPSString (Window window) {
//     if (fps < 100000000 && fps > 0) {
//         sprintf(titleFPS, "%s%s%i", window.title, "   FPS: ", fps);
//     }
// }

#endif