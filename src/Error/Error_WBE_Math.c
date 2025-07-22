#include "Error/Error_WBE_Math.h"
#include "Error/WBE_Error.h"
#include <stdint.h>

// long long Error_WBE_Fibonacci (long long index) {}

int32_t Error_WBE_ChangeBit (int var, int bitPos, int on_or_off) {
    int errorTracker = 0;
    int bitMask = 0;

    if (bitPos < 0) {
        WBE_GetError(WBE_ChangeBit_ERROR_1);
        bitMask = 1 << 0;
        errorTracker |= bitMask;
    }
    if (bitPos >= sizeof(int32_t)*8) {
        WBE_GetError(WBE_ChangeBit_ERROR_2);
        bitMask = 1 << 1;
        errorTracker |= bitMask;
    }
    if (on_or_off < 0) {
        WBE_GetError(WBE_ChangeBit_ERROR_3);
        bitMask = 1 << 2;
        errorTracker |= bitMask;
    }
    if (on_or_off > 1) {
        WBE_GetError(WBE_ChangeBit_Error_4);
        bitMask = 1 << 3;
        errorTracker |= bitMask;
    }

    return errorTracker;
}