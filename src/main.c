#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "WBE_Startup.h"
#include "WBE_Clock.h"

#include "WBE_Cleanup.h"

int main (int argc, char *argv[]) {
    WBE_Startup();

    WBE_Clock* gameClock = WBE_CreateClock();

    bool running = true;
    while (running) {
        WBE_UpdateClock(gameClock);
    }

    WBE_Cleanup();
    return 0;
}
