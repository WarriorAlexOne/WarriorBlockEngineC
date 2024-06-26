#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"


const double MILLI_SEC = 1000.0;
double tickRate = 60.0;
double tickTime = 0.0;
double tickDelta = 0.0;           //Used for the tick clock. Do not use with game events.
double deltaTime = 0.0;           //Used for game events to keep values consistent with time.
long long int currentTime = 0;
long long int lastTime = 0;

long long int targetTime = 0;

int fps = 0;
int tps = 0;
string strFPS[16];
string titleFPS[48];

void (*frameUpdateFunctions[1024]) ();
short frameUpdateFunctionCount = 0;

void (*tickUpdateFunctions[1024]) ();
short tickUpdateFunctionCount = 0;

void (*pauseFrameUpdateFunctions[1024]) ();
short pauseFrameUpdateFunctionCount = 0;


void initClock ();
void updateClocks ();
void tickUpdate ();
void frameUpdate ();
void pauseFrameUpdate ();
void addTickFunction (void (*function) ());
void addFrameFunction (void (*function) ());
void addPauseFrameFunction (void (*function) ());
void fpsToString ();
void titleFPSString ();


void initClock () {
    tickTime = MILLI_SEC/tickRate;
    targetTime = SDL_GetTicks64() + MILLI_SEC;
    strcpy(titleFPS, title);
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
    }

    //Sec Update
    if (currentTime >= targetTime) {
        targetTime = currentTime + MILLI_SEC;
        fpsToString();
        titleFPSString();
        fps = 0;
        tps = 0;
    }

    frameUpdate();
}


void tickUpdate () {
    for (int i = 0; i < tickUpdateFunctionCount; i++) {
        tickUpdateFunctions[i]();
    }
}
void frameUpdate () {
    for (int i = 0; i < frameUpdateFunctionCount; i++) {
        frameUpdateFunctions[i]();
    }
}
void pauseFrameUpdate () {
    for (int i = 0; i < pauseFrameUpdateFunctionCount; i++) {
        pauseFrameUpdateFunctions[i]();
    }
}


void addTickFunction (void (*function) ()) {
    tickUpdateFunctions[tickUpdateFunctionCount] = function;
    tickUpdateFunctionCount++;
}
void addFrameFunction (void (*function) ()) {
    frameUpdateFunctions[frameUpdateFunctionCount] = function;
    frameUpdateFunctionCount++;
}
void addPauseFrameFunction (void (*function) ()) {
    pauseFrameUpdateFunctions[pauseFrameUpdateFunctionCount] = function;
    pauseFrameUpdateFunctionCount++;
}


void fpsToString () {
    if (fps < 100000000 && fps > 0) {
        sprintf(strFPS, "%s%i", "FPS: ", fps);
    }
}
void titleFPSString () {
    if (fps < 100000000 && fps > 0) {
        sprintf(titleFPS, "%s%s%i", title, "   FPS: ", fps);
    }
}

#endif