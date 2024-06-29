#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

#include <stdio.h>
#include <stdbool.h>

#include "../utils/clock.h"


bool debug = false;    //Toggles debug mode, which pauses the program upon exit to more easily review the console logs.
bool tickOnce = true;  //Set to false after running some code in an if statement.


void initDebugTools ();
void updateDebugTools ();


void initDebugTools () {
    if (debug) {
        addFrameFunction(updateDebugTools);
        printf("Debugging Tools Initialized!\n");
    }
}

void updateDebugTools () {
    
}

#endif