#include "WBE/WBE_Names.h"
#include "WBE/Debug/WBE_Debug.h"
#include "SDL3/SDL.h"


void Debug_WBE_CheckForKeyString (char* string1, char* string2) {
    if (GetDebugState_WBE_Keyboard()) SDL_Log("Looking for: %s  Found: %s", string1, string2);
}
