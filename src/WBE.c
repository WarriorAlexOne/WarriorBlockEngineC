#include <WBE/WBE.h>
#include "WBE/WBE_Names.h"

bool WBE_Init () {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("%s Failed to load SDL!\n", WBE_NAME_Init);
        SDL_GetError();
        return -1;
    }
    if (!TTF_Init()) {
        SDL_Log("%s Failed to load SDL_ttf!\n", WBE_NAME_Init);
        SDL_GetError();
        return -1;
    }

    // Give external application info
    SDL_SetAppMetadata(WBE_NAME, WBE_VERSION, WBE_APPID);

    // Print SDL Version
    SDL_Log(
        "%s SDL Version: %d.%d.%d\n",
        WBE_NAME_Init,
        SDL_VERSIONNUM_MAJOR(SDL_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_VERSION)
    );

    // Print SDL_image Version
    SDL_Log(
        "%s SDL_image Version: %d.%d.%d\n",
        WBE_NAME_Init,
        SDL_VERSIONNUM_MAJOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_IMAGE_VERSION)
    );

    // Print SDL_ttf Version
    SDL_Log(
        "%s SDL_ttf Version: %d.%d.%d\n",
        WBE_NAME_Init,
        SDL_VERSIONNUM_MAJOR(SDL_TTF_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_TTF_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_TTF_VERSION)
    );

    // Print WarriorBlockEngine Version
    SDL_Log("%s %s Version: %s\n", WBE_NAME_Init, WBE_NAME, WBE_VERSION);
    
    // Print Startup Confirmation
    SDL_Log("%s %s Startup Successful!\n", WBE_NAME_Init, WBE_NAME);
    return true;
}
