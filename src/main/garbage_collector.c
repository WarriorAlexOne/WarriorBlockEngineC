#include "../../include/util/common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../include/main/window.h"
#include "../../include/main/garbage_collector.h"


void cleanup_on_exit () {
    cleanupWindows();
    IMG_Quit();
    SDL_Quit();
    SDL_Log("Everything Closed Successfully!");
}
