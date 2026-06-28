#ifndef WBE_CLOCK_H
#define WBE_CLOCK_H

#include <SDL3/SDL.h>
#include "WBE/WBE_Instance_Types.h"

#ifndef WBE_NS
#define WBE_NS 1000000000.0
#endif

#ifndef WBE_DEFAULT_FRAMERATE
#define WBE_DEFAULT_FRAMERATE 60
#endif

#ifndef WBE_DEFAULT_TICKRATE
#define WBE_DEFAULT_TICKRATE 60
#endif

#ifndef WBE_TICKFUNCTION_LIMIT
#define WBE_TICKFUNCTION_LIMIT 1024
#endif


typedef struct {
   long long currentTime;

    int frameRate;
    long long frameLength;
    long long currentFrameTime;
    long long lastFrameTime;
    long long scheduledFrameTime;
    long long delayTime;

    float deltaTime;

    int tickCounter;

    void (*tickFunctions[WBE_TICKFUNCTION_LIMIT])();
    int tickFunctionCount;

    long long secDelayTime;
    int fps;
} WBE_Clock;


WBE_Clock* WBE_CreateClock(WBE_Instance* instance, int frameRate, int tickRate);
void WBE_CleanupClocks (WBE_Instance* instance);

void WBE_UpdateClock (WBE_Clock* clock);
bool WBE_AddTickFunction (WBE_Clock* clock, void (*function)());

int WBE_GetFrameRate (WBE_Clock* clock);
void WBE_SetFrameRate (WBE_Clock* clock, int frameRate);

int WBE_GetFPS (WBE_Clock* clock);
double WBE_GetDT (WBE_Clock* clock);

#endif