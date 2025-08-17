#include <stdint.h>
#include <SDL3/SDL.h>
#include "Error/WBE_Error.h"

/*
Case     0       reserved for No Error.
Case     1-999   reserved for Setup Errors.
Case  1000-1999  reserved for Clock Errors.
Case  2000-2999  reserved for Keyboard Input Errors.
Case  3000-3999  reserved for Mouse Input Errors.
Case  4000-4999  reserved for Controller Input Errors.
Case  5000-5999  reserved for Window Errors.
Case  6000-6999  reserved for Renderer Errors.
Case  7000-7999  reserved for World Errors.
Case  8000-8999  reserved for Camera Errors.
Case  9000-9999  reserved for Splash Errors.
Case 10000-10999 reserved for Math Errors.
*/

// Default Errors:
const char Error_WBE_No_Error[] =           "No error found.";
const char Error_WBE_Unknown_Error[] =      "Error! The problem that triggered this error is unknown.\n";
// Clock Errors:
const char Error_WBE_CreateClock_Prefix[] = "Error in WBE_CreateClock: ";
const char Error_WBE_CreateClock_MSG1[] =   "There was an issue creating the clock!\n";
// Math Errors:
const char Error_WBE_ChangeBit_Prefix[] =   "Error in WBE_ChangeBit: ";
const char Error_WBE_ChangeBit_MSG1[] =     "bitPos is too low! Please use a higher value.\n";
const char Error_WBE_ChangeBit_MSG2[] =     "bitPos is too high! Please use a value lower than 32.\n";
const char Error_WBE_ChangeBit_MSG3[] =     "on_or_off is too low! Please use 1 or 0.\n";
const char Error_WBE_ChangeBit_MSG4[] =     "on_or_off is too high! Please use 1 or 0.\n";

void WBE_GetError (int errorCode) {
    switch (errorCode) {
        default:
            SDL_Log(Error_WBE_Unknown_Error);
            break;
        case 0:
            SDL_Log(Error_WBE_No_Error);
            break;
        case WBE_CreateClock_ERROR_1:
            SDL_Log("%s%s", Error_WBE_CreateClock_Prefix, Error_WBE_CreateClock_MSG1);
            break;
        // case 7000:
        //     SDL_Log("%sCamera argument is NULL or corrupted!\n", Error_WBE_CreateWorld_Prefix);
        //     SDL_Log("Attempting to fix camera...\n");
        //     break;
        // case 7001:
        //     SDL_Log("%sCould not fix camera!\n", Error_WBE_CreateWorld_Prefix);
        //     break;
        case WBE_ChangeBit_ERROR_1:   // Impossible, but will be kept for any future changes.
            SDL_Log("%s%s", Error_WBE_ChangeBit_Prefix, Error_WBE_ChangeBit_MSG1);
            break;
        case WBE_ChangeBit_ERROR_2:
            SDL_Log("%s%s", Error_WBE_ChangeBit_Prefix, Error_WBE_ChangeBit_MSG2);
            break;
        case WBE_ChangeBit_ERROR_3:   // Impossible, but will be kept for any future changes.
            SDL_Log("%s%s", Error_WBE_ChangeBit_Prefix, Error_WBE_ChangeBit_MSG3);
            break;
        case WBE_ChangeBit_ERROR_4:
            SDL_Log("%s%s", Error_WBE_ChangeBit_Prefix, Error_WBE_ChangeBit_MSG4);
            break;
    }
}
