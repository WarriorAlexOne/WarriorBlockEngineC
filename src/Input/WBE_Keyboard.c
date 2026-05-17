#include "WBE/Input/WBE_Keyboard.h"
#include "WBE/Input/WBE_Input_Defines.h"


// Checks for scancode events, then updates the isKeyDown bool to the correct state.
void WBE_UpdateKeys (WBE_Instance* instance) {
    if (instance->event.key.scancode < 0 || instance->event.key.scancode > SDL_SCANCODE_COUNT) return;
    int scancode = instance->event.key.scancode;

    if (instance->event.type == SDL_EVENT_KEY_DOWN) instance->keyboard.isKeyDown[scancode] = true;
    if (instance->event.type == SDL_EVENT_KEY_UP) instance->keyboard.isKeyDown[scancode] = false;
}

// Updates key press/release states.
void WBE_FrameUpdateKeys (WBE_Instance* instance) {
    // Check every scancode to set isKeyPressed/Released to false after 1 frame has passed.
    for (int scancode = 0; scancode < SDL_SCANCODE_COUNT; scancode++) {
        // If key is released...
        if (!instance->keyboard.isKeyDown[scancode]) {
            // Set isKeyReleased to false if it was true last frame.
            if (instance->keyboard.isKeyReleased[scancode]) instance->keyboard.isKeyReleased[scancode] = false;
            // Set isKeyReleased to true if key was pressed last frame (will be false next frame ^^^).
            if (instance->keyboard.wasKeyPressed[scancode]) {
                instance->keyboard.isKeyReleased[scancode] = true;
                // SDL_Log("%s key was released!", SDL_GetScancodeName(scancode));
            }
            // Set wasKeyPressed and isKeyPressed to false, since key was released.
            instance->keyboard.wasKeyPressed[scancode] = false;
            instance->keyboard.isKeyPressed[scancode] = false;
            // Skip rest of code since key is released.
            continue;
        }
        // Check if key was pressed last frame (wasKeyPressed).
        if (instance->keyboard.wasKeyPressed[scancode]) {
            instance->keyboard.isKeyPressed[scancode] = false;
            continue;
        }

        // If both if statements are false, then it's safe to assume key was pressed.
        instance->keyboard.isKeyPressed[scancode] = true;
        instance->keyboard.wasKeyPressed[scancode] = true;

        WBE_LogKey(instance, scancode);

        // SDL_Log("Test");
        // for (int i = 0; i < WBE_MAX_KEYLOGGER_LENGTH; i++) {
        //     if (instance->keyboard.keyLogs[i] != 0) {
        //         SDL_Log(SDL_GetKeyName(SDL_GetKeyFromScancode(instance->keyboard.keyLogs[i], 0, 0)));
        //     }
        // }

        SDL_Log("%s key was pressed!", SDL_GetScancodeName(scancode));
    }
}

// Checks if a key is pressed. Returns true for every frame the key is pressed.
bool WBE_IsKeyDown (WBE_Instance* instance, WBE_Scancode scancode) {
    if (instance->keyboard.isKeyDown[scancode]) {
        WBE_LogKey(instance, scancode);
        return true;
    }
    return false;
    // return instance->keyboard.isKeyDown[scancode];
}
// Checks if a key was released. Returns true for every frame the key is released.
bool WBE_IsKeyUp (WBE_Instance* instance, WBE_Scancode scancode) {
    if (!instance->keyboard.isKeyDown[scancode]) {
        WBE_LogKey(instance, scancode);
        return true;
    }
    return false;
}
// Checks if a key is pressed. Returns true for the first frame the key is pressed.
bool WBE_IsKeyPressed (WBE_Instance* instance, WBE_Scancode scancode) {
    if (instance->keyboard.isKeyPressed[scancode]) {
        WBE_LogKey(instance, scancode);
        return true;
    }
    return false;
}
// Checks if a key is released. Returns true for the first frame the key is released.
bool WBE_IsKeyReleased (WBE_Instance* instance, WBE_Scancode scancode) {
    if (instance->keyboard.isKeyReleased[scancode]) {
        WBE_LogKey(instance, scancode);
        return true;
    }
    return false;
}

void WBE_LogKey (WBE_Instance* instance, WBE_Scancode scancode) {
    for (int i = WBE_MAX_KEYLOGGER_LENGTH-1; i > 0; i--) {
        instance->keyboard.keyLogs[i] = instance->keyboard.keyLogs[i-1];
    }
    instance->keyboard.keyLogs[0] = scancode;
}