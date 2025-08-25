#include <WBE/WBE.h>
#include "WBE/Utils/WBE_List.h"
#include "WBE/Wao_Key.h"

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

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("Am I Looping?", 1500, 800, SDL_WINDOW_RESIZABLE, &window, &renderer);

    Wao_KeyCheck* keyChecker = Wao_CreateKeyChecker();
    SDL_Event event;

    SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/textures/tiles/stone.png");

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    bool running = true;
    while (running) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            Wao_UpdateKeyCheck(keyChecker, event);
            if (Wao_IsKeyPressed(keyChecker, SDL_SCANCODE_ESCAPE)) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);
        SDL_RenderClear(renderer);



        SDL_RenderPresent(renderer);
    }

    // WBE_Cleanup();
    return 0;
}
