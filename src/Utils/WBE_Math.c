#include "Utils/WBE_Math.h"
#include "Error/WBE_Error.h"
#include "Error/Error_WBE_Math.h"
#include <SDL3/SDL.h>

long long WBE_Fibonacci (long long index) {
    int isNegative = 0;
    if (index == 0) return 0;
    if (index < 0) {
        index = -index;
        isNegative = 1;
    }
    long long temp = 0;
    long long a = 0;
    long long b = 1;

    while (index > 0) {
        temp = a + b;
        a = b;
        b = temp;
        index--;
    }
    if (isNegative) a = -a;
    return a;
}

int WBE_ChangeBit (int var, int bitPos, int on_or_off) {
    int errorCode = Error_WBE_ChangeBit(var, bitPos, on_or_off);
    if (errorCode) return var;

    int bitMask = 0;
    if (on_or_off == 1) {
        bitMask = 1 << bitPos;
        var |= bitMask;
    }
    else if (on_or_off == 0) {
        bitMask = ~(1 << bitPos);
        var &= bitMask;
    }

    return var;
}
