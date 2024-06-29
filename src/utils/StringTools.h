#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <stdbool.h>


bool isNum (char c);
bool isAlpha (char c);


bool isNum (char c) {
    return c >= '0' && c <= '9';
}

bool isAlpha (char c) {
    return c >='A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

#endif