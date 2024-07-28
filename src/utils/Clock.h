#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "../utils/globalVariables.h"

#define CLOCK_MONOTONIC 1


const double NANO_SEC = 1000000000.0;
double tickRate = 60.0;
double tickDelay;
double tickDelta;           //Used for the tick clock. Do not use with game events.
double deltaTime;           //Used for game events to keep values consistent with time.
long long int currentTime;
long long int lastTime;

long long int secTime;

void (*frameUpdateFunctions[1024]) ();
void (*tickUpdateFunctions[1024]) ();
void (*secUpdateFunctions[1024]) ();
void (*pauseFrameUpdateFunctions[1024]) ();

short frameUpdateFunctionCount;
short tickUpdateFunctionCount;
short secUpdateFunctionCount;
short pauseFrameUpdateFunctionCount;

long long currentNanoTime();
void initClock ();
void updateClocks ();

void frameUpdate ();
void tickUpdate ();
void secUpdate ();
void pauseFrameUpdate ();

void addFrameFunction (void (*function) ());
void addTickFunction (void (*function) ());
void addSecFunction (void (*function) ());
void addPauseFrameFunction (void (*function) ());


long long currentNanoTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1e9 + ts.tv_nsec;
}

void initClock () {
    tickDelay = NANO_SEC/tickRate;
    secTime = currentNanoTime() + NANO_SEC;
    printf("Clocks Initialized!\n");
}

void updateClocks () {
    while (gamePaused) {
        pauseFrameUpdate();
    }
    currentTime = currentNanoTime();
    fps++;

    tickDelta += (currentTime - lastTime) / tickDelay;
    deltaTime = (currentTime - lastTime) / NANO_SEC;

    lastTime = currentTime;

    printf("NANOSECONDS: %lli\n", currentNanoTime());
    //Tick Update
    while (tickDelta >= 1) {
        tps++;
        tickDelta--;
        tickUpdate();
        // while (currentTime >= secTime) {
        //     fps = 0;
        //     tps = 0;
        //     secUpdate();
        // }
    }

    //Sec Update
    if (currentTime >= secTime) {
        secTime = currentTime + NANO_SEC;
        // fpsToString();
        // titleFPSString();
    }

    frameUpdate();
}


void frameUpdate () {
    for (int i = 0; i < frameUpdateFunctionCount; i++) {
        frameUpdateFunctions[i]();
    }
}
void tickUpdate () {
    for (int i = 0; i < tickUpdateFunctionCount; i++) {
        tickUpdateFunctions[i]();
    }
}
void secUpdate () {
    for (int i = 0; i < secUpdateFunctionCount; i++) {
        secUpdateFunctions[i]();
    }
}
void pauseFrameUpdate () {
    for (int i = 0; i < pauseFrameUpdateFunctionCount; i++) {
        pauseFrameUpdateFunctions[i]();
    }
}

void addFrameFunction (void (*function) ()) {
    frameUpdateFunctions[frameUpdateFunctionCount] = function;
    frameUpdateFunctionCount++;
}
void addTickFunction (void (*function) ()) {
    tickUpdateFunctions[tickUpdateFunctionCount] = function;
    tickUpdateFunctionCount++;
}
void addSecFunction (void (*function) ()) {
    secUpdateFunctions[secUpdateFunctionCount] = function;
    secUpdateFunctionCount++;
}
void addPauseFrameFunction (void (*function) ()) {
    pauseFrameUpdateFunctions[pauseFrameUpdateFunctionCount] = function;
    pauseFrameUpdateFunctionCount++;
}

#endif