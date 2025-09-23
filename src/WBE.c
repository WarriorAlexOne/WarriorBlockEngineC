#include <WBE/WBE.h>
#include "WBE/Util/WBE_List.h"
#include "WBE/Input/WBE_Key.h"
#include "WBE/WBE_Window.h"

WBE_KeyChecker* keyChecker;
WBE_Window waowindow;

int x = 0;
int y = 0;
int winX = 0;
int winY = 0;

int onGround = false;

void temp () {
    // if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_W)) {
    //     y -= 20;
    //     SDL_Log("W IS PRESSED!");
    // }
    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_A)) {
        winX = -20;
        // SDL_Log("A IS PRESSED!");
    }
    // if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_S)) {
    //     y += 20;
    //     SDL_Log("S IS PRESSED!");
    // }
    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_D)) {
        winX = 20;
        // SDL_Log("D IS PRESSED!");
    }
    if (!WBE_IsKeyDown(keyChecker, SDL_SCANCODE_A) && !WBE_IsKeyDown(keyChecker, SDL_SCANCODE_D)) {
        winX = 0;
    }

    char winIcon[1024];
    static int i;
    i++;
    SDL_snprintf(winIcon, 1024, "assets/textures/misc/%i.png", i);
    WBE_SetWindowIcon(&waowindow, winIcon);
    if (i >= 9) {
        i = 0;
    }

    if (WBE_IsKeyDown(keyChecker, SDL_SCANCODE_SPACE) && onGround) {
        winY -= 65;
    }
    
    winY += 5;
    if (winY > 55) {
        winY = 55;
    }
    if (waowindow.pos.y + waowindow.size.y > waowindow.displaySize.y - 80) {
        waowindow.pos.y = waowindow.displaySize.y - waowindow.size.y - 1 - 80;
        onGround = true;
    }
    if (waowindow.pos.y + waowindow.size.y < waowindow.displaySize.y-1-80) {
        onGround = false;
    }
    // if (waowindow.pos.x + waowindow.size.x > waowindow.displaySize.x) {
    //     winX = -5;
    // }
    // if (waowindow.pos.y + waowindow.size.y > waowindow.displaySize.y) {
    //     winY = -5;
    // }
    // if (waowindow.pos.x < 0) {
    //     winX = 5;
    // }
    // if (waowindow.pos.y < 0) {
    //     winY = 5;
    // }
    WBE_SetWindowVelocity(&waowindow, winX, winY);
    WBE_UpdateWindows(&waowindow);
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
    WBE_AddFrameFunction(&gameClock, temp);
    // WBE_SetFrameLimit(&gameClock, 1);

    // SDL_Window* window;
    // SDL_Renderer* renderer;
    // SDL_CreateWindowAndRenderer("Am I Looping?", 1000, 600, SDL_WINDOW_RESIZABLE, &window, &renderer);

    waowindow = WBE_CreateWindow("Am I Looping?", 1000, 600);
    // WBE_Window waowindow2 = WBE_CreateWindow("Test", 300, 300);
    // WBE_SetWindowIcon(&waowindow, "assets/textures/misc/slome_cursor.png");

    // WBE_SetWindowVelocity(&waowindow, 5, 5);

    keyChecker = WBE_CreateKeyChecker();
    SDL_Event event;

    SDL_Texture* texture = IMG_LoadTexture(waowindow.sdl_renderer, "assets/textures/tiles/stone.png");

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

        SDL_SetRenderDrawColor(waowindow.sdl_renderer, 25, 51, 153, 255);
        SDL_RenderClear(waowindow.sdl_renderer);

        SDL_SetRenderDrawColor(waowindow.sdl_renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(waowindow.sdl_renderer, &(SDL_FRect){x, y, 16, 16});

        SDL_RenderPresent(waowindow.sdl_renderer);
    }

    WBE_Cleanup();
    return 0;
}
