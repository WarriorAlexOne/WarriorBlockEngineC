#include "WBE/WBE_Testing/WBETest_Clock.h"

#define WBE_NANO_SEC 1000000000.0

void (*functions[128])() = {NULL};
int functionCount = 0;

bool quit = false;

int TARGET_FPS = 60;
int FRAME_NS;

int next_frame_time;

void WBETest_InitClock () {
    FRAME_NS = WBE_NANO_SEC / TARGET_FPS;
}

int WBETest_Clock (SDL_Event* event) {
     while (SDL_PollEvent(event)) {
        if (event->type == SDL_EVENT_QUIT) {
            quit = true;
        } else if (event->type == SDL_EVENT_KEY_DOWN) {
            if (event->key.key == SDLK_ESCAPE) {
                quit = true;
            }
        }
    }
    SDL_Log("Loop");

    // Run stored functions
    for (int i = 0; i < functionCount; i++) functions[i]();

        

    // Delay last
    SDL_DelayPrecise(16666665);

    if (quit) return 0;
    return 1;
}

void WBETest_AddFunc (void (*function)()) {
    functions[functionCount++] = function;
}

void WBETest_QuitWindow () {
    quit = true;
}
