#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/clock.h"
#include "../input/inputs.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"


typedef struct {
    byte ID;
    double x;
    double y;
    double sizeX;
    double sizeY;
} Player;

Player* playerList;
byte numberOfPlayers = 1;

SDL_Rect playerRect;

SDL_Texture* texture;


void initPlayers ();
void playerTickUpdate ();
void playerFrameUpdate ();
void playerRender ();


void initPlayers () {
    playerList = malloc(numberOfPlayers * sizeof(Player));
    for (byte i = 0; i < numberOfPlayers; i++) {
        playerList[i].ID = i + 1;
        playerList[i].x = 0;
        playerList[i].y = 0;
        playerList[i].sizeX = 16 * gameScale;
        playerList[i].sizeY = 16 * gameScale;
    }
    addTickFunction(playerTickUpdate);
    addFrameFunction(playerFrameUpdate);
    printf("Players Initialized!\n");
}

void playerTickUpdate () {
    
}

void playerFrameUpdate () {
    if (checkHeldKey(SDL_SCANCODE_EQUALS)) {
        gameScale += 0.1;
        playerList[0].sizeX = DEFAULT_TILE_SIZE * gameScale;
        playerList[0].sizeY = DEFAULT_TILE_SIZE * gameScale;
    }
    if (checkHeldKey(SDL_SCANCODE_MINUS)) {
        gameScale -= 0.1;
        playerList[0].sizeX = DEFAULT_TILE_SIZE * gameScale;
        playerList[0].sizeY = DEFAULT_TILE_SIZE * gameScale;
    }
    if (checkHeldKey(SDL_SCANCODE_D)) {
        playerList[0].x += (1 * 60) * deltaTime;
    }
    if (checkHeldKey(SDL_SCANCODE_A)) {
        playerList[0].x -= (1 * 60) * deltaTime;
    }
    if (checkHeldKey(SDL_SCANCODE_W)) {
        playerList[0].y -= (1 * 60) * deltaTime;
    }
    if (checkHeldKey(SDL_SCANCODE_S)) {
        playerList[0].y += (1 * 60) * deltaTime;
    }
}

void playerRender () {
    playerRect = makeRect((int)playerList[0].x, (int)playerList[0].y, (int)playerList[0].sizeX, (int)playerList[0].sizeY);

    texture = IMG_LoadTexture(renderer, "assets/textures/players/Slome.png");

    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

#endif