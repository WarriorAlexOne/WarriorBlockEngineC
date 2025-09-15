#include "WBE/WBE_Startup.h"
#include "WBE/WBE_Names.h"

void WBE_Init () {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("%s Failed to load SDL!\n", NAME_WBE_Init);
    }
    SDL_SetAppMetadata(WBE_NAME, WBE_VERSION ,NULL);

    // Print SDL Version
    SDL_Log(
        "%s SDL Version: %d.%d.%d\n",
        NAME_WBE_Init,
        SDL_VERSIONNUM_MAJOR(SDL_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_VERSION)
    );

    // Print SDL_image Version
    SDL_Log(
        "%s SDL_image Version: %d.%d.%d\n",
        NAME_WBE_Init,
        SDL_VERSIONNUM_MAJOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_IMAGE_VERSION)
    );

    // Print WarriorBlockEngine Version
    SDL_Log("%s %s %s\n", NAME_WBE_Init, WBE_NAME, WBE_VERSION);

    

    SDL_Log("%s %s Startup Successful!\n", NAME_WBE_Init, WBE_NAME);
}
