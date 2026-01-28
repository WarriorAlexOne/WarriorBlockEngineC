#include <SDL3/SDL.h>
#include "WBE/Input/WBE_Key.h"
// #include "WBE/WBE_Clock.h"

#define WBE_NS 1000000000.0

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

bool running = true;

SDL_FRect player = {64, 64, 64, 64};
float speed = 60.0f;

// SDL_FRect box = { 50.0f, 200.0f, 60.0f, 60.0f };
// float speed_pixels_per_second = 220.0f; // how fast it moves

// void testFunc () {
//     if (event.type == SDL_EVENT_QUIT) {
//         WBE_QuitWindow();
//     }
// }

// void draw () {
//     // SDL_SetRenderVSync()

//     SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);
//     SDL_RenderClear(renderer);

//     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//     SDL_RenderRect(renderer, &box);

//     SDL_RenderPresent(renderer);
// }

int main () {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Log("Am I Looping?");

    SDL_CreateWindowAndRenderer("Test Window", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer);

    // // WBE_AddFunc(testFunc);
    // WBE_AddFunc(draw);

    // WBE_InitClock();

    // while (WBE_Clock(&event)) {
    //     SDL_Log("WHILE!!!");
    // }

    long long currentTime = SDL_GetTicksNS();

    int frameRate = 60;
    long long frameTarget = WBE_NS/frameRate;
    long long currentFrameTime = currentTime;
    long long lastFrameTime = currentTime;
    long long scheduledFrameTime = currentTime+frameTarget;
    long long delayTime = scheduledFrameTime;
    float deltaTime = 0.0f;

    int tickCounter = 0;

    long long secDelayTime = currentTime+WBE_NS;
    int fps = 0;

    WBE_Keys keys;

    while (running) {
    // ---------------- Clock ----------------

        // ---------------- Frames ----------------
        deltaTime = (currentFrameTime - lastFrameTime) / WBE_NS;
        lastFrameTime = currentFrameTime;  // Used for DeltaTime

        // Tracks frames & ticks per second
        fps++;

        // Keeps track of how many ticks should be ran
        tickCounter++;

        // Get current time to compare to the next target time
        currentFrameTime = SDL_GetTicksNS();
        // If a frame lags longer than 1 frame, advance by 1 frame of time until a frame is within range
        while (currentFrameTime >= scheduledFrameTime) {
            scheduledFrameTime += frameTarget;
            tickCounter++;
        }

        // Get the difference between the next scheduled frame, and the time that was used up prior
        delayTime = scheduledFrameTime-currentFrameTime;
        // Delay program until next scheduled frame
        SDL_DelayPrecise(delayTime);

        // Update the frame schedule for the next frame
        scheduledFrameTime += frameTarget;

        // Run ticks
        while (tickCounter > 0) {
            tickCounter--;
            // Add TickUpdate Functions Here
        }
        // ---------------- Frames ----------------


        // ---------------- Seconds ----------------
        // Sec clock to keep track of fps
        currentTime = SDL_GetTicksNS();
        if (currentTime >= secDelayTime) {
            secDelayTime += WBE_NS;
            SDL_Log("FPS: %i", fps);
            fps = 0;
        }
        // ---------------- Seconds ----------------
    // ---------------- Clock ----------------

        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) running = false;
        WBE_UpdateKeys(&keys);

        SDL_SetRenderDrawColor(renderer, 25, 51, 153, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 127, 127, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);

        if (WBE_IsKeyPressed(&keys, SDL_SCANCODE_W)) SDL_DelayPrecise(frameTarget*30);
        player.x += speed * deltaTime;
    }

    SDL_Quit();
    return 0;
}
