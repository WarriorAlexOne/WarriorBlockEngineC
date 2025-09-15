#include <WBE/WBE.h>
#include "WBE/Util/WBE_List.h"
#include "WBE/Input/WBE_Key.h"

WBE_KeyChecker* keyChecker;

int x = 0;
int y = 0;

void temp () {
    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_W)) {
        y -= 20;
        SDL_Log("W IS PRESSED!");
    }
    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_A)) {
        x -= 20;
        SDL_Log("A IS PRESSED!");
    }
    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_S)) {
        y += 20;
        SDL_Log("S IS PRESSED!");
    }
    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_D)) {
        x += 20;
        SDL_Log("D IS PRESSED!");
    }
}

int main (int argc, char *argv[]) {
    WBE_Init();

    int* test;
    test = CreateList(sizeof(int), 3);

    test[0] = 1;
    test[1] = 2;
    test[2] = 3;

    SDL_Log("%i", test[0]);
    SDL_Log("%i", test[1]);
    SDL_Log("%i", test[2]);

    WBE_Clock gameClock = WBE_CreateClock();
    WBE_AddTickFunction(&gameClock, temp);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("Am I Looping?", 1000, 600, SDL_WINDOW_RESIZABLE, &window, &renderer);

    keyChecker = WBE_CreateKeyChecker();
    SDL_Event event;

    SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/textures/tiles/stone.png");

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            WBE_UpdateKeyCheck(keyChecker, event);

            // if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_ESCAPE)) {
            //     running = false;
            // }

            // if (WBE_IsKeyReleased(keyChecker, SDL_SCANCODE_W)) {
            //     SDL_Log("W IS Released!------------");
            // }

            // if (WBE_IsKeyPressed(keyChecker, SDL_SCANCODE_D)) {
            //     SDL_Log("D IS PRESSED!");
            // }
            // if (WBE_IsKeyReleased(keyChecker, SDL_SCANCODE_D)) {
            //     SDL_Log("D IS Released!------------");
            // }
        }

        // if (WBE_IsKeyUp(keyChecker, SDL_SCANCODE_W)) {
        //     SDL_Log("W IS RELEASED!------------------");
        // }

        WBE_UpdateClock(&gameClock);

        SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &(SDL_FRect){x, y, 16, 16});

        SDL_RenderPresent(renderer);
    }

    // WBE_Cleanup();
    return 0;
}
