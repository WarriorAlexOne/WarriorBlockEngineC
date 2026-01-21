#include "WBE/Input/WBE_Mouse.h"
#include "WBE/Input/WBE_Input.h"

WBE_Mouse mouse;


void WBE_InitMouse () {

}

void WBE_UpdateMouse () {
    WBE_UpdateInput(NULL);
    mouse.lastPos = mouse.pos;
    mouse.mouseState = SDL_GetMouseState(&mouse.pos.x, &mouse.pos.y);
    mouse.vel = WBE_Vec2fSubtract(mouse.pos, mouse.lastPos);

    if (mouse.mouseState & SDL_BUTTON_LMASK) mouse.click[0] = true;
    else mouse.click[0] = false;
    if (mouse.mouseState & SDL_BUTTON_MMASK) mouse.click[1] = true;
    else mouse.click[1] = false;
    if (mouse.mouseState & SDL_BUTTON_RMASK) mouse.click[2] = true;
    else mouse.click[2] = false;
    if (mouse.mouseState & SDL_BUTTON_X1MASK) mouse.click[3] = true;
    else mouse.click[3] = false;
    if (mouse.mouseState & SDL_BUTTON_X2MASK) mouse.click[4] = true;
    else mouse.click[4] = false;
}

bool WBE_IsMouseDown (WBE_MouseButtons mouseButton) {
    if (mouseButton < 0) {
        SDL_Log("WBE: WBE_IsMouseDown: Argument value is too low! Please use the WBE_MouseButtons enum for values, or choose a value from 0-4.");
    }
    if (mouseButton > 4) {
        SDL_Log("WBE: WBE_IsMouseDown: Argument value is too high! Please use the WBE_MouseButtons enum for values, or choose a value from 0-4.");
    }
    return mouse.click[mouseButton];
}

WBE_Vec2f WBE_GetMousePos () {
    WBE_Vec2f newPos = {mouse.pos.x, mouse.pos.y};
    return newPos;
}

WBE_Vec2f WBE_GetMouseVelocity () {
    return mouse.vel;
}
