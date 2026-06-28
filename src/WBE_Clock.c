#include "WBE/Error/Error_WBE_Clock.h"
#include "WBE/Error/WBE_Error.h"
#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Names.h"


static void WBE_TickUpdate (WBE_Clock* clock);

WBE_Clock* WBE_CreateClock (WBE_Instance* instance, int frameRate, int tickRate) {
    // Add proper error correction code
    if (!instance->isInitialized) {
        WBE_Clock* failedClock = NULL;
        SDL_Log("%s Failed to create Clock!", WBE_NAME_CreateClock);
        return failedClock;
    }
    WBE_Clock* newClock = SDL_malloc(sizeof(WBE_Clock));

    newClock->currentTime = SDL_GetTicksNS();

    newClock->frameRate = frameRate;
    newClock->frameLength = WBE_NS/newClock->frameRate;
    newClock->currentFrameTime = newClock->currentTime;
    newClock->lastFrameTime = newClock->currentTime;
    newClock->scheduledFrameTime = newClock->currentTime+newClock->frameLength;
    newClock->delayTime = newClock->scheduledFrameTime;
    newClock->deltaTime = 0.0f;
        
    newClock->tickCounter = 0;

    for (int i = 0; i < WBE_TICKFUNCTION_LIMIT; i++) {
        newClock->tickFunctions[i] = NULL;
    }
    newClock->tickFunctionCount = 0;

    newClock->secDelayTime = newClock->currentTime+WBE_NS;
    newClock->fps = 0;

    instance->clocks[instance->clockCount++] = newClock;
    instance->doesClockExist = true;

    SDL_Log("%s Clock created!", WBE_NAME_CreateClock);
    return newClock;
}

void WBE_UpdateClock (WBE_Clock* clock) {
    clock->deltaTime = (clock->currentFrameTime - clock->lastFrameTime) / WBE_NS;
    clock->lastFrameTime = clock->currentFrameTime;  // Used for DeltaTime

    // Tracks frames & ticks per second
    clock->fps++;

    // Keeps track of how many ticks should be ran
    clock->tickCounter++;

    // Get current time to compare to the next target time
    clock->currentFrameTime = SDL_GetTicksNS();
    // If a frame lags longer than 1 frame, advance by 1 frame of time until a frame is within range
    while (clock->currentFrameTime >= clock->scheduledFrameTime) {
        clock->scheduledFrameTime += clock->frameLength;
        clock->tickCounter++;
    }

    // Get the difference between the next scheduled frame, and the time that was used up prior
    clock->delayTime = clock->scheduledFrameTime-clock->currentFrameTime;
    // Delay program until next scheduled frame
    SDL_DelayPrecise(clock->delayTime);

    // Update the frame schedule for the next frame
    clock->scheduledFrameTime += clock->frameLength;

    // Run ticks
    while (clock->tickCounter > 0) {
        WBE_TickUpdate(clock);
        clock->tickCounter--;
    }


    // Sec clock to keep track of fps
    clock->currentTime = SDL_GetTicksNS();
    if (clock->currentTime >= clock->secDelayTime) {
        clock->secDelayTime += WBE_NS;
        // SDL_Log("FPS: %i", clock->fps);
        clock->fps = 0;
    }
}

static void WBE_TickUpdate (WBE_Clock* clock) {
    for (int i = 0; i < clock->tickFunctionCount; i++) {
        // if (!e_Clock_tickUpdate(clock, i)) continue;
        if (clock->tickFunctions[i] == NULL) continue;
        clock->tickFunctions[i]();
    }
}
bool WBE_AddTickFunction (WBE_Clock* clock, void (*function)()) {
    // if (!e_Clock_addTickFunction(clock, function)) return false;
    clock->tickFunctions[clock->tickFunctionCount++] = function;
    return true;
}

int WBE_GetFrameRate (WBE_Clock* clock) { return clock->frameRate; }
void WBE_SetFrameRate (WBE_Clock* clock, int frameRate) {
    clock->frameRate = frameRate;
    clock->frameLength = frameRate/WBE_NS;
}

int WBE_GetFPS (WBE_Clock* clock) { return clock->fps; }
double WBE_GetDT (WBE_Clock* clock) { return clock->deltaTime; }

// Add Clock_pause, which pauses all clocks, or maybe add a parameter that takes in an enum, that has entries for each clock type (to pause frame, tick, sec, or all, individually)
// Add Clock_unpause, which brings the clocks up-to-date, then resumes them