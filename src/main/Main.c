#include "../../include/util/common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../include/util/global_variables.h"  //DONE
#include "../../include/util/FastNoiseLite/FastNoiseLite.h"   // Third Party Noise Library
#include "../../include/util/clocks.h"  //DONE
#include "../../include/util/tools.h"
#include "../../include/util/vector_2D.h"
#include "../../include/util/vector_3D.h"
#include "../../include/util/string_tools.h"
#include "../../include/main/window.h"  //DONE
#include "../../include/main/rendering.h"  //DONE   // Figure out how to check which window is focused on, to accurately take a screenshot of the correct window
#include "../../include/util/drawing_tools.h"
#include "../../include/input/inputs.h"  //DONE
#include "../../include/input/key_input.h"  //DONE
// #include "../input/mouseInput.h"
// #include "../input/controllerInput.h"
// #include "../input/touchInput.h"
// #include "../entity/globalActions.h"
// #include "../entity/camera.h"
// #include "../map/tiles.h"
// #include "../entity/items.h"
// #include "../map/proceduralChunkGenerator.h"
// #include "../map/staticPositionLevelReader.h"
// #include "../entity/player.h"
// #include "../map/tileManipulation.h"
// #include "../map/staticPositionLevelRenderer.h"
// #include "../gui/text.h"
// #include "../gui/textDisplay.h"
// #include "../main/rendering.h"
#include "../../include/main/garbage_collector.h"
// #include "../test programs/BouncyBlock/test_main.c"
#include "../../include/util/debug_tools.h"  //DONE


// Make screen flip function
// Make screen pixelation function with an argument for the pixelation percentage(or some arbitrary value ig)
// Make screen tinting function with arguments for RGBA


int main (int argc, char* args[]) {
    SDL_Init(
        SDL_INIT_TIMER
        | SDL_INIT_AUDIO
        | SDL_INIT_VIDEO
        | SDL_INIT_EVENTS
    );
    IMG_Init(IMG_INIT_PNG);

    printf("Fib: %i", fib(10));

    cleanup_on_exit();
    if (true) {
        SDL_Log("DEBUG MODE\nGame Exit Successful\n");
        system("pause");
    }
    return 0;
}