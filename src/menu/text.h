#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../main/window.h"


TTF_Font* font;
SDL_Texture *textTexture;
char c1 = ' ';
char c2 = '~';


void initText ();
void renderText ();


void initText () {
    //Temp Text Code
    font = TTF_OpenFont("assets/fonts/ARIAL.TTF", 500);
    SDL_Color color = {255, 255, 255};  // white color
    SDL_Surface *surface = TTF_RenderText_Solid(font, "WarriorBlockEngine v0.0", color);
    textTexture = SDL_CreateTextureFromSurface(windows[0].renderer, surface);
    SDL_FreeSurface(surface);
}

void renderText () {
    SDL_RenderCopy(windows[0].renderer, textTexture, NULL, &(SDL_Rect){0,0,256,28});
}
    
#endif