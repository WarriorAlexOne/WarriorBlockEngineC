#ifndef WBE_STRING_H
#define WBE_STRING_H

int WBE_IsCharNum (char character);
int WBE_IsCharLetter (char character);
int WBE_IsCharLowerCase (char character);
int WBE_IsCharUpperCase (char character);
char* WBE_ShiftStringAlpha (char string[], int shiftSteps);
int WBE_strcpy (char* dstStr, char* srcStr, int maxDstLen);

#endif