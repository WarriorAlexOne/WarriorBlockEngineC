#include "../../include/util/common.h"

#include <SDL3/SDL.h>

#include "../../include/util/clock.h"
#include "../../include/error/e_clock.h"

// Get system time in nanoseconds, converted to an 64-bit int  (Replaced with SDL_GetTicksNS to ensure multiplatform compatibility)
// This function is known to work for Windows, Linux, and Android. Not tested on other platforms. Kept for any usefulness.
// long long int Clock_nanoTime() {
//     struct timespec ts;
//     clock_gettime(1, &ts);
//     return (long long int)ts.tv_sec * NANO_SEC + ts.tv_nsec;
// }

// Create a new Clock instance
Clock* Clock_create () {
    Clock* clock = malloc(sizeof(Clock));
    if (!e_Clock_create(clock)) return NULL;

    Clock_init(clock);
    return clock;
}

// Destroy a Clock instance
void Clock_destroy (Clock** clockPtr) {
    if (!e_Clock_destroy(clockPtr)) return;

    free(*clockPtr);
    *clockPtr = NULL;
    SDL_Log("Clock destroyed.");
}

// Initialize the Clock
void Clock_init (Clock* clock) {
    if (!e_Clock_init(clock)) return;
    clock->currentCycleTime = SDL_GetTicksNS();
    clock->lastCycleTime = clock->currentCycleTime;
    clock->cycleDelta = (clock->currentCycleTime - clock->lastCycleTime) / NANO_SEC;
    clock->cps = 0;
    clock->getCPS = 0;

    clock->frameRate = DEFAULT_FRAMERATE;
    clock->frameTime = NANO_SEC / clock->frameRate;
    clock->frameTarget = clock->currentCycleTime + clock->frameTime;
    clock->lastFrameTime = clock->currentCycleTime;
    clock->frameDelta = (clock->currentCycleTime - clock->lastFrameTime) / NANO_SEC;
    clock->fps = 0;
    clock->getFPS = 0;

    clock->tickRate = DEFAULT_TICKRATE;
    clock->tickTime = NANO_SEC / DEFAULT_TICKRATE;
    clock->tickTarget = clock->currentCycleTime + clock->tickTime;
    clock->tickDelta = 0;
    clock->tps = 0;
    clock->getTPS = 0;

    clock->secTime = clock->currentCycleTime + NANO_SEC;

    for (int i = 0; i < CYCLE_FUNCTION_LIMIT; i++) {
        clock->cycleUpdateFunctions[i] = NULL;
    }
    for (int i = 0; i < FRAME_FUNCTION_LIMIT; i++) {
        clock->frameUpdateFunctions[i] = NULL;
    }
    for (int i = 0; i < TICK_FUNCTION_LIMIT; i++) {
        clock->tickUpdateFunctions[i] = NULL;
    }
    for (int i = 0; i < SEC_FUNCTION_LIMIT; i++) {
        clock->secUpdateFunctions[i] = NULL;
    }

    clock->cycleUpdateCount = 0;
    clock->frameUpdateCount = 0;
    clock->tickUpdateCount = 0;
    clock->secUpdateCount = 0;

    for (int i = 0; i < CYCLE_FUNCTION_LIMIT; i++) {
        clock->e_cycleUpdateErrorPositions[i] = false;
    }
    for (int i = 0; i < FRAME_FUNCTION_LIMIT; i++) {
        clock->e_frameUpdateErrorPositions[i] = false;
    }
    for (int i = 0; i < TICK_FUNCTION_LIMIT; i++) {
        clock->e_tickUpdateErrorPositions[i] = false;
    }
    for (int i = 0; i < SEC_FUNCTION_LIMIT; i++) {
        clock->e_secUpdateErrorPositions[i] = false;
    }

    SDL_Log("Clock initialized.");
}

// Update the Clock
void Clock_update (Clock* clock) {
    if (!e_Clock_update(clock)) return;
    Clock_cycleUpdate(clock);
    
    clock->currentCycleTime = SDL_GetTicksNS();

    clock->cycleDelta = (clock->currentCycleTime - clock->lastCycleTime) / (double)NANO_SEC;
    clock->tickDelta += (clock->currentCycleTime - clock->lastCycleTime) / clock->tickTime;
    clock->lastCycleTime = clock->currentCycleTime;

    clock->cps++;

    // 1 Sec Loop
    if (clock->currentCycleTime >= clock->secTime) {
        Clock_secUpdate(clock);

        clock->secTime = clock->currentCycleTime + NANO_SEC;

        clock->getCPS = clock->cps;
        clock->getFPS = clock->fps;
        clock->getTPS = clock->tps;

        clock->cps = 0;
        clock->fps = 0;
        clock->tps = 0;
    }

    // Frame Loop
    while (clock->currentCycleTime >= clock->frameTarget) {
        Clock_frameUpdate(clock);

        clock->frameDelta = (clock->currentCycleTime - clock->lastFrameTime) / (double)NANO_SEC;
        clock->lastFrameTime = clock->currentCycleTime;

        clock->frameTarget = clock->currentCycleTime + clock->frameTime;

        clock->fps++;

        // Tick Loop
        while (clock->tickDelta >= 1) {
            Clock_tickUpdate(clock);

            clock->tickDelta--;

            clock->tps++;

            if (clock->tickDelta > TICK_CATCHUP_LIMIT) {
                clock->tickDelta = TICK_CATCHUP_LIMIT;
            }
        }
    }
}

// Update functions (Updated within the Clock_update function. Not recommended to use anywhere)
void Clock_cycleUpdate (Clock* clock) {
    for (int i = 0; i < clock->cycleUpdateCount; i++) {
        if (!e_Clock_cycleUpdate(clock, i)) continue;
        clock->cycleUpdateFunctions[i]();
    }
}
void Clock_frameUpdate (Clock* clock) {
    for (int i = 0; i < clock->frameUpdateCount; i++) {
        if (!e_Clock_frameUpdate(clock, i)) continue;
        clock->frameUpdateFunctions[i]();
    }
}
void Clock_tickUpdate (Clock* clock) {
    for (int i = 0; i < clock->tickUpdateCount; i++) {
        if (!e_Clock_tickUpdate(clock, i)) continue;
        clock->tickUpdateFunctions[i]();
    }
}
void Clock_secUpdate (Clock* clock) {
    for (int i = 0; i < clock->secUpdateCount; i++) {
        if (!e_Clock_secUpdate(clock, i)) continue;
        clock->secUpdateFunctions[i]();
    }
}

// Add functions
void Clock_addCycleFunction (Clock* clock, void (*function)()) {
    if (!e_Clock_addCycleFunction(clock, function)) return;
    clock->cycleUpdateFunctions[clock->cycleUpdateCount] = function;
    clock->cycleUpdateCount++;
}
void Clock_addFrameFunction (Clock* clock, void (*function)()) {
    if (!e_Clock_addCycleFunction(clock, function)) return;
    clock->frameUpdateFunctions[clock->frameUpdateCount] = function;
    clock->frameUpdateCount++;
}
void Clock_addTickFunction (Clock* clock, void (*function)()) {
    if (!e_Clock_addTickFunction(clock, function)) return;
    clock->tickUpdateFunctions[clock->tickUpdateCount] = function;
    clock->tickUpdateCount++;
}
void Clock_addSecFunction (Clock* clock, void (*function)()) {
    if (!e_Clock_addSecFunction(clock, function)) return;
    clock->secUpdateFunctions[clock->secUpdateCount] = function;
    clock->secUpdateCount++;
}
