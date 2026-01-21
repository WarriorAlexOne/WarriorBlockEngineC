#include "WBE/Input/WBE_Input.h"
#include <SDL3/SDL.h>


SDL_Event WBE_Event = {0};


void WBE_UpdateInput (WBE_Keys* keys) {
    while (SDL_PollEvent(&WBE_Event)) {
        // if (WBE_Event.type == SDL_EVENT_QUIT) {
        //     for (int i = 0; i < WBE_GetWindowCount(); i++) {
        //         if (windowTracker[0] == NULL) {

        //         }
        //     }
        // }
    }
    WBE_UpdateKeys(keys);
}
