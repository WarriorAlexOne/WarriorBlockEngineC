#ifndef WBE_INSTANCE_H
#define WBE_INSTANCE_H

#include "WBE/WBE_Instance_Types.h"
#include <SDL3/SDL.h>

WBE_Instance WBE_CreateNewInstance ();
void WBE_Update (WBE_Instance* instance);

#endif