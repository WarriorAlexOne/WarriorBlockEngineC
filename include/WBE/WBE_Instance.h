#ifndef WBE_INSTANCE_H
#define WBE_INSTANCE_H

#include "WBE/WBE_Instance_Types.h"
#include <SDL3/SDL.h>

WBE_Instance WBE_CreateNewInstance ();
bool WBE_Update (WBE_Instance* instance);
bool WBE_InstanceQuitState (WBE_Instance* instance);

#endif