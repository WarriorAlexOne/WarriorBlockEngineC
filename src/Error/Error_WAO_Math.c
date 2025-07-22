#include "Error/Error_WAO_Math.h"
#include "Error/WAO_Error.h"

// long long Error_WAO_Fibonacci (long long index) {}

int Error_WAO_ChangeBit (int var, int bitPos, int on_or_off) {
    int errorTracker = 0;
    int bitMask = 0;

    if (bitPos < 0) {
        WAO_GetError(10000);
        bitMask = 1 << 0;
        errorTracker |= bitMask;
    }
    if (bitPos >= sizeof(int)*8) {
        WAO_GetError(10001);
        bitMask = 1 << 1;
        errorTracker |= bitMask;
    }
    if (on_or_off < 0) {
        WAO_GetError(10002);
        bitMask = 1 << 2;
        errorTracker |= bitMask;
    }
    if (on_or_off > 1) {
        WAO_GetError(10003);
        bitMask = 1 << 3;
        errorTracker |= bitMask;
    }

    return errorTracker;
}