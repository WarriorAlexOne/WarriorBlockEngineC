#include <SDL3/SDL.h>
#include "WAO_Splash.h"
#include "Error/EWAO_Splash.h"

#define WAO_MAX_SPLASH_LIST_LENGTH 512
#define WAO_MAX_SPLASH_STRING_LENGTH 256

char** WAO_CreateSplashList (int listLength, int maxStringLength) {
    char tempArray = (char**)SDL_malloc(sizeof(char*) * listLength);
    // for (int x = 0; x < WAO_SPLASH_LIST_LENGTH; x++) {
    //     for (int y = 0; y < WAO_SPLASH_STRING_LENGTH; y++) {
            
    //     }
    // }
}
// "Am I Looping?",   // ------------- 0
// "Powered By Milk & Tacos!"   // --- 1

// char* WAO_GetSplash () {
//     SDL_srand(Wao_GetNanoTime());
//     switch (SDL_rand(2)) {
//         default:
//             return splashList[0];
//             break;
//         case 1:
//             return splashList[1];
//             break;
//     }
// }

char* WAO_GetSpecificSplash (int splashID) {
    // if 
}

//Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in