#ifndef WBE_SPLASH_H
#define WBE_SPLASH_H

#define WBE_MAX_SPLASH_LIST_LENGTH 1024
#define WBE_MAX_SPLASH_STRING_LENGTH 512

// extern char* splashList[];

typedef struct {
    int listLength;
    int maxStringLength;
    char** splashList;
} WBE_SplashList;

char** WBE_CreateSplashList (int listLength, int maxStringLength);

#endif