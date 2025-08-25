#include <SDL3/SDL.h>
#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Cleanup.h"

void WBE_Cleanup () {
    // WBE_CleanupClocks();
    SDL_Quit();
}