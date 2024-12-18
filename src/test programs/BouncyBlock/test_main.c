#include "../../util/common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../util/global_variables.h"
#include "../../util/clocks.h"
#include "../../util/tools.h"
#include "../../util/drawing_tools.h"
#include "../../main/window.h"
#include "../../main/rendering.h"  //Figure out how to check which window is focused on, to accurately take a screenshot of the correct window
#include "../../input/inputs.h"
#include "../../input/key_input.h"


byte win0 = 0;


void drawBackground ();
void testRender ();


void testMain () {
    initClocks();
    updateClocks();
    initDebugTools();
    initWindows();

    createWindow(0, "WarriorBlock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800);
    toggleWindow(0, true);

    initRenderers();
    
    addRenderFunction(0, testRender);

    initInputs();
    initKeyInput();

    //Main Loop
    while (!quit) {
        updateClocks();
        // printf("%i", window_list_initialized);
    }
}

void testRender () {
    setColor(win0, 0, 0, 0, 255);
    drawRect(win0, 500, 500, 250, 50);
}
