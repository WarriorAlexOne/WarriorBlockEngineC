#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include "../../include/util/common.h"


bool checkKeyHeld (short scancode);
bool checkKeyPressed (short scancode);
bool checkKeyReleased (short scancode);
void initKeyInput ();
void updateKeyInput ();

#endif