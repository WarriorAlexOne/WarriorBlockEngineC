#include "WAO_Clock.h"
// #include "e_clock.h"

// Get system time in nanoseconds, converted to an 64-bit int  (Replaced with SDL_GetTicksNS to ensure multiplatform compatibility)
// This function is known to work for Windows, Linux, and Android. Not tested on other platforms. Kept for any usefulness.
// long long int Clock_nanoTime() {
//     struct timespec ts;
//     clock_gettime(1, &ts);
//     return (long long int)ts.tv_sec * NANO_SEC + ts.tv_nsec;
// }

// Create a new Clock instance
WAO_Clock* WAO_CreateClock() {
    WAO_Clock* clock = SDL_malloc(sizeof(WAO_Clock));
    // if (!e_Clock_create(clock)) return NULL;

    WAO_InitClock(clock);
    
    SDL_Log("Clock created.");
    return clock;
}

// Destroy a Clock instance
void WAO_DestroyClock (WAO_Clock** clockPtr) {
    // if (!e_Clock_destroy(clockPtr)) return;

    SDL_free(*clockPtr);
    *clockPtr = NULL;
    SDL_Log("Clock destroyed.");
}

// Initialize the Clock
void WAO_InitClock (WAO_Clock* clock) {
    // if (!e_Clock_init(clock)) return;
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

    clock->secTarget = clock->currentCycleTime + NANO_SEC;

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

    clock->timerCount = 0;

    clock->timers = SDL_malloc(sizeof(WAO_Timer) * DEFAULT_TIMER_MALLOC);

    // for () {
    //     clock->timers->startTime = 0;
    //     clock->timers->endTime = 0;
    //     clock->timers->remainingTime = 0;
    //     clock->timers->remainingTime_Seconds = 0;
    // }
}

// Update the Clock
void WAO_UpdateClock (WAO_Clock* clock) {
    // if (!e_Clock_update(clock)) return;
    WAO_CycleUpdate(clock);
    
    clock->currentCycleTime = SDL_GetTicksNS();

    clock->cycleDelta = (clock->currentCycleTime - clock->lastCycleTime) / (double)NANO_SEC;
    clock->tickDelta += (clock->currentCycleTime - clock->lastCycleTime) / clock->tickTime;
    clock->lastCycleTime = clock->currentCycleTime;

    clock->cps++;

    // Frame Loop
    while (clock->currentCycleTime >= clock->frameTarget) {
        WAO_FrameUpdate(clock);

        clock->frameDelta = (clock->currentCycleTime - clock->lastFrameTime) / (double)NANO_SEC;
        clock->lastFrameTime = clock->currentCycleTime;

        clock->frameTarget = clock->currentCycleTime + clock->frameTime;

        clock->fps++;

        // Tick Loop
        while (clock->tickDelta >= 1) {

            // Limits the amount of time that ticks can make-up for, to avoid rapid fast forward.
            if (clock->tickDelta > TICK_CATCHUP_LIMIT) {
                clock->tickDelta = TICK_CATCHUP_LIMIT;
            }
            
            WAO_TickUpdate(clock);

            clock->tickDelta--;

            clock->tps++;
        }
    }

    // 1 Sec Loop
    if (clock->currentCycleTime >= clock->secTarget) {

        // Limits the amount of time that sec clock can make-up for, to avoid rapid fast forward.
        if (clock->currentCycleTime > clock->secTarget + SEC_CATCHUP_LIMIT) {
            for (long long int i = clock->secTarget + SEC_CATCHUP_LIMIT; i < clock->currentCycleTime; i++) {
                clock->secTarget += NANO_SEC;
            }
        }

        WAO_SecUpdate(clock);
        
        clock->secTarget = clock->secTarget + NANO_SEC;

        clock->getCPS = clock->cps;
        clock->getFPS = clock->fps;
        clock->getTPS = clock->tps;

        clock->cps = 0;
        clock->fps = 0;
        clock->tps = 0;


    }
}

// Update functions (Updated within the Clock_update function. Not recommended to use anywhere)
static void WAO_CycleUpdate (WAO_Clock* clock) {
    for (int i = 0; i < clock->cycleUpdateCount; i++) {
        // if (!e_Clock_cycleUpdate(clock, i)) continue;
        clock->cycleUpdateFunctions[i]();
    }
}
static void WAO_FrameUpdate (WAO_Clock* clock) {
    for (int i = 0; i < clock->frameUpdateCount; i++) {
        // if (!e_Clock_frameUpdate(clock, i)) continue;
        clock->frameUpdateFunctions[i]();
    }
}
static void WAO_TickUpdate (WAO_Clock* clock) {
    for (int i = 0; i < clock->tickUpdateCount; i++) {
        // if (!e_Clock_tickUpdate(clock, i)) continue;
        clock->tickUpdateFunctions[i]();
    }
}
static void WAO_SecUpdate (WAO_Clock* clock) {
    for (int i = 0; i < clock->secUpdateCount; i++) {
        // if (!e_Clock_secUpdate(clock, i)) continue;
        clock->secUpdateFunctions[i]();
    }
}

// Add functions
bool WAO_AddCycleFunction (WAO_Clock* clock, void (*function)()) {
    // if (!e_Clock_addCycleFunction(clock, function)) return false;
    clock->cycleUpdateFunctions[clock->cycleUpdateCount] = function;
    clock->cycleUpdateCount++;
    return true;
}
bool WAO_AddFrameFunction (WAO_Clock* clock, void (*function)()) {
    // if (!e_Clock_addCycleFunction(clock, function)) return false;
    clock->frameUpdateFunctions[clock->frameUpdateCount] = function;
    clock->frameUpdateCount++;
    return true;
}
bool WAO_AddTickFunction (WAO_Clock* clock, void (*function)()) {
    // if (!e_Clock_addTickFunction(clock, function)) return false;
    clock->tickUpdateFunctions[clock->tickUpdateCount] = function;
    clock->tickUpdateCount++;
    return true;
}
bool WAO_AddSecFunction (WAO_Clock* clock, void (*function)()) {
    // if (!e_Clock_addSecFunction(clock, function)) return false;
    clock->secUpdateFunctions[clock->secUpdateCount] = function;
    clock->secUpdateCount++;
    return true;
}

// void Clock_createTimer (WBE_Clock* clock) {
//     if (clock->timerCount % DEFAULT_TIMER_MALLOC == 0) {
        
//     }
// }

long long int WAO_GetCPS (WAO_Clock* clock) { return clock->cps; }
int WAO_GetFPS (WAO_Clock* clock) { return clock->fps; }
int WAO_GetTPS (WAO_Clock* clock) { return clock->tps; }
double WAO_GetDT (WAO_Clock* clock) { return clock->frameDelta; }

// Add Clock_pause, which pauses all clocks, or maybe add a parameter that takes in an enum, that has entries for each clock type (to pause frame, tick, sec, or all, individually)
// Add Clock_unpause, which brings the clocks up-to-date, then resumes them