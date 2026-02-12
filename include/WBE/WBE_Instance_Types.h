#ifndef WBE_INSTANCE_TYPES_H
#define WBE_INSTANCE_TYPES_H

#include "WBE/WBE_Defines.h"

typedef struct {
    bool isInitialized;

    void** clocks;
    void** windows;
    void** keyCheckers;

    int clockCount;
    int windowCount;
    int keyCheckerCount;

    bool doesClockExist;
    bool doesWindowExist;
    bool doesKeyCheckerExist;
} WBE_Instance;

#endif