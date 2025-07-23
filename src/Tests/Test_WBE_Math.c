#include <SDL3/SDL.h>
#include "Utils/WBE_Math.h"
#include "Tests/Test_WBE_Math.h"

void WBE_TestMathFunctions () {
    // ------------------------------------------------------------- //
    SDL_Log("\nTesting WBE_Fibonacci...\n");
    SDL_Log("\nTest 1:\n");

    SDL_Log("Returned Value: %lli\n", WBE_Fibonacci(100));


    SDL_Log("\nTest 2:\n");

    SDL_Log("Returned Value: %lli\n", WBE_Fibonacci(-100));
    SDL_Log("\nEnd of WBE_Fibonacci Tests.\n\n");
    // ------------------------------------------------------------- //


    // ------------------------------------------------------------- //
    SDL_Log("\nTesting WBE_ChangeBit...\n");
    SDL_Log("\nTest 1:\n");

    SDL_Log("Returned Value: %i\n", WBE_ChangeBit(0b1000, 1000, 1));
    

    SDL_Log("\nTest 2:\n");

    SDL_Log("Returned Value: %i\n", WBE_ChangeBit(0b1000, -1000, 1));


    SDL_Log("\nTest 3:\n");

    SDL_Log("Returned Value: %i\n", WBE_ChangeBit(0b1000, 0, 1000));


    SDL_Log("\nTest 4:\n");

    SDL_Log("Returned Value: %i\n", WBE_ChangeBit(0b1000, 0, -1000));
    SDL_Log("\nEnd of WBE_ChangeBit Tests.\n\n");
    // ------------------------------------------------------------- //


    // ------------------------------------------------------------- //
    // SDL_Log("\nTesting WBE_...\n");
    // SDL_Log("\nTest 1:\n");


    // SDL_Log("\nEnd of WBE_ Tests.\n\n");
    // ------------------------------------------------------------- //
}
