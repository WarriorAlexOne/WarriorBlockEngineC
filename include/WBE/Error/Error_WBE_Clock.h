#ifndef ERROR_WBE_CLOCK_H
#define ERROR_WBE_CLOCK_H

#include <stdint.h>
#include "WBE/WBE_Defines.h"
#include "WBE/WBE_Clock.h"

bool Error_WBE_CreateClock(WBE_Clock* clock);
int32_t Error_WBE_DestroyClock (WBE_Clock** clockPtr);
int32_t Error_WBE_InitClock (WBE_Clock* clock);

int32_t Error_WBE_UpdateClock (WBE_Clock* clock);

int32_t Error_WBE_CycleUpdate (WBE_Clock* clock);
int32_t Error_WBE_FrameUpdate (WBE_Clock* clock);
int32_t Error_WBE_TickUpdate (WBE_Clock* clock);
int32_t Error_WBE_SecUpdate (WBE_Clock* clock);

int32_t Error_WBE_AddCycleFunction (WBE_Clock* clock, void (*function)());
int32_t Error_WBE_AddFrameFunction (WBE_Clock* clock, void (*function)());
int32_t Error_WBE_AddTickFunction (WBE_Clock* clock, void (*function)());
int32_t Error_WBE_AddSecFunction (WBE_Clock* clock, void (*function)());

int32_t Error_WBE_GetCPS (WBE_Clock* clock);
int32_t Error_WBE_GetFPS (WBE_Clock* clock);
int32_t Error_WBE_GetTPS (WBE_Clock* clock);
int32_t Error_WBE_GetDT (WBE_Clock* clock);

#endif