#include "WBE_Clock.h"
// #include "e_clock.h"

WBE_Clock** clockTracker = NULL;
int clocksMade = 0;

static void WBE_CycleUpdate (WBE_Clock* clock);
static void WBE_FrameUpdate (WBE_Clock* clock);
static void WBE_TickUpdate (WBE_Clock* clock);
static void WBE_SecUpdate (WBE_Clock* clock);

// Get system time in nanoseconds, converted to a 64-bit int. (Replaced with SDL_GetTicksNS to ensure multiplatform compatibility).
// This function is known to work for Windows, Linux, and Android. Not tested on other platforms. Kept for any usefulness.
// long long int WBE_GetNanoTime() {
//     struct timespec ts;
//     clock_gettime(1, &ts);
//     return (long long int)ts.tv_sec * WBE_NANO_SEC + ts.tv_nsec;
// }

WBE_Clock* WBE_CreateClock() {
    WBE_Clock* clock = SDL_malloc(sizeof(WBE_Clock));
    // if (!e_Clock_create(clock)) return NULL;

    WBE_InitClock(clock);
    
    SDL_Log("Clock created.");
    return clock;
}

void WBE_DestroyClock (WBE_Clock** clockPtr) {
    // if (!e_Clock_destroy(clockPtr)) return;

    SDL_free(*clockPtr);
    *clockPtr = NULL;
    SDL_Log("Clock destroyed.");
}

void WBE_InitClock (WBE_Clock* clock) {
    // if (!e_Clock_init(clock)) return;
    clock->currentCycleTime = SDL_GetTicksNS();
    clock->lastCycleTime = clock->currentCycleTime;
    clock->cycleDelta = (clock->currentCycleTime - clock->lastCycleTime) / WBE_NANO_SEC;
    clock->cps = 0;
    clock->getCPS = 0;

    clock->frameRate = WBE_DEFAULT_FRAMERATE;
    clock->frameTime = WBE_NANO_SEC / clock->frameRate;
    clock->frameTarget = clock->currentCycleTime + clock->frameTime;
    clock->lastFrameTime = clock->currentCycleTime;
    clock->frameDelta = (clock->currentCycleTime - clock->lastFrameTime) / WBE_NANO_SEC;
    clock->fps = 0;
    clock->getFPS = 0;

    clock->tickRate = WBE_DEFAULT_TICKRATE;
    clock->tickTime = WBE_NANO_SEC / WBE_DEFAULT_TICKRATE;
    clock->tickTarget = clock->currentCycleTime + clock->tickTime;
    clock->tickDelta = 0;
    clock->tps = 0;
    clock->getTPS = 0;

    clock->secTarget = clock->currentCycleTime + WBE_NANO_SEC;

    for (int i = 0; i < WBE_CYCLE_FUNCTION_LIMIT; i++) {
        clock->cycleUpdateFunctions[i] = NULL;
    }
    for (int i = 0; i < WBE_FRAME_FUNCTION_LIMIT; i++) {
        clock->frameUpdateFunctions[i] = NULL;
    }
    for (int i = 0; i < WBE_TICK_FUNCTION_LIMIT; i++) {
        clock->tickUpdateFunctions[i] = NULL;
    }
    for (int i = 0; i < WBE_SEC_FUNCTION_LIMIT; i++) {
        clock->secUpdateFunctions[i] = NULL;
    }

    clock->cycleUpdateCount = 0;
    clock->frameUpdateCount = 0;
    clock->tickUpdateCount = 0;
    clock->secUpdateCount = 0;

    for (int i = 0; i < WBE_CYCLE_FUNCTION_LIMIT; i++) {
        clock->e_cycleUpdateErrorPositions[i] = false;
    }
    for (int i = 0; i < WBE_FRAME_FUNCTION_LIMIT; i++) {
        clock->e_frameUpdateErrorPositions[i] = false;
    }
    for (int i = 0; i < WBE_TICK_FUNCTION_LIMIT; i++) {
        clock->e_tickUpdateErrorPositions[i] = false;
    }
    for (int i = 0; i < WBE_SEC_FUNCTION_LIMIT; i++) {
        clock->e_secUpdateErrorPositions[i] = false;
    }

    clock->timerCount = 0;

    clock->timers = SDL_malloc(sizeof(WBE_Timer) * WBE_DEFAULT_TIMER_MALLOC);

    // for () {
    //     clock->timers->startTime = 0;
    //     clock->timers->endTime = 0;
    //     clock->timers->remainingTime = 0;
    //     clock->timers->remainingTime_Seconds = 0;
    // }
    if (clockTracker == NULL) {
        clockTracker = (WBE_Clock**)SDL_malloc(sizeof(WBE_Clock*) * WBE_CLOCK_CREATION_LIMIT);
    }
    clockTracker[clocksMade] = clock;
    clocksMade++;
}

void WBE_UpdateClock (WBE_Clock* clock) {
    // if (!e_Clock_update(clock)) return;
    WBE_CycleUpdate(clock);
    
    clock->currentCycleTime = SDL_GetTicksNS();

    clock->cycleDelta = (clock->currentCycleTime - clock->lastCycleTime) / (double)WBE_NANO_SEC;
    clock->tickDelta += (clock->currentCycleTime - clock->lastCycleTime) / clock->tickTime;
    clock->lastCycleTime = clock->currentCycleTime;

    clock->cps++;

    // Frame Loop
    while (clock->currentCycleTime >= clock->frameTarget) {
        WBE_FrameUpdate(clock);

        clock->frameDelta = (clock->currentCycleTime - clock->lastFrameTime) / (double)WBE_NANO_SEC;
        clock->lastFrameTime = clock->currentCycleTime;

        clock->frameTarget = clock->currentCycleTime + clock->frameTime;

        clock->fps++;

        // Tick Loop
        while (clock->tickDelta >= 1) {

            // Limits the amount of time that ticks can make-up for, to avoid rapid fast forward.
            if (clock->tickDelta > WBE_TICK_CATCHUP_LIMIT) {
                clock->tickDelta = WBE_TICK_CATCHUP_LIMIT;
            }
            
            WBE_TickUpdate(clock);

            clock->tickDelta--;

            clock->tps++;
        }
    }

    // 1 Sec Loop
    if (clock->currentCycleTime >= clock->secTarget) {

        // Limits the amount of time that sec clock can make-up for, to avoid rapid fast forward.
        if (clock->currentCycleTime > clock->secTarget + WBE_SEC_CATCHUP_LIMIT) {
            for (long long int i = clock->secTarget + WBE_SEC_CATCHUP_LIMIT; i < clock->currentCycleTime; i++) {
                clock->secTarget += WBE_NANO_SEC;
            }
        }

        WBE_SecUpdate(clock);
        
        clock->secTarget = clock->secTarget + WBE_NANO_SEC;

        clock->getCPS = clock->cps;
        clock->getFPS = clock->fps;
        clock->getTPS = clock->tps;

        clock->cps = 0;
        clock->fps = 0;
        clock->tps = 0;


    }
}

static void WBE_CycleUpdate (WBE_Clock* clock) {
    for (int i = 0; i < clock->cycleUpdateCount; i++) {
        // if (!e_Clock_cycleUpdate(clock, i)) continue;
        clock->cycleUpdateFunctions[i]();
    }
}
static void WBE_FrameUpdate (WBE_Clock* clock) {
    for (int i = 0; i < clock->frameUpdateCount; i++) {
        // if (!e_Clock_frameUpdate(clock, i)) continue;
        clock->frameUpdateFunctions[i]();
    }
}
static void WBE_TickUpdate (WBE_Clock* clock) {
    for (int i = 0; i < clock->tickUpdateCount; i++) {
        // if (!e_Clock_tickUpdate(clock, i)) continue;
        clock->tickUpdateFunctions[i]();
    }
}
static void WBE_SecUpdate (WBE_Clock* clock) {
    for (int i = 0; i < clock->secUpdateCount; i++) {
        // if (!e_Clock_secUpdate(clock, i)) continue;
        clock->secUpdateFunctions[i]();
    }
}

// Add functions
bool WBE_AddCycleFunction (WBE_Clock* clock, void (*function)()) {
    // if (!e_Clock_addCycleFunction(clock, function)) return false;
    clock->cycleUpdateFunctions[clock->cycleUpdateCount] = function;
    clock->cycleUpdateCount++;
    return true;
}
bool WBE_AddFrameFunction (WBE_Clock* clock, void (*function)()) {
    // if (!e_Clock_addCycleFunction(clock, function)) return false;
    clock->frameUpdateFunctions[clock->frameUpdateCount] = function;
    clock->frameUpdateCount++;
    return true;
}
bool WBE_AddTickFunction (WBE_Clock* clock, void (*function)()) {
    // if (!e_Clock_addTickFunction(clock, function)) return false;
    clock->tickUpdateFunctions[clock->tickUpdateCount] = function;
    clock->tickUpdateCount++;
    return true;
}
bool WBE_AddSecFunction (WBE_Clock* clock, void (*function)()) {
    // if (!e_Clock_addSecFunction(clock, function)) return false;
    clock->secUpdateFunctions[clock->secUpdateCount] = function;
    clock->secUpdateCount++;
    return true;
}

// void Clock_createTimer (WBE_Clock* clock) {
//     if (clock->timerCount % WBE_DEFAULT_TIMER_MALLOC == 0) {
        
//     }
// }

long long int WBE_GetCPS (WBE_Clock* clock) { return clock->cps; }
int WBE_GetFPS (WBE_Clock* clock) { return clock->fps; }
int WBE_GetTPS (WBE_Clock* clock) { return clock->tps; }
double WBE_GetDT (WBE_Clock* clock) { return clock->frameDelta; }

// Add Clock_pause, which pauses all clocks, or maybe add a parameter that takes in an enum, that has entries for each clock type (to pause frame, tick, sec, or all, individually)
// Add Clock_unpause, which brings the clocks up-to-date, then resumes them