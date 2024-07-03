#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/globalVariables.h"
#include "../utils/FastNoiseLite/FastNoiseLite.h"
#include "../utils/tools.h"
#include "../utils/vector2D.h"
#include "../utils/vector3D.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/mouseInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../entity/camera.h"
#include "../map/tiles.h"
#include "../map/levelGen.h"
#include "../map/mining.h"
#include "../entity/player.h"
#include "../main/rendering.h"


int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    initClock();
    initDebugTools();
    initInputs();
    initMainWindow();
    initKeyInput();
    initMouseInput();
    initControllerInput();
    initTiles();
    initLevelGen();
    createLevel0();
    initBlockManipulation();
    initPlayers();
    initRenderer();
    printf("Initialization Complete!\n\n");

    // FILE* fp = fopen("saves/testFile.txt", "w");

    // fprintf(fp, "Test");

    // fclose(fp);

    //Main Loop
    while (!quit) {

        while (gamePaused) {
            updateClocks();
        }

        updateClocks();
    }
    
    destroyTileTextures(tiles, numberOfTiles);
    if (controllers) {
        SDL_GameControllerClose(controllers[0].SDL_Controller);
    }
    free(players);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if (debug) { printf("DEBUG MODE\nGame Exit Successful\n"); system("pause"); }
    return 0;
}
