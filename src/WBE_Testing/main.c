#include <WBE/WBE.h>
#include "WBE/Paint/WBE_Gradient.h"

SDL_Event event;

WBE_Clock* clock;
WBE_Window window;
WBE_Keys keys;

WBE_Instance wbe;

SDL_FRect player = {64, 64, 64, 64};

float rotato = 0.0f;


int main () {
    WBE_Init();

    wbe = WBE_CreateNewInstance();
    window = WBE_CreateWindow("blockengine", 800, 600);

    clock = WBE_CreateClock(&wbe, 60, 60);

    SDL_Texture* gradientTexture = WBE_CreateGradient(window.sdl_renderer, 0, 0, 255, 255, 0, 0);

    bool running = true;
    while (running) {
        rotato += 0.01;
        WBE_Update(&wbe);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        WBE_UpdateKeys(&keys);

        if (WBE_IsKeyDown(&keys, SDL_SCANCODE_W)) player.y -= 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&keys, SDL_SCANCODE_A)) player.x -= 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&keys, SDL_SCANCODE_S)) player.y += 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&keys, SDL_SCANCODE_D)) player.x += 400 * WBE_GetDT(clock);

        
        SDL_SetRenderDrawColor(window.sdl_renderer, 25, 51, 153, 255);
        SDL_SetRenderDrawColor(window.sdl_renderer, 0, 0, 0, 255);
        SDL_RenderClear(window.sdl_renderer);

        // SDL_SetRenderDrawColor(window.sdl_renderer, 217, 177, 107, 255);
        // SDL_RenderFillRect(window.sdl_renderer, &player);

        // RenderGradient(window.sdl_renderer, 20, 184, 152, 221, 144, 36);
        // RenderGradient(window.sdl_renderer, 42, 21, 214, 59, 71, 46);
        // RenderGradient(window.sdl_renderer, 0, 0, 255, 255, 0, 0);

        SDL_RenderTextureRotated(
            window.sdl_renderer,
            gradientTexture,
            &(SDL_FRect){0, 0, gradientTexture->w, gradientTexture->h},
            &(SDL_FRect){500-SDL_sin(rotato)*100, 100, gradientTexture->w+(SDL_sin(rotato)*200), gradientTexture->h+500},
            rotato*50,
            &(SDL_FPoint){(gradientTexture->w/2)+(SDL_sin(rotato)*100), (gradientTexture->h/2)+250},
            SDL_FLIP_NONE
        );

        SDL_RenderPresent(window.sdl_renderer);
    }

    WBE_Cleanup();
    return 0;
}
