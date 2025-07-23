#include <SDL3/SDL.h>
#include "WarriorBlockEngine.h"
#include "WBE_Startup.h"

void WBE_StartProgram () {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetAppMetadata(WBE_NAME, WBE_VERSION ,NULL);

    
}