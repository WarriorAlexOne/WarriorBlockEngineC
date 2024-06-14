#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "../entity/Player.h"


void initClockValues ();
void updateClocks ();
void fpsToString ();
void titleFPSString ();


const short milli = 1000;
float tickRate;
double tickTime;
double delta;
long long int currentTime;
long long int lastTime;

long long int targetTime;

bool tickPassed = false;
bool startupSecPassed = false;

int fps = 0;
string strFPS[16];
string titleFPS[48];


void initClockValues () {
    tickRate = 60;
    tickTime = milli/tickRate;
    targetTime = SDL_GetTicks64() + 1000;
}

void updateClocks () {
    currentTime = SDL_GetTicks64();
    fps++;
    tickPassed = false;
    startupSecPassed = false;

    delta += (currentTime - lastTime) / tickTime;

    lastTime = currentTime;

    if (delta >= 1) {
        tickPassed = true;
        delta--;
    }

    if (currentTime >= targetTime) {
        targetTime = currentTime + 1000;
        startupSecPassed = true;
        fpsToString();
        titleFPSString();
        fps = 0;
    }

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