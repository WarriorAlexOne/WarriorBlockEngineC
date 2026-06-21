#include "WBE/Util/WBE_List.h"


WBE_List** listTracker = NULL;
int listTrackerSize = 0;
int listTrackerCount = 0;

int listID = 0;


/*
Allocates memory to a user-provided pointer of any type; similar to malloc().
WBE keeps track of list info in the background.
*/
void* WBE_CreateList (unsigned int sizeof_type) {
    if (listTracker == NULL) {
        listTracker = SDL_malloc(sizeof(WBE_List*) * WBE_LIST_TRACKER_DEFAULT_SIZE);
        for (int i = 0; i < WBE_LIST_TRACKER_DEFAULT_SIZE; i++) {
            listTracker[i] = SDL_malloc(sizeof(WBE_List));
        }
        listTrackerSize = WBE_LIST_TRACKER_DEFAULT_SIZE;
    }
    if (listTrackerCount == listTrackerSize) {
        listTrackerSize *= 2;
        listTracker = SDL_realloc(listTracker, sizeof(WBE_List*) * listTrackerSize);
    }

    // Fill in default info.
    WBE_List* newList = SDL_malloc(sizeof(WBE_List));
    newList->listID = ++listID;
    newList->sizeof_type = sizeof_type;
    newList->arraySize = WBE_LIST_DEFAULT_SIZE;
    newList->lastIndexFilled = -1;

    // Create new pointer array for the user.
    void* newArray;
    newArray = SDL_malloc(sizeof_type * (WBE_LIST_DEFAULT_SIZE+1));  //+1 for expansion buffer.
    // SDL_Log("New Pointer: %i", &newArray);

    /*
    Store pointer to verify memory address later
    (allows the user to use any type they want, at the risk of them changing
    the memory address, causing the WBE_List to no longer work).
    */
    newList->listAddress = newArray;

    // Store data in the WBE list tracker.
    listTracker[listTrackerCount] = newList;
    listTrackerCount++;

    return newArray;
}

unsigned int WBE_ListAdd_Func (void** list) {
    for (int i = 0; i < listTrackerCount; i++) {
        // If memory address matches one in the list tracker:
        if (*list == listTracker[i]->listAddress) {

            // If list has reached max size, increase size.
            if (listTracker[i]->lastIndexFilled+1 == listTracker[i]->arraySize) {

                listTracker[i]->arraySize *= 2;
                // SDL_Log("Before: %i", *list);
                void* newList = SDL_realloc(*list, listTracker[i]->sizeof_type * listTracker[i]->arraySize);
                *list = newList;
                // SDL_Log("After: %i", *list);

                listTracker[i]->listAddress = *list;
                // SDL_Log("List Expanded To %i!", listTracker[i]->arraySize);
            }

            // Increase count, then return previous count value (for use in arrays).
            listTracker[i]->lastIndexFilled++;
            // SDL_Log("Index %i Added!", listTracker[i]->lastIndexFilled);
            return listTracker[i]->lastIndexFilled;
        }
    }
    // Add WBE_Error code function here. List could not be found...
    return 0;
}


unsigned int WBE_GetLastIndex (void* list) {
    for (int i = 0; i < listTrackerCount; i++) {
        if (list == listTracker[i]->listAddress) {
            return listTracker[i]->lastIndexFilled;
        }
    }
    // Add error code, list could not be found...
}