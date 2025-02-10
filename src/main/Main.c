#include "../../include/main/test.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


int main () {
    SDL_Log("SDL Version: %d.%d.%d\n",
        SDL_VERSIONNUM_MAJOR(SDL_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_VERSION));

    SDL_Log("SDL_image Version: %d.%d.%d\n",
        SDL_VERSIONNUM_MAJOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_IMAGE_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_IMAGE_VERSION));

    SDL_Log("WarriorBlockEngine v0.0.1 Rev. 7");

    test_main();
    return 0;
}
