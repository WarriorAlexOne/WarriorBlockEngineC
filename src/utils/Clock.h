#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void initClockValues ();
void updateClocks ();
void tickUpdate ();
void frameUpdate ();
void addTickFunction (void (*function)());
void addFrameFunction (void (*function)());
// void fpsToString ();
// void titleFPSString ();


const short milliSec = 1000;
float tickRate = 60;
double tickTime = 0;
double delta = 0;
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


void initClockValues () {
    tickTime = milliSec/tickRate;
    targetTime = SDL_GetTicks64() + milliSec;
    printf("Clocks Initialized!\n");
}

void updateClocks () {
    currentTime = SDL_GetTicks64();
    fps++;

    delta += (currentTime - lastTime) / tickTime;

    lastTime = currentTime;

    while (delta >= 1) {
        tps++;
        delta--;
        tickUpdate();
    }

    if (currentTime >= targetTime) {
        targetTime = currentTime + milliSec;
        // fpsToString();
        // titleFPSString();
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


void addTickFunction (void (*function)()) {
    tickUpdateFunctions[tickUpdateFunctionCount] = function;
    tickUpdateFunctionCount++;
}
void addFrameFunction (void (*function)()) {
    frameUpdateFunctions[frameUpdateFunctionCount] = function;
    frameUpdateFunctionCount++;
}


// void fpsToString () {
//     if (fps < 100000000 && fps > 0) {
//         sprintf(strFPS, "%s%i", "FPS: ", fps);
//     }
// }
// void titleFPSString () {
//     if (fps < 100000000 && fps > 0) {
//         sprintf(titleFPS, "%s%s%i", title, "   FPS: ", fps);
//     }
// }

#endif