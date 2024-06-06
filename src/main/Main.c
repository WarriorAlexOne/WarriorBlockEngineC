#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "../utils/Clock.h"

#define byte char

bool debug = false;

int quit = 0;
bool bordered = true;

int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow(
        "WarriorBlockEngineC 0.0",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1700,
        900,
        SDL_WINDOW_SHOWN
        | SDL_WINDOW_RESIZABLE
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 2);

    //Main Loop
    while (!quit) {
        SDL_RenderPresent(renderer);
        
        SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 191, 0, 0, 255);
        SDL_Rect testRect = {100, 100, 100, 100};
        SDL_RenderFillRect(renderer, &testRect);


        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                bordered = !bordered;
                SDL_SetWindowBordered(window, bordered);
                bordered ? printf("Bordered\n") : printf("Borderless\n");
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if (debug) {
        printf("DEBUG MODE\nGame Exit Successful\n");
        system("pause");
    }
    return 0;
}