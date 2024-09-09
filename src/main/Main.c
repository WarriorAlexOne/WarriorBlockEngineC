#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
// #include <glut.h>  <-OpenGL C Library. Look into using sometime later.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
#include "../entity/items.h"
#include "../map/proceduralChunkGenerator.h"
#include "../map/staticPositionLevelReader.h"
#include "../entity/player.h"
#include "../map/tileManipulation.h"
#include "../map/staticPositionLevelRenderer.h"
#include "../gui/text.h"
#include "../main/rendering.h"


// FILE* fp = fopen("saves/testFile.txt", "w");
// fprintf(fp, "Test");
// fclose(fp);


int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    initClock();
    // initDebugTools();
    createWindow(
        "WarriorBlockEngine v0.0",
        "assets/textures/misc/WarriorBlockEngine Logo v1.png",
        500,
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
    initItems();
    initLevelGen();
    createLevel0();
    readLevel(1);
    readBGLevel(1);
    initPlayers();
    initBlockManipulation();
    initText();
    initRenderUpdater();
    printf("Initialization Complete!\n\n");


    createText(VERSION_NUMBER, L"WarriorBlockEngine", (Vec2_Int){0,2}, (Vec2_Int){16,16});
    delayedText(VERSION_NUMBER, 0.02);

    // createText(L"Lorem ipsum odor amet, consectetuer adipiscing elit.\nTempor hac potenti lorem; tristique elementum urna.\nNec tempor habitant bibendum varius phasellus quisque\ntellus parturient. Euismod conubia senectus praesent\ndolor eu ridiculus facilisi. In hac rutrum risus;\ncubilia bibendum lacus. Ex facilisi integer adipiscing\nsollicitudin tortor odio augue curabitur. Gravida\nconsequat ante luctus integer penatibus netus. Ligula\ndictum vestibulum id auctor maecenas sodales lacinia\nblandit. Parturient nunc ridiculus ipsum mollis\nscelerisque suspendisse.", (Vec2_Int){32,32}, (Vec2_Int){32,32}, 1, TEST_UI_TEXT);
    // delayedText(TEST_UI_TEXT);

    bool quickTest;
    //Main Loop
    while (!windows[0].quit) {

        // if (players[0].pressed.devKey && !quickTest) {
        //     delayedText(VERSION_NUMBER, 10);
        //     quickTest = true;
        // }
        while (gamePaused) {
            updateClocks();
        }

        updateClocks();
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(currentFont);
    destroyTileTextures(tiles, numberOfTiles);
    destroyItemTextures (items, numberOfItems);
    // if (controllers) {
    //     SDL_GameControllerClose(controllers[0].SDL_Controller);
    // }
    free(players);
    SDL_DestroyRenderer(windows->renderer);
    SDL_DestroyWindow(windows->window);
    IMG_Quit();
    SDL_Quit();
    free(windows);
    if (debug) { printf("DEBUG MODE\nGame Exit Successful\n"); system("pause"); }
    return 0;
}
