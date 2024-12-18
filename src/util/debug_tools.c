#include "../../include/util/debug_tools.h"


bool debug = false;  //Toggles debug mode, which pauses the program upon exit to more easily review the console logs.
bool tickOnce = false;  //Set to true after running some code in an if statement.


void initDebugTools () {
    if (debug) {
        SDL_Log("Debugging Tools Initialized!\n");
    }
}