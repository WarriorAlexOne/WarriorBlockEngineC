#include <SDL3/SDL.h>
#include "WAO_Startup.h"
#include "WarriorBlockEngine.h"

void WAO_StartProgram () {
    SDL_SetAppMetadata(WAO_NAME, WAO_VERSION ,NULL);
}