#ifndef WBE_CLOCK_H
#define WBE_CLOCK_H

#include <SDL3/SDL.h>

void WBETest_InitClock ();
int WBETest_Clock (SDL_Event* event);
void WBETest_AddFunc (void (*function)());
void WBETest_QuitWindow ();

#endif