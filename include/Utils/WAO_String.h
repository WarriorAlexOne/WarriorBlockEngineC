#ifndef WAO_STRING_H
#define WAO_STRING_H

int WAO_IsCharNum (char character);
int WAO_IsCharLetter (char character);
int WAO_IsCharLowerCase (char character);
int WAO_IsCharUpperCase (char character);
char* WAO_StringShiftAlpha (char string[], int shiftSteps);

#endif