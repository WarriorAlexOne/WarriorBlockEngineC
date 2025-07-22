#include <SDL3/SDL.h>
#include "Error/Wao_Error.h"

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

// World Errors:
const char Error_WAO_CreateWorld[] = "Error in WAO_CreateWorld: ";
// Splash Errors:
// const char Error_WAO_;
// Math Errors:
const char Error_WAO_WAO_ChangeBit[] = "Error in WAO_ChangeBit: ";

void WAO_GetError (int errorCode) {
    switch (errorCode) {
        default:
            SDL_Log("Error! The problem that triggered this error is unknown. \n");
            break;
        case 0:
            SDL_Log("No error found.");
            break;
        case 7000:
            SDL_Log("%sCamera argument is NULL or corrupted!\n", Error_WAO_CreateWorld);
            SDL_Log("Attempting to fix camera...\n");
            break;
        case 7001:
            SDL_Log("%sCould not fix camera!\n", Error_WAO_CreateWorld);
            break;
        case 9000:
            break;
        case 10000:
            SDL_Log("%sChosen bit position is too low! Please use a higher value.\n", Error_WAO_WAO_ChangeBit);
            break;
        case 10001:
            SDL_Log("%sChosen bit position is too high! Please use a lower value.\n", Error_WAO_WAO_ChangeBit);
            break;
    }
}