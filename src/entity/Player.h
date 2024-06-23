#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/clock.h"
#include "../utils/debugTools.h"
#include "../utils/stringTools.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"

void playerTickUpdate ();
void playerFrameUpdate ();
void playerRender ();
void initPlayers ();


typedef struct {
    byte id;
    double x;
    double y;
    double sizeX;
    double sizeY;
} Player;

Player* playerList;
byte numberOfPlayers = 5;


void playerTickUpdate () {
    if (checkReleasedKey(SDL_SCANCODE_W)) {
        printf("W KEY RELEASED %i\n", keyReleased[26]);
    }
}

void playerFrameUpdate () {

}

void playerRender () {
    SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/textures/players/Idle.png");  //Player Texture
    SDL_RenderCopy(renderer, texture, NULL, NULL);  //Temp Player Render
}


void initPlayers () {
    playerList = malloc(numberOfPlayers * sizeof(Player));
    for (byte i = 0; i < numberOfPlayers; i++) {
        playerList[i].id = i + 1;
    }
    playerRender();
    addTickFunction(playerTickUpdate);
    addFrameFunction(playerFrameUpdate);
    printf("Players Initialized!\n");
}

#endif