#ifndef TEXT_H
#define TEXT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../main/window.h"


typedef struct {
    int ID;
    int stringLength;
    int delayedTextCurrentChar;
    double delaySpeed;
    long long int delayedTextTargetTime;
    Vec2_Int coords;
    Vec2_Int size;
    Vec2_Int* charCoords;
} UIText;

typedef enum {
    VERSION_NUMBER,
    TEST_UI_TEXT,
    END_OF_UI_TEXTS
} UITextNames;

SDL_Texture* currentFont;
char fontPath[256] = "assets/textures/fonts/WAO Font 16-Bit.png";
Vec2_Int charSpriteSize = {16,16};
int sprite_Sheet_X_Grid_Length = 32;

UIText* textList;

void (*textFunctions[1024]) ();


void initText ();
void createText (int textID, wchar_t textString[], Vec2_Int coords, Vec2_Int size);
void disableText (int textID);
void enableText (int textID);
void delayedText (int textID, double delaySeconds);
void loopTexts ();
void renderText (int textID);
void renderDelayedText (int textID);


void initText () {
    textList = malloc(sizeof(UIText) * 1000);
    currentFont = IMG_LoadTexture(windows[0].renderer, fontPath);
    for (int i = 0; i < 1024; i++) {
        textFunctions[i] = NULL;
    }
}

void createText (int textID, wchar_t textString[], Vec2_Int coords, Vec2_Int size) {
    textList[textID].stringLength = wcslen(textString);
    
    textList[textID].coords = coords;
    textList[textID].size = size;
    textList[textID].delayedTextCurrentChar = 0;
    textList[textID].delaySpeed = 0;
    textList[textID].ID = textID;

    //TODO: Add safety to avoid mallocing the same list multiple times. Use Realloc after first time.
    textList[textID].charCoords = malloc(sizeof(Vec2_Int) * (textList[textID].stringLength + 64));  //64 Extra Bytes for a buffer.

    for (int i = 0; i < textList[textID].stringLength; i++) {
        wchar_t getLetter = textString[i];
        int getLine = getLetter / sprite_Sheet_X_Grid_Length;

        textList[textID].charCoords[i].x = getLetter - (sprite_Sheet_X_Grid_Length*getLine);
        textList[textID].charCoords[i].y = getLine;
    }
}

void disableText (int textID) {
    textFunctions[textID] = NULL;
    textList[textID].delayedTextCurrentChar = 0;
}

void enableText (int textID) {
    textFunctions[textID] = renderText;
    textList[textID].delayedTextCurrentChar = 0;
}

void delayedText (int textID, double delaySeconds) {
    disableText(textID);
    textList[textID].delaySpeed = delaySeconds * 1000000000.0;
    textList[textID].delayedTextTargetTime = currentTime + textList[textID].delaySpeed;
    textFunctions[textID] = renderDelayedText;
}

void loopTexts () {
    for (int i = 0; i < END_OF_UI_TEXTS; i++) {
        if (textFunctions[i] == renderText || textFunctions[i] == renderDelayedText) {
            textFunctions[i](i);
        }
    }
}

void renderText (int textID) {
    int nudgeY = 0;
    int resetX = 0;
    for (int i = 0; i < textList[textID].stringLength; i++) {
        if (textList[textID].charCoords[i].x == '\n' && textList[textID].charCoords[i].y == 0) {
            nudgeY++;
            resetX = i*(textList[textID].size.x*0.75)+(textList[textID].size.x*0.75);
        }
        SDL_RenderCopy(
            windows[0].renderer,
            currentFont,
            &(SDL_Rect){textList[textID].charCoords[i].x*charSpriteSize.x, textList[textID].charCoords[i].y*charSpriteSize.y, charSpriteSize.x, charSpriteSize.y},
            &(SDL_Rect){textList[textID].coords.x+(i*(textList[textID].size.x*0.75))-(resetX), textList[textID].coords.y+(nudgeY*(textList[textID].size.y*1.125)), textList[textID].size.x, textList[textID].size.y}
        );
    }
}

void renderDelayedText (int textID) {  //Maybe this should require a boolean that gets set to true once the text reaches it's end
    int nudgeY = 0;
    int resetX = 0;
    if (currentTime > textList[textID].delayedTextTargetTime) {
        textList[textID].delayedTextCurrentChar++;
        textList[textID].delayedTextTargetTime = currentTime + textList[textID].delaySpeed;
    }
    for (int i = -1; i < min(textList[textID].delayedTextCurrentChar, textList[textID].stringLength); i++) {
        if (textList[textID].charCoords[i].x == '\n' && textList[textID].charCoords[i].y == 0) {
            nudgeY++;
            resetX = i*(textList[textID].size.x*0.75)+(textList[textID].size.x*0.75);
        }
        SDL_RenderCopy(
            windows[0].renderer,
            currentFont,
            &(SDL_Rect){textList[textID].charCoords[i < 0 ? 0 : i].x*charSpriteSize.x, textList[textID].charCoords[i < 0 ? 0 : i].y*charSpriteSize.y, charSpriteSize.x, charSpriteSize.y},
            &(SDL_Rect){textList[textID].coords.x+(i*(textList[textID].size.x*0.75))-(resetX), textList[textID].coords.y+(nudgeY*(textList[textID].size.y*1.125)), textList[textID].size.x, textList[textID].size.y}
        );
    }
}

#endif