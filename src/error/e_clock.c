#include "../../include/util/common.h"

#include <SDL3/SDL.h>

#include "../../include/util/clock.h"

bool e_Clock_create (Clock* clock) {
    if (!clock) {
        SDL_Log("Error! Clock_create: Could not create Clock instance.");

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_create: Could not create Clock instance.", NULL);
        return false;
    }
    SDL_Log("Clock created.");
    return true;
}
bool e_Clock_destroy (Clock** clockPtr) {
    if (!*clockPtr) {
        SDL_Log("Error! Clock_destroy: Attempted to destroy a NULL Clock pointer.");

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_destroy: Attempted to destroy a NULL Clock pointer.", NULL);
        return false;
    }
    return true;
}

bool e_Clock_init (Clock* clock) {
    if (!clock) {
        SDL_Log("Error! Clock_init: Could not initialize Clock instance. Clock instance may be invalid or corrupted.");

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_init: Could not initialize Clock instance."
        "Clock instance may be invalid or corrupted.", NULL);
        return false;
    }
    return true;
}
bool e_Clock_update (Clock* clock) {
    if (!clock) {
        SDL_Log("Error! Clock_update: Could not update Clock instance. Clock instance may be invalid or corrupted.");
        return false;
    }
    return true;
}

bool e_Clock_cycleUpdate (Clock* clock, int i) {
    if (!clock->cycleUpdateFunctions[i]) {
        if (!clock->e_cycleUpdateErrorPositions[i]) {
            SDL_Log("Clock_cycleUpdate: Function in array element (%i) is null!", i);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_cycleUpdate: A function in the array element is null!", NULL);
            clock->e_cycleUpdateErrorPositions[i] = true;
        }
        return false;
    }
    return true;
}
bool e_Clock_frameUpdate (Clock* clock, int i) {
    if (!clock->frameUpdateFunctions[i]) {
        if (!clock->e_frameUpdateErrorPositions[i]) {
            SDL_Log("Clock_frameUpdate: Function in array element (%i) is null!", i);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_frameUpdate: A function in the array element is null!", NULL);
            clock->e_frameUpdateErrorPositions[i] = true;
        }
        return false;
    }
    return true;
}
bool e_Clock_tickUpdate (Clock* clock, int i) {
    if (!clock->tickUpdateFunctions[i]) {
        if (!clock->e_tickUpdateErrorPositions[i]) {
            SDL_Log("Clock_tickUpdate: Function in array element (%i) is null!", i);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_tickUpdate: A function in the array element is null!", NULL);
            clock->e_tickUpdateErrorPositions[i] = true;
        }
        return false;
    }
    return true;
}
bool e_Clock_secUpdate (Clock* clock, int i) {
    if (!clock->secUpdateFunctions[i]) {
        if (!clock->e_secUpdateErrorPositions[i]) {
            SDL_Log("Clock_secUpdate: Function in array element (%i) is null!", i);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_secUpdate: A function in the array element is null!", NULL);
            clock->e_secUpdateErrorPositions[i] = true;
        }
        return false;
    }
    return true;
}

bool e_Clock_addCycleFunction (Clock* clock, void (*function)()) {
    if (clock->cycleUpdateCount >= CYCLE_FUNCTION_LIMIT) {
        SDL_Log("Error! Clock_addCycleFunction: The cycle function limit has been reached (%i)", CYCLE_FUNCTION_LIMIT);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addCycleFunction: The cycle function limit has been reached.", NULL);
        clock->cycleUpdateCount = CYCLE_FUNCTION_LIMIT;
        return false;
    }
    else if (!function) {
        SDL_Log("Error! Clock_addCycleFunction: Function is null and can't be added.");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addCycleFunction: Function is null and can't be added.", NULL);
        return false;
    }
    return true;
}
bool e_Clock_addFrameFunction (Clock* clock, void (*function)()) {
    if (clock->frameUpdateCount >= FRAME_FUNCTION_LIMIT) {
        SDL_Log("Error! Clock_addFrameFunction: The frame function limit has been reached (%i)", FRAME_FUNCTION_LIMIT);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addFrameFunction: The frame function limit has been reached.", NULL);
        clock->frameUpdateCount = FRAME_FUNCTION_LIMIT;
        return false;
    }
    else if (!function) {
        SDL_Log("Error! Clock_addFrameFunction: Function is null and can't be added.");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addFrameFunction: Function is null and can't be added.", NULL);
        return false;
    }
    return true;
}
bool e_Clock_addTickFunction (Clock* clock, void (*function)()) {
    if (clock->tickUpdateCount >= TICK_FUNCTION_LIMIT) {
        SDL_Log("Error! Clock_addTickFunction: The tick function limit has been reached (%i)", TICK_FUNCTION_LIMIT);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addTickFunction: The tick function limit has been reached.", NULL);
        clock->tickUpdateCount = TICK_FUNCTION_LIMIT;
        return false;
    }
    else if (!function) {
        SDL_Log("Error! Clock_addTickFunction: Function is null and can't be added.");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addTickFunction: Function is null and can't be added.", NULL);
        return false;
    }
    return true;
}
bool e_Clock_addSecFunction (Clock* clock, void (*function)()) {
    if (clock->secUpdateCount >= SEC_FUNCTION_LIMIT) {
        SDL_Log("Error! Clock_addSecFunction: The sec function limit has been reached (%i)", SEC_FUNCTION_LIMIT);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addSecFunction: The sec function limit has been reached.", NULL);
        clock->secUpdateCount = SEC_FUNCTION_LIMIT;
        return false;
    }
    else if (!function) {
        SDL_Log("Error! Clock_addSecFunction: Function is null and can't be added.");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Clock_addSecFunction: Function is null and can't be added.", NULL);
        return false;
    }
    return true;
}
