#include <SDL3/SDL.h>
#include "WBE_Clock.h"
#include "WBE_Cleanup.h"

void WBE_Cleanup () {
    WBE_CleanupClocks();
    SDL_Quit();
}