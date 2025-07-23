#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Utils/WBE_String.h"
#include "Utils/WBE_Math.h"
#include "WBE_Clock.h"
#include "Tests/Test_WBE_Math.h"

int main (int argc, char **argv) {
    WBE_TestMathFunctions();

    printf("Am I Looping? %lli\n", WBE_Fibonacci(6));
    return 0;
}
