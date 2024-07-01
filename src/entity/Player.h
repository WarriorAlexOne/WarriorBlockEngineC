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
#include "../input/mouseInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../entity/camera.h"
#include "../maps/tiles.h"
#include "../maps/levelGen.h"


typedef struct {
    byte ID;

    //Coords
    double x;
    double y;
    double sizeX;
    double sizeY;
    int screenX;
    int screenY;

    //Speed
    double speed;
    double velocityX;
    double velocityY;

    //Jump
    bool canJump;
    bool jumped;
    bool isJumping;
    bool isFalling;
    double jumpPower;
    double jumpAccel;
    double jumpVelocity;

    //Gravity
    double gravity;
    double gravityAccel;

    //Collision
    bool onGround;
} Player;

Player* players;
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
        players[i].screenX = windowW/2;
        players[i].screenY = windowH/2;

        //Speed
        players[i].speed = 10 * gameScale;
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
    if (checkKeyHeld(SDL_SCANCODE_EQUALS)) {
        gameScale *= 1.01;
        // cameraX += 10.0;
        // cameraY += 20.0;
    }
        
    if (checkKeyHeld(SDL_SCANCODE_MINUS) && gameScale >= 0.1) {
        gameScale /= 1.01;
        // cameraX -= 20.0;
        // cameraY -= 20.0;
    }
}

void playerFrameUpdate () {
    playerFrameInput(&players);
    playerGravity(&players);
    playerJump(&players);
}

void playerRender () {
    playerRect = makeRect((int)players[0].screenX, (int)players[0].screenY, (int)players[0].sizeX, (int)players[0].sizeY);

    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

void playerGravity (Player* player[]) {

}

void playerJump (Player* player[]) {

}

void playerFrameInput (Player* player[]) {
    for (byte i = 0; i < numberOfPlayers; i++) {
        player[i]->sizeX = DEFAULT_TILE_SIZE * gameScale;
        player[i]->sizeY = DEFAULT_TILE_SIZE * gameScale;

        player[i]->screenX = (windowW/2) - player[i]->sizeX/2;
        player[i]->screenY = (windowH/2) - player[i]->sizeY/2;

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
            cameraY -= (player[i]->speed * 60) * deltaTime;
        }
        if (checkKeyHeld(SDL_SCANCODE_A)) {
            cameraX -= (player[i]->speed * 60) * deltaTime;
        }
        if (checkKeyHeld(SDL_SCANCODE_S)) {
            cameraY += (player[i]->speed * 60) * deltaTime;
        }
        if (checkKeyHeld(SDL_SCANCODE_D)) {
            cameraX += (player[i]->speed * 60) * deltaTime;
        }

        if (checkKeyPressed(SDL_SCANCODE_T)) {
            printf("T PRESSED!!!!\n");
        }
        if (checkMousePressed(MOUSE_LEFT)) {
            printf("LEFT CLICK!!!\n");
        }
        if (checkMousePressed(MOUSE_RIGHT)) {
            printf("RIGHT CLICK!!!\n");
        }
        if (checkMousePressed(MOUSE_MIDDLE)) {
            printf("MIDDLE CLICK!!!\n");
        }
        if (checkMouseReleased(MOUSE_LEFT)) {
            printf("-----LEFT RELEASED!!!\n");
        }
        if (checkMouseReleased(MOUSE_RIGHT)) {
            printf("-----RIGHT RELEASED!!!\n");
        }
        if (checkMouseReleased(MOUSE_MIDDLE)) {
            printf("-----MIDDLE RELEASED!!!\n");
        }
    }
}

#endif