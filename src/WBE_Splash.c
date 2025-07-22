#include <SDL3/SDL.h>
#include "WBE_Splash.h"
#include "Error/Error_WBE_Splash.h"

// char** WBE_CreateSplashList (int listLength, int maxStringLength) {
//     // if (Error_WBE_CreateSplashList(listLength, maxStringLength)) {

//     // }
//     char** tempArray = (char**)SDL_malloc(sizeof(char*) * listLength);
//     if (tempArray == NULL) {
//         SDL_Log(
//             "Error in WBE_CreateSplashList: %s", 
//                 "Couldn't allocate memory to list array! Setting array to NULL.\n"
//         );
//         return NULL;
//     }

//     for (int x = 0; x < maxStringLength; x++) {
//         tempArray[x] = (char*)SDL_malloc(sizeof(char) * maxStringLength);
//         if (tempArray[x] == NULL) {
//             SDL_Log(
//             "Error in WBE_CreateSplashList: %s%i%s%s", 
//                 "Couldn't allocate memory to string [",x,"] in list array! ",
//                 "Setting array to NULL.\n"
//             );
//             return NULL;
//         }
//     }

//     return NULL;
// }
// "Am I Looping?",   // ------------- 0
// "Powered By Milk & Tacos!"   // --- 1

// char* WBE_GetSplash () {
//     SDL_srand(WBE_GetNanoTime());
//     switch (SDL_rand(2)) {
//         default:
//             return splashList[0];
//             break;
//         case 1:
//             return splashList[1];
//             break;
//     }
// }

// char* WAO_GetSpecificSplash (int splashID) {
//     // if 
//     return NULL;
// }

//Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor
//incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam quis nostrud
//exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute
//irure dolor in Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
//eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam
//quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
//Duis aute irure dolor in.