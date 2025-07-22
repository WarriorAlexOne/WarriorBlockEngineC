#ifndef WAO_SPLASH_H
#define WAO_SPLASH_H

#define WAO_MAX_SPLASH_LIST_LENGTH 1024
#define WAO_MAX_SPLASH_STRING_LENGTH 512

// extern char* splashList[];

typedef struct {
    int listLength;
    int maxStringLength;
    char** splashList;
} WAO_SplashList;

char** WAO_CreateSplashList (int listLength, int maxStringLength);

#endif