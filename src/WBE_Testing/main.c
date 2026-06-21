#include <WBE/WBE.h>
#include "WBE/Util/WBE_List.h"


WBE_Instance wbe;
WBE_Clock* clock;
WBE_Window* window;
WBE_Window* window1;
WBE_Window* window2;
WBE_Window* window3;
WBE_Window* window4;
SDL_FRect player = {64, 64, 64, 64};

float rotato = 0.0f;

typedef struct {
    int int1;
    char char2;
    float float3;
    double double4;
} WBE_Test;



int main () {
    WBE_Init();

    WBE_Test* test = WBE_CreateList(sizeof(WBE_Test));

    for (int i = 0; i < 65; i++) {
        
        WBE_ListAdd(test) = (WBE_Test){i*i, i, i*1.5, i*1.128};


        // test[WBE_GetLastIndex(test)] = (WBE_Test){i*i, i, i*1.5, i*1.128};
        SDL_Log(
            "Struct Values: int %d char %d float %f double %lf",
            test[WBE_GetLastIndex(test)].int1,
            test[WBE_GetLastIndex(test)].char2,
            test[WBE_GetLastIndex(test)].float3,
            test[WBE_GetLastIndex(test)].double4
        );
    }


    // Game Setup
    wbe = WBE_CreateNewInstance();
    window = WBE_CreateWindow(&wbe, WBE_NAME " " WBE_VERSION, 800, 600);
    // window1 = WBE_CreateWindow(&wbe, "1", 800, 600);
    // window2 = WBE_CreateWindow(&wbe, "2", 800, 600);
    clock = WBE_CreateClock(&wbe, 60, 60);

    SDL_Texture* gradientTexture = WBE_CreateGradient(window->sdl_renderer, 0, 255, 20, 20, 140, 140, 20, 20);

    SDL_Texture* playerTexture = IMG_LoadTexture(window->sdl_renderer, "assets/textures/players/slome.png");
    SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_PIXELART);

    float playerX = 0;
    float playerY = 0;

    float rotX = 0;
    float rotY = 0;

    while (WBE_Update(&wbe)) {
        rotato += 0.01;

        // Player Movement
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_W)) {
            playerX += SDL_sin(rotX)*2;
            playerY -= SDL_cos(rotX)*2;
        }
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_A)) rotX -= 0.025;
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_S)) player.y += 400 * WBE_GetDT(clock);
        if (WBE_IsKeyDown(&wbe, WBE_SCANCODE_D)) rotX += 0.025;
        
        if (WBE_IsKeyPressed(&wbe, WBE_SCANCODE_RETURN)) {
            if (WBE_CheckForKeyString(&wbe, "UpUpDownDownLeftRightLeftRightBAReturn", 11)) {
                SDL_Log("Cheat found!");
            }
        }


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

        SDL_RenderTextureRotated(
            window->sdl_renderer,
            playerTexture,
            &(SDL_FRect){0, 0, 16, 16},
            &(SDL_FRect){playerX, playerY, 16*4, 16*4},
            rotX*55,
            &(SDL_FPoint){16*2, 16*2},
            SDL_FLIP_NONE
        );

        SDL_RenderPresent(window->sdl_renderer);
    }

    WBE_Cleanup();
    return 0;
}
