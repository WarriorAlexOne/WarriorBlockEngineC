#include "Error/WBE_Error.h"
#include "Error/Error_WBE_Math.h"

// long long Error_WBE_Fibonacci (long long index) {}

int32_t Error_WBE_ChangeBit (int32_t var, unsigned int bitPos, unsigned int on_or_off) {
    int32_t errorTracker = 0;
    int32_t bitMask = 0;

    // Maybe add limit for var if using a long long arg causes security issues.

    if (bitPos < 0) {   // Impossible, but will be kept for any future changes.
        WBE_GetError(WBE_ChangeBit_ERROR_1);
        bitMask = 1 << 0;
        errorTracker |= bitMask;
    }
    if (bitPos >= sizeof(int32_t)*8) {
        WBE_GetError(WBE_ChangeBit_ERROR_2);
        bitMask = 1 << 1;
        errorTracker |= bitMask;
    }
    if (on_or_off < 0) {   // Impossible, but will be kept for any future changes.
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
