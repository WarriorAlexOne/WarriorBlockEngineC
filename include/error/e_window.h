#ifndef E_WINDOW_H
#define E_WINDOW_H

#include "../../include/util/common.h"


char window_list_not_init[] = "Window List not initialized!";

char init_windows[] = "INIT WINDOWS:";
char create_window[] = "CREATE WINDOW:";
char toggle_window[] = "TOGGLE WINDOW:";
char set_window_icon[] = "SET WINDOW ICON:";
char cleanup_windows[] = "CLEANUP WINDOWS:";


bool e_initWindows ();
bool e_createWindow (int windowID, char title[], int x, int y, int w, int h);
bool e_toggleWindow (int windowID, bool state);
bool e_setWindowIcon (int windowID, char iconPath[]);
bool e_cleanupWindows ();

#endif