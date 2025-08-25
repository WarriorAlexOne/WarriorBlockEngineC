#include "WBE/Utils/WBE_List.h"
#include <stdlib.h>

void* CreateList (int sizeof_Type, int indexAmount) {
    void* pointer = malloc(sizeof_Type * indexAmount);
    return pointer;
}
