#ifndef WBE_LIST_H
#define WBE_LIST_H

#include <SDL3/SDL.h>

// #define WBE_ListAdd(ptr) WBE_ListAdd_Func((void**)&(ptr))

#define WBE_ListAdd(ptr) WBE_ListAdd_Func((void**)&(ptr)); \
                         ptr[WBE_GetLastIndex(ptr)]

// WBE_ListAdd(test);
// test[WBE_GetLastIndex(test)] = (WBE_Test){i*i, i, i*1.5, i*1.128};

#define WBE_LIST_TRACKER_DEFAULT_SIZE 64
#define WBE_LIST_DEFAULT_SIZE 8

typedef struct {
    int listID;
    int sizeof_type;
    int arraySize;
    int lastIndexFilled;
    bool needsExpanding;
    void* listAddress;
    void* nextAddress;
} WBE_List;

void* WBE_CreateList (unsigned int sizeof_type);
unsigned int WBE_ListAdd_Func (void** list);
unsigned int WBE_GetLastIndex (void* list);

#endif