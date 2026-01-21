#include <WBE/WBE.h>


int main (int argc, char *argv[]) {
    WBE_Init();

    WBE_Window window = WBE_CreateWindow("Am I Looping?", 1300, 900);
    WBE_Window window2 = WBE_CreateWindow("Am I Pooping?", 1300, 900);

    WBE_Keys key = {0};

    // Initialize Input
    // WBE_InitInput();

    bool running = true;
    while (running) {
        WBE_UpdateKeys(&key);

        if (WBE_IsKeyPressed(&key, SDL_SCANCODE_W)) {
            SDL_Log("W IS PRESS!");
        }
    }

    WBE_Cleanup();
    return 0;
}
