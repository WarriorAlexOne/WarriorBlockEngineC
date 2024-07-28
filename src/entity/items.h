#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../main/window.h"


const char ITEM_FILE_PATH[24] = "assets/textures/items/";

typedef struct {
    SDL_Texture* texture;
} Item;

typedef enum {
    NONE,
    IRON_PICKAXE
} ItemNames;

Item items[16];

short numberOfItems = 0;


void initItems ();
Item createItem (char itemName[]);
SDL_Texture* createItemTexture (SDL_Texture* texture, char texturePath[]);
void destroyItemTextures (Item items[], int itemAmount);


void initItems () {
    items[IRON_PICKAXE] = createItem("iron_pickaxe");
    printf("Items Initialized!\n");
}

Item createItem (char itemName[]) {
    char texturePath[128];
    Item newItem;

    sprintf(texturePath, "%s%s%s", ITEM_FILE_PATH, itemName, ".png");
    newItem.texture = createItemTexture(newItem.texture, texturePath);

    numberOfItems++;

    return newItem;
}

SDL_Texture* createItemTexture (SDL_Texture* texture, char texturePath[]) {
    texture = IMG_LoadTexture(windows[0].renderer, texturePath);
    return texture;
}

void destroyItemTextures (Item items[], int itemAmount) {
    for (int i = 0; i < itemAmount; i++) {
        SDL_DestroyTexture(items[i].texture);
    }
}

#endif