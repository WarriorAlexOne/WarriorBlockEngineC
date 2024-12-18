#include "../../include/util/common.h"

#include "../../include/util/string_tools.h"


bool charIsNum (char c) {
    return c >= '0' && c <= '9';
}

bool charIsAlpha (char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}