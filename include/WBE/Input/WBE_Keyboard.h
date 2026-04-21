#ifndef WBE_KEY_H
#define WBE_KEY_H

#include "WBE/WBE_Instance_Types.h"
#include "WBE/Input/WBE_Scancodes.h"

void WBE_UpdateKeys (WBE_Instance* instance);
void WBE_FrameUpdateKeys (WBE_Instance* instance);
bool WBE_IsKeyDown (WBE_Instance* instance, WBE_Scancode scancode);
bool WBE_IsKeyUp (WBE_Instance* instance, WBE_Scancode scancode);
bool WBE_IsKeyPressed (WBE_Instance* instance, WBE_Scancode scancode);
bool WBE_IsKeyReleased (WBE_Instance* instance, WBE_Scancode scancode);

#endif