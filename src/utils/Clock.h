#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>

#include <SDL2/SDL.h>

#include "../utils/globalVariables.h"


const double MILLI_SEC = 1000.0;
double tickRate = 60.0;
double tickTime = 0.0;
double tickDelta = 0.0;           //Used for the tick clock. Do not use with game events.
double deltaTime = 0.0;           //Used for game events to keep values consistent with time.
long long int currentTime = 0;
long long int lastTime = 0;

long long int targetTime = 0;


void (*frameUpdateFunctions[1024]) ();
short frameUpdateFunctionCount = 0;

void (*tickUpdateFunctions[1024]) ();
short tickUpdateFunctionCount = 0;

void (*secUpdateFunctions[1024]) ();
short secUpdateFunctionCount = 0;

void (*pauseFrameUpdateFunctions[1024]) ();
short pauseFrameUpdateFunctionCount = 0;


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


void initClock () {
    tickTime = MILLI_SEC/tickRate;
    targetTime = SDL_GetTicks64() + MILLI_SEC;
    printf("Clocks Initialized!\n");
}

void updateClocks () {
    while (gamePaused) {
        pauseFrameUpdate();
    }
    currentTime = SDL_GetTicks64();
    fps++;

    tickDelta += (currentTime - lastTime) / tickTime;
    deltaTime = (currentTime - lastTime) / MILLI_SEC;

    lastTime = currentTime;

    //Tick Update
    while (tickDelta >= 1) {
        tps++;
        tickDelta--;
        tickUpdate();
        // while (currentTime >= targetTime) {
        //     fps = 0;
        //     tps = 0;
        //     secUpdate();
        // }
    }

    //Sec Update
    if (currentTime >= targetTime) {
        targetTime = currentTime + MILLI_SEC;
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