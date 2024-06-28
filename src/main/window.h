#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"


bool bordered = true;

SDL_Window* window;
SDL_Renderer* renderer;


void initMainWindow ();
void windowUpdate ();


void initMainWindow () {
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1300,
        800,
        SDL_WINDOW_SHOWN
        | SDL_WINDOW_RESIZABLE
    );
    renderer = SDL_CreateRenderer(window, -1, 2);

    SDL_Surface* windowIcon = IMG_Load(iconPath);
    if (windowIcon == NULL) {
        printf("SDL_image Error: %s\nUnable To Load Window Icon.\n", IMG_GetError());
        SDL_FreeSurface(windowIcon);
    }
    else {
        SDL_SetWindowIcon(window, windowIcon);
        SDL_FreeSurface(windowIcon);
    }
    addFrameFunction(windowUpdate);
    printf("Main Window Initialized!\n");
    printf("Renderer Initialized!\n");
}

void windowUpdate () {
    SDL_SetWindowTitle(window, titleFPS);
}

#endif