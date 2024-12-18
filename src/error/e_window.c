#include "../../include/util/common.h"

#include <SDL2/SDL.h>

#include "../../include/main/window.h"


//Returns 1 if an error is found. Returns 0 otherwise.
bool e_initWindows () {
    if (window_list_initialized) {  //windowList: Check if window list was initialized first
        SDL_Log("%s Window List already initialized!\n", init_windows);
        return 1;
    }
    return 0;
}

bool e_createWindow (int windowID, char title[], int x, int y, int w, int h) {
    if (!window_list_initialized) {  //windowList: Check if window list was initialized first
        SDL_Log("%s Can't Create Window, %s\n", create_window, window_list_not_init);
        return 1;
    }
    if (windowID < 0) {  //ID: Check if value is too low
        SDL_Log("%s Window ID value is too low! Please use an available ID above 0. Current ID is: %i.\n", create_window, windowID);
        return 1;
    }
    if (windowID >= MAX_WINDOW_COUNT) {  //ID: Check if value is too high
        SDL_Log("%s Window ID value is above the max value! Please use a different ID or increase the MAX_WINDOW_COUNT. Current ID is: %i. MAX_WINDOW_COUNT: %i.\n", create_window, windowID, MAX_WINDOW_COUNT);
        return 1;
    }
    if (windowList[windowID].id != -1) {  //ID: Check if window was already created
        SDL_Log("%s A Window with this ID has already been created! Please use a different ID. Current ID is: %i.\n", create_window, windowList[windowID].id);
        return 1;
    }
    if (strlen(title) > MAX_TITLE_LENGTH) {  //Title: Check if title is too long
        SDL_Log("%s Window Title is too long! Please use a shorter title, or increase the MAX_TITLE_LENGTH. Current title length: %i. MAX_TITLE_LENGTH: %i.\n", create_window, strlen(title), MAX_TITLE_LENGTH);
        return 1;
    }

    //No other checks are necessary (probably...)

    return 0;
}

bool e_toggleWindow (int windowID, bool state) {
    if (!window_list_initialized) {  //windowList: Check if window list was initialized first
        SDL_Log("%s Can't Toggle Window! %s\n", toggle_window, window_list_not_init);
        return 1;
    }
    if (windowID < 0) {  //ID: Check if value is too low
        SDL_Log("%s Window ID value is too low! Please use an assigned ID above -1. Current ID is: %i.\n", toggle_window, windowID);
        return 1;
    }
    if (windowID >= MAX_WINDOW_COUNT) {  //ID: Check if value is too high
        SDL_Log("%s Window ID value is above the max value! Please use a different ID. Current ID is: %i. MAX_WINDOW_COUNT: %i.\n", toggle_window, windowID, MAX_WINDOW_COUNT);
        return 1;
    }
    if (!windowList[windowID].isLoaded) {  //Create Window: Check if window was created and the data was loaded
        SDL_Log("%s There is no Window with this ID! Please use a different ID. Current ID is: %i.\n", toggle_window, windowID);
        return 1;
    }
    if (state) {  //State: If enabling window:
        if (windowList[windowID].enabled) {  //windowList: Check if window is already on screen
            SDL_Log("%s Window already enabled!", toggle_window);
            return 1;
        }
        if (windowList[windowID].window != NULL) {  //windowList: Check if there's already a window assigned
            SDL_Log("%s Window already exists! Window assigned somewhere else.\n", toggle_window);
            return 1;
        }
        if (windowList[windowID].renderer != NULL) {  //windowList: Check if there's already a renderer assigned
            SDL_Log("%s Renderer already exists! Renderer assigned somewhere else.\n", toggle_window);
            return 1;
        }
    }
    else if (!state) {  //State: If disabling window:
        if (!windowList[windowID].enabled) {  //windowList: Check if window is already removed from screen
            SDL_Log("%s Window %i already Disabled!\n", toggle_window, windowID);
            return 1;
        }
        if (windowList[windowID].window == NULL) {  //windowList: Check if window already exists
            SDL_Log("%s Window doesn't exist! Please create a window.\n", toggle_window);
            return 1;
        }
        if (windowList[windowID].renderer == NULL) {  //windowList: Check if renderer already exists
            SDL_Log("%s Renderer doesn't exist! Please create a window/renderer.\n", toggle_window);
            return 1;
        }
    }

    //No other checks are necessary (probably...)

    return 0;
}

bool e_setWindowIcon (int windowID, char iconPath[]) {
    if (!window_list_initialized) {  //windowList: Check if window list was initialized first
        SDL_Log("%s Window List not initialized!\n", set_window_icon);
        return 1;
    }
    if (strlen(iconPath) > MAX_ICONPATH_LENGTH) {  //Title: Check if iconPath is too long
        SDL_Log("%s Window Icon Path is too long! Please use a shorter title or increase the MAX_ICONPATH_LENGTH. Current Icon Path length is: %i.\n", set_window_icon, strlen(iconPath));
        return 1;
    }

    //No other checks are necessary (probably...)

    return 0;
}

bool e_cleanupWindows () {
    if (!window_list_initialized) {  //windowList: Check if window list was initialized first
        SDL_Log("%s Window List not initialized!\n", cleanup_windows);
        return 1;
    }

    //No other checks are necessary (probably...)

    return 0;
}