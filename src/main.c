#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Utils/WAO_String.h"
#include "Utils/WAO_Math.h"

int main (int argc, char **argv) {

    printf("Am I Looping? %lli\n", WAO_Fibonacci(6));
    return 0;
}
