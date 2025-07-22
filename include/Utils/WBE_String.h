#ifndef WBE_STRING_H
#define WBE_STRING_H

int WBE_IsCharNum (char character);
int WBE_IsCharLetter (char character);
int WBE_IsCharLowerCase (char character);
int WBE_IsCharUpperCase (char character);
char* WBE_StringShiftAlpha (char string[], int shiftSteps);

#endif