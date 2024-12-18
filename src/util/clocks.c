#include "../../include/util/common.h"

#include <SDL2/SDL.h>

#include "../../include/util/global_variables.h"
#include "../../include/util/clocks.h"


long long int currentTime;   // The clock that makes the program run. THIS SHOULD NEVER BE CHANGED!
long long int lastCycleTime;   // Used to calculate the cycleDelta & tickDelta, to check how much time has passed/was lost.
double cycleDelta;   // Used to get the time between 'cycles'. Useful for making values run consistently during any slowdown or speedup.
int cps = 0;   // Cycles per second. (Not Child Protective Services :P)

double frameRate = DEFAULT_FRAMERATE;
double frameTime = NANO_SEC/DEFAULT_FRAMERATE;   // Frame Rate converted to a second-fraction.
double frameTarget;   // Constantly updates to the next time 'til it runs a frame.
long long int lastFrameTime;   // Used to calculate the frameDelta, to check how much time has passed/was lost between frames.
double frameDelta;   // Used to get the time between frames. Useful for making values run consistently with a varying framerate.
int fps = 0;   // Frames per second.

double tickRate = DEFAULT_TICKRATE;
double tickTime = NANO_SEC/DEFAULT_TICKRATE;   // Tick Rate converted to a second-fraction.
double tickTarget;   // Constantly updates to the next time 'til it runs a tick.
double tickDelta;   // Different from other delta times. Keeps track of current tick progression, and whether ticks were lost or not.
int tps = 0;   // Ticks per second.

double secTime;   // Updates every time a second passes, to know when the next second should pass.

// Function arrays used for updating specified functions at different points.
void (*instantUpdateFunctions[1024]) ();
void (*frameUpdateFunctions[1024]) ();
void (*tickUpdateFunctions[1024]) ();
void (*secUpdateFunctions[1024]) ();
void (*pauseFrameUpdateFunctions[1024]) ();
void (*pauseTickUpdateFunctions[1024]) ();

// Keeps track of how many functions each array contains during runtime. Used to loop through each populated element in the array.
// int instantUpdateCount = 0;
int frameUpdateCount = 0;
int tickUpdateCount = 0;
int secUpdateCount = 0;
int pauseFrameUpdateCount = 0;
int pauseTickUpdateCount = 0;


long long int getNanoTime() {
    struct timespec ts;
    clock_gettime(1, &ts);
    return (long long int)ts.tv_sec * 1e9 + ts.tv_nsec;
}

void initClocks () {
    currentTime = getNanoTime();
    lastCycleTime = currentTime;
    lastFrameTime = currentTime;
    frameTarget = currentTime + frameTime;
    tickTarget = currentTime + tickTime;
    // if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
    //     printf("Current refresh rate: %dHz\n", displayMode.refresh_rate);
    //     frameRate = displayMode.refresh_rate;
    // } else {
    //     printf("Could not get display mode: %s\n", SDL_GetError());
    // }
    SDL_Log("Clocks Initialized!\n");
}

void updateClocks () {
    cycleUpdate();
    currentTime = getNanoTime();

    cycleDelta = (currentTime - lastCycleTime) / NANO_SEC;
    tickDelta += (currentTime - lastCycleTime) / tickTime;
    lastCycleTime = currentTime;

    cps++;

    // 1 Sec Loop
    if (currentTime >= secTime) {
        secTime = currentTime + NANO_SEC;
        // SDL_Log("CPS: %i\n", cps);
        // SDL_Log("FPS: %i\n", fps);
        // SDL_Log("TPS: %i\n", tps);
        secUpdate();
        cps = 0;
        fps = 0;
        tps = 0;
    }

    // Frame Loop
    while (currentTime >= frameTarget) {
        frameUpdate();

        frameDelta = (currentTime - lastFrameTime) / NANO_SEC;
        lastFrameTime = currentTime;

        frameTarget = currentTime + frameTime;

        fps++;

        // Tick Loop
        while (tickDelta >= 1) {
            tickUpdate();

            tickDelta--;

            tps++;

            if (tickDelta > TICK_CATCHUP_LIMIT) tickDelta = TICK_CATCHUP_LIMIT;
        }
    }
}

// void cycleUpdate () {
//     for (int i = 0; i < instantUpdateCount; i++) {
//         instantUpdateFunctions[i]();
//     }
// }
void frameUpdate () {
    for (int i = 0; i < frameUpdateCount; i++) {
        frameUpdateFunctions[i]();
    }
}
void tickUpdate () {
    for (int i = 0; i < tickUpdateCount; i++) {
        tickUpdateFunctions[i]();
    }
}
void secUpdate () {
    for (int i = 0; i < secUpdateCount; i++) {
        secUpdateFunctions[i]();
    }
}
void pauseFrameUpdate () {
    for (int i = 0; i < pauseFrameUpdateCount; i++) {
        pauseFrameUpdateFunctions[i]();
    }
}
void pauseTickUpdate () {
    for (int i = 0; i < pauseTickUpdateCount; i++) {
        pauseTickUpdateFunctions[i]();
    }
}

void addCycleFunction (void (*function) ()) {
    static int instantUpdateCount;
    instantUpdateFunctions[instantUpdateCount] = function;
    instantUpdateCount++;
}
void addFrameFunction (void (*function) ()) {
    frameUpdateFunctions[frameUpdateCount] = function;
    frameUpdateCount++;
}
void addTickFunction (void (*function) ()) {
    tickUpdateFunctions[tickUpdateCount] = function;
    tickUpdateCount++;
}
void addSecFunction (void (*function) ()) {
    secUpdateFunctions[secUpdateCount] = function;
    secUpdateCount++;
}
void addPauseFrameFunction (void (*function) ()) {
    pauseFrameUpdateFunctions[pauseFrameUpdateCount] = function;
    pauseFrameUpdateCount++;
}
void addPauseTickFunction (void (*function) ()) {
    pauseTickUpdateFunctions[pauseTickUpdateCount] = function;
    pauseTickUpdateCount++;
}