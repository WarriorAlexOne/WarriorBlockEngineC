#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"


bool isNum (char c);
bool isAlpha (char c);


bool isNum (char c) {
    return c >= '0' && c <= '9';
}

bool isAlpha (char c) {
    return c >='A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

#endif