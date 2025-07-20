#ifndef WAO_SPLASH_H
#define WAO_SPLASH_H

// extern char* splashList[];

typedef struct {
    int listLength;
    int maxStringLength;
    char** splashList;
} SplashList;

void WAO_InitSplashList ();

#endif