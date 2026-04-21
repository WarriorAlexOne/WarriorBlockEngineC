#include <WBE/WBE.h>


WBE_Instance wbe;
WBE_Clock* clock;
WBE_Window* window;
WBE_Window* window1;
WBE_Window* window2;
WBE_Window* window3;
SDL_FRect player = {64, 64, 64, 64};

float rotato = 0.0f;


int main () {
    WBE_Init();

    // Game Setup
    wbe = WBE_CreateNewInstance();
    window = WBE_CreateWindow(&wbe, WBE_NAME " " WBE_VERSION, 800, 600);
    window1 = WBE_CreateWindow(&wbe, "1", 800, 600);
    window2 = WBE_CreateWindow(&wbe, "2", 800, 600);
    window3 = WBE_CreateWindow(&wbe, "3", 800, 600);
    clock = WBE_CreateClock(&wbe, 60, 60);

    SDL_Texture* gradientTexture = WBE_CreateGradient(window->sdl_renderer, 0, 255, 20, 40, 140, 140, 20, 20);


    while (WBE_Update(&wbe)) {
        rotato += 0.01;

        // Smooth Player Movement
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_W)) player.y -= 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_A)) player.x -= 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_S)) player.y += 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_D)) player.x += 400 * WBE_GetDT(clock);

        // Render
        SDL_SetRenderDrawColor(window->sdl_renderer, 25, 51, 153, 255);
        SDL_RenderClear(window->sdl_renderer);

        int screenWid = 2560;
        int screenHei = 1440;
        int gradwid = 3000;
        int gradhei = 3000;
        SDL_RenderTextureRotated(
            window->sdl_renderer,
            gradientTexture,
            &(SDL_FRect){0, 0, gradientTexture->w, gradientTexture->h},
            &(SDL_FRect){(screenWid/2)-(gradwid/2), (screenHei/2)-(gradhei/2), gradwid, gradhei},
            rotato*12,
            &(SDL_FPoint){gradwid/2, gradhei/2},
            SDL_FLIP_NONE
        );

        SDL_SetRenderDrawColor(window->sdl_renderer, 217, 177, 107, 255);
        SDL_RenderFillRect(window->sdl_renderer, &player);

        SDL_RenderPresent(window->sdl_renderer);
    }

    WBE_Cleanup();
    return 0;
}
