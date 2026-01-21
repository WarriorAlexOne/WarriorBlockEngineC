#ifndef WBE_LIST_H
#define WBE_LIST_H

#define WBE_MAX_LIST_SIZE

// typedef struct {
//     int listID;
//     int sizeof_type;
//     int indexCount;
//     void* dynamicArray;
// } WBE_List;

void* WBE_CreateList (void* pointer, unsigned int sizeof_type, unsigned int indexCount);

#endif