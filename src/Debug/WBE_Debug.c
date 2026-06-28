#include "WBE/Debug/WBE_Debug.h"

bool showDebug_Keyboard = false;

void ShowDebug_WBE_Keyboard (bool state) {
    if (state == 0 || state == 1) showDebug_Keyboard = state;
}
bool GetDebugState_WBE_Keyboard () {
    return showDebug_Keyboard;
}
