#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/globalVariables.h"
#include "../utils/clock.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../entity/camera.h"
#include "../maps/tiles.h"
#include "../maps/levelGen.h"


byte numberOfPlayers = 1;

SDL_Rect playerRect;

SDL_Texture* texture;


void initPlayers ();
void playerTickUpdate ();
void playerFrameUpdate ();
void playerRender ();
void playerGravity (Player* player[]);
void playerJump (Player* player[]);
void playerFrameInput (Player* player[]);


void initPlayers () {
    players = malloc(numberOfPlayers * sizeof(Player));
    for (byte i = 0; i < numberOfPlayers; i++) {
        players[i].ID = i + 1;
        
        //Coords
        players[i].x = 0;
        players[i].y = 0;
        players[i].sizeX = 16 * gameScale;
        players[i].sizeY = 16 * gameScale;

        //Speed
        players[i].speed = 50 * gameScale;
        players[i].velocityX = 0 * gameScale;
        players[i].velocityY = 0 * gameScale;

        //Jump
        players[i].canJump = false;
        players[i].jumped = false;
        players[i].isJumping = false;
        players[i].isFalling = false;
        players[i].jumpPower = 60 * gameScale;
        players[i].jumpAccel = 1 * gameScale;
        players[i].jumpVelocity = 0 * gameScale;

        //Gravity
        players[i].gravity = 1 * gameScale;

        //Collision
        players[i].onGround = false;
    }
    texture = IMG_LoadTexture(renderer, "assets/textures/players/Slome.png");  //Temporary
    addTickFunction(playerTickUpdate);
    addFrameFunction(playerFrameUpdate);
    printf("Players Initialized!\n");
}

void playerTickUpdate () {
    
}

void playerFrameUpdate () {
    playerFrameInput(&players);
    playerGravity(&players);
    playerJump(&players);
    
}

void playerRender () {
    playerRect = makeRect((int)players[0].x, (int)players[0].y, (int)players[0].sizeX, (int)players[0].sizeY);

    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

void playerGravity (Player* player[]) {

}

void playerJump (Player* player[]) {

}

void playerFrameInput (Player* player[]) {
    for (byte i = 0; i < numberOfPlayers; i++) {
        if (checkKeyHeld(SDL_SCANCODE_EQUALS)) {
            gameScale += (0.01 * 60) * deltaTime;
            player[i]->sizeX = DEFAULT_TILE_SIZE * gameScale;
            player[i]->sizeY = DEFAULT_TILE_SIZE * gameScale;
        }
        if (checkKeyHeld(SDL_SCANCODE_MINUS) && gameScale >= 0.1) {
            gameScale -= (0.01 * 60) * deltaTime;
            player[i]->sizeX = DEFAULT_TILE_SIZE * gameScale;
            player[i]->sizeY = DEFAULT_TILE_SIZE * gameScale;
        }

        if (checkKeyHeld(SDL_SCANCODE_LEFTBRACKET)) {
            perlinSeed -= (1 * 60) * deltaTime;
            printf("%f\n", perlinSeed);
        }
        if (checkKeyHeld(SDL_SCANCODE_RIGHTBRACKET)) {
            perlinSeed += (1 * 60) * deltaTime;
            printf("%f\n", perlinSeed);
        }
        if (checkKeyHeld(SDL_SCANCODE_C)) {
            // createLevel();
        }

        if (checkKeyHeld(SDL_SCANCODE_W)) {
            player[i]->y -= ((player[i]->speed * 60) * deltaTime) * gameScale;
        }
        if (checkKeyHeld(SDL_SCANCODE_A)) {
            player[i]->x -= ((player[i]->speed * 60) * deltaTime) * gameScale;
        }
        if (checkKeyHeld(SDL_SCANCODE_S)) {
            player[i]->y += ((player[i]->speed * 60) * deltaTime) * gameScale;
        }
        if (checkKeyHeld(SDL_SCANCODE_D)) {
            player[i]->x += ((player[i]->speed * 60) * deltaTime) * gameScale;
        }

        if (checkKeyPressed(SDL_SCANCODE_T)) {
            printf("T PRESSED!!!!\n");
        }
    }
}

#endif