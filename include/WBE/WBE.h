#ifndef WBE_H
#define WBE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "WBE/WBE_Info.h"
#include "WBE/WBE_Defines.h"

#include "WBE/WBE_Clock.h"
#include "WBE/WBE_Window.h"
#include "WBE/Input/WBE_Scancodes.h"
#include "WBE/Input/WBE_Keyboard.h"
#include "WBE/Input/WBE_Mouse.h"
#include "WBE/Input/WBE_Input.h"

#include "WBE/Paint/WBE_Gradient.h"

#include "WBE/WBE_Cleanup.h"
#include "WBE/WBE_Instance.h"

bool WBE_Init ();

#endif