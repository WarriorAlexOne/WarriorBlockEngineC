#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "WarriorBlockEngine.h"
#include "WBE_Startup.h"

void WBE_Startup () {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetAppMetadata(WBE_NAME, WBE_VERSION ,NULL);

    SDL_Log(
        "SDL Version: %d.%d.%d\n",
        SDL_VERSIONNUM_MAJOR(SDL_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_VERSION)
    );
    SDL_Log(
        "SDL_image Version: %d.%d.%d\n",
        SDL_VERSIONNUM_MAJOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_IMAGE_VERSION)
    );

    

    SDL_Log("%s Startup Successful!\n", WBE_NAME);
}
