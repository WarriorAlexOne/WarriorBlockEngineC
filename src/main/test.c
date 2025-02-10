#include "../../include/util/common.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "../../include/util/clock.h"
#include "../../include/util/global_variables.h"
#include "../../include/util/string_tools.h"
#include "../../include/util/tools.h"
#include "../../include/util/vector_2D.h"
#include "../../include/util/vector_3D.h"
#include "../../include/input/inputs.h"
#include "../../include/input/key_input.h"
#include "../../include/main/cleanup.h"
// #include "../../include/main/rendering.h"
// #include "../../include/main/window.h"
// #include "../../include/entity/"
// #include "../../include/error/"
// #include "../../include/gui/"
#include "../../include/main/test.h"


bool start = true;
Clock* mainClock;


void test_main () {
    SDL_Init(SDL_INIT_VIDEO);

    mainClock = Clock_create();

    Clock_addCycleFunction(mainClock, test_cycleUpdate);
    Clock_addFrameFunction(mainClock, test_frameUpdate);
    Clock_addTickFunction(mainClock, test_tickUpdate);
    Clock_addSecFunction(mainClock, test_secUpdate);

    while (start) {
        Clock_update(mainClock);
    }

    Clock_destroy(&mainClock);
    Clock_destroy(&mainClock);
    SDL_Quit();
    SDL_Log("Shutdown Successful!");
}


void test_cycleUpdate () {

}

void test_frameUpdate () {

}

void test_tickUpdate () {

}

void test_secUpdate () {
    SDL_Log("%lli", mainClock->getCPS);
}