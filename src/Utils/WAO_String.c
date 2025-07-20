#include "Utils/WAO_String.h"

bool WAO_IsCharNum (char character) {
    return character >= '0' && character <= '9';
}

bool WAO_IsCharLetter (char character) {
    return (character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z');
}

bool WAO_IsCharLowerCase (char character) {
    return (character >= 'a' && character <= 'z');
}

bool WAO_IsCharUpperCase (char character) {
    return (character >= 'A' && character <= 'Z');
}

char* WAO_StringShiftAlpha (char string[], int shiftSteps) {
    if (shiftSteps == 0) return string;   // Return string if there is no shift.

    long long unsigned int stringLength = strlen(string);
    shiftSteps %= 26;   // If steps is a multiple of 26, go back to 0

    if (shiftSteps < 0) goto WAO_StringShiftAlpha_NegativeStep;   // If shift argument is negative, go to the second loop.

    // Positive Shift Logic
    for (long long unsigned int i = 0; i < stringLength; i++) {
        if (String_isLowerCase(string[i])) {
            if ((string[i] + shiftSteps) > 'z') {
                string[i] -= 26;
                string[i] += shiftSteps;
                continue;
            }
            string[i] += shiftSteps;
        }

        else if (String_isUpperCase(string[i])) {
            if ((string[i] + shiftSteps) > 'Z') {
                string[i] -= 26;
                string[i] += shiftSteps;
                continue;
            }
            string[i] += shiftSteps;
        }
    }
    return string;

    WAO_StringShiftAlpha_NegativeStep:
    // Negative Shift Logic
    for (long long unsigned int i = 0; i < stringLength; i++) {
        if (String_isLowerCase(string[i])) {
            if ((string[i] + shiftSteps) < 'a') {
                string[i] += 26;
                string[i] += shiftSteps;
                continue;
            }
            string[i] += shiftSteps;
        }

        else if (String_isUpperCase(string[i])) {
            if ((string[i] + shiftSteps) < 'A') {
                string[i] += 26;
                string[i] += shiftSteps;
                continue;
            }
            string[i] += shiftSteps;
        }
    }
    return string;
}
