#include <SDL3/SDL.h>
#include "WAO_Splash.h"
#include "Error/WAO_Error.h"
#include "Error/Error_WAO_Splash.h"

int errorTracker = 0;

bool Error_WAO_CreateSplashList (int listLength, int maxStringLength) {
    if (listLength < 1) {
        WAO_GetError(9000);
    }
    if (listLength > WAO_MAX_SPLASH_LIST_LENGTH) {

    }
}