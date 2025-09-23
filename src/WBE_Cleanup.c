#include <SDL3/SDL.h>
#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Window.h"
#include "WBE/WBE_Names.h"
#include "WBE/WBE_Cleanup.h"

void WBE_Cleanup () {
    SDL_Log("%s Cleaning up before exit...", NAME_WBE_Cleanup);
    // WBE_CleanupClocks();
    WBE_CleanupWindows();
    SDL_Quit();
    SDL_Log("%s Cleanup complete!", NAME_WBE_Cleanup);
}