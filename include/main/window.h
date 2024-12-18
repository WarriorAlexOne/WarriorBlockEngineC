#ifndef WINDOW_H
#define WINDOW_H

#include "../../include/util/common.h"

#include <SDL2/SDL.h>

#include "../../include/util/vector_2D.h"

#define MAX_WINDOW_COUNT 64
#define MAX_TITLE_LENGTH 128
#define MAX_ICONPATH_LENGTH 128


typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char iconPath[MAX_TITLE_LENGTH];

    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 sdlID;

    bool isLoaded;

    Vec2_Int defaultCoords;
    Vec2_Int defaultSize;

    Vec2_Int coords;
    Vec2_Int size;

    bool enabled;
} Window;


#include "../../include/error/e_window.h"


void initWindows ();
void updateWindows ();
void createWindow (int windowID, char title[], int x, int y, int w, int h);
void toggleWindow (int windowID, bool state);
void setWindowIcon (int windowID, char iconPath[]);
void cleanupWindows ();

#endif