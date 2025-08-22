#include <SDL3/SDL.h>
#include "WBE/WBE_Splash.h"
#include "WBE/Error/WBE_Error.h"
#include "WBE/Error/Error_WBE_Splash.h"

int errorTracker = 0;

// bool Error_WBE_CreateSplashList (int listLength, int maxStringLength) {
//     if (listLength < 1) {
//         WBE_GetError(9000);
//     }
//     if (listLength > WBE_MAX_SPLASH_LIST_LENGTH) {

//     }
//     return false;
// }