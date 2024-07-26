#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
// #include <glut.h>  <-OpenGL C Library. Look into using sometime later.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/globalVariables.h"
#include "../utils/FastNoiseLite/FastNoiseLite.h"
#include "../utils/tools.h"
#include "../utils/vector2D.h"
#include "../utils/vector3D.h"
#include "../utils/clock.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/inputs.h"
#include "../input/keyInput.h"
#include "../input/mouseInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../entity/camera.h"
#include "../map/tiles.h"
#include "../map/proceduralChunkGenerator.h"
#include "../map/staticPositionLevelReader.h"
#include "../entity/player.h"
#include "../map/tileManipulation.h"
#include "../map/staticPositionLevelRenderer.h"
#include "../menu/text.h"
#include "../main/rendering.h"


// FILE* fp = fopen("saves/testFile.txt", "w");
// fprintf(fp, "Test");
// fclose(fp);


int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    initClock();
    // initDebugTools();
    createWindow(
        "WarriorBlockEngine v0.0",
        "assets/textures/misc/WarriorBlockEngine Logo v1.png",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1300,
        800
    );
    loadWindow(&windows[0]);
    initInputs();
    initKeyInput();
    initMouseInput();
    // initControllerInput();
    // initTouchInput();
    initCamera();
    initTiles();
    initLevelGen();
    createLevel0();
    readLevel(1);
    initPlayers();
    initBlockManipulation();
    initText();
    initRenderUpdater();
    printf("Initialization Complete!\n\n");


    //Main Loop
    while (!windows[0].quit) {

        while (gamePaused) {
            updateClocks();
        }

        updateClocks();
    }
    
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    destroyTileTextures(tiles, numberOfTiles);
    // if (controllers) {
    //     SDL_GameControllerClose(controllers[0].SDL_Controller);
    // }
    free(players);
    SDL_DestroyRenderer(windows->renderer);
    SDL_DestroyWindow(windows->window);
    SDL_Quit();
    free(windows);
    if (debug) { printf("DEBUG MODE\nGame Exit Successful\n"); system("pause"); }
    return 0;
}
