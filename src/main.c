#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Utils/WBE_String.h"
#include "Utils/WBE_Math.h"
#include "WBE_Clock.h"

int main (int argc, char **argv) {
    // WBE_Clock* testClock = WBE_CreateClock();
    // WBE_CycleUpdate(testClock);


    printf("Am I Looping? %lli\n", WBE_Fibonacci(6));
    return 0;
}
