#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define byte char
#define string char

string title[32] = "WarriorBlockEngine 0.0";
string iconPath[64] = "assets/textures/misc/WarriorBlockEngine Logo v1.png";

#include "../utils/StringTools.h"
#include "../utils/Clock.h"
#include "../entity/Player.h"


bool debug = false;

int quit = 0;
bool bordered = true;

int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);  //Other initializations need to be OR'd in.
    IMG_Init(IMG_INIT_PNG);
    initClockValues();

    
    SDL_Window* window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1700,
        900,
        SDL_WINDOW_SHOWN
        | SDL_WINDOW_RESIZABLE
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 2);

    SDL_Surface* windowIcon = IMG_Load(iconPath);
    if (windowIcon == NULL) {
        printf("SDL_image Error: %s\nUnable To Load Window Icon.", IMG_GetError());
        SDL_FreeSurface(windowIcon);
    }
    else {
        SDL_SetWindowIcon(window, windowIcon);
        SDL_FreeSurface(windowIcon);
    }
    


    //Main Loop
    while (!quit) {
        updateClocks();
        SDL_RenderPresent(renderer);
        
        SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);  //Pretty Navy Blue.
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 191, 0, 0, 255);
        SDL_Rect testRect = {100, 100, 100, 100};
        SDL_RenderFillRect(renderer, &testRect);


        // Tick Loop
        if (tickPassed) {

        }

        //Sec Loop
        if (startupSecPassed) {
            SDL_SetWindowTitle(window, titleFPS);
        }


        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
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
