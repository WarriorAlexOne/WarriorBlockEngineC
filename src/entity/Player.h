#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/globalVariables.h"
#include "../utils/tools.h"
#include "../utils/vector2D.h"
#include "../utils/clock.h"
#include "../main/window.h"
#include "../input/keyInput.h"
#include "../input/mouseInput.h"
#include "../input/controllerInput.h"
#include "../input/touchInput.h"
#include "../entity/controls.h"
#include "../entity/camera.h"


typedef struct {
    bool up;
    bool left;
    bool down;
    bool right;
    bool jump;
    bool pause;
} Controls;

typedef struct {
    byte ID;

    //Controls
    Controls pressed;
    bool controlsEnabled;

    //Coordinates
    Vec2 coords;
    Vec2 size;
    Vec2 screenCoords;

    //Speed
    double speed;
    Vec2 velocity;

    //Jump
    bool isJumping;
    bool isFalling;
    double jumpPower;

    //Gravity
    double gravity;

    //Collision
    bool onGround;
} Player;

Player* players;
byte numberOfPlayers = 1;

SDL_Rect playerRect;

SDL_Texture* texture;

bool playerInit = false;


void initPlayers ();
void playerTickUpdate ();
void playerFrameUpdate ();
void playerRender ();
void playerGravity (Player* player[]);
void playerJump (Player* player[]);
void playerFrameInput (Player* player[]);
void playerUpdateStats (Player* player[]);


void initPlayers () {
    players = malloc(numberOfPlayers * sizeof(Player));
    for (byte i = 0; i < numberOfPlayers; i++) {
        players[i].ID = i + 1;
        
        //Coords
        players[i].coords.x = 0;
        players[i].coords.y = 0;
        players[i].size.x = 16;
        players[i].size.y = 16;

        //Speed
        players[i].speed = 0.25;
        players[i].velocity.x = 0;
        players[i].velocity.y = 0;

        //Jump
        players[i].jumpPower = 2.5;

        //Gravity
        players[i].gravity = 0.1;

        //Collision
        players[i].onGround = false;

        //Controls
        players[i].controlsEnabled = true;
        players[i].pressed.up = false;
        players[i].pressed.left = false;
        players[i].pressed.down = false;
        players[i].pressed.right = false;
        players[i].pressed.jump = false;
        players[i].pressed.pause = false;
    }
    texture = IMG_LoadTexture(windows[0].renderer, "assets/textures/players/Idle.png");  //Temporary
    addTickFunction(playerTickUpdate);
    addFrameFunction(playerFrameUpdate);

    playerInit = true;
    printf("Players Initialized!\n");
}

void playerTickUpdate () {
    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_EQUALS)) {
        gameScale *= 1.015;
    }
    else if (checkKeyHeld(SDL_SCANCODE_EQUALS)) {
        gameScale *= 1.005;
    }

    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_MINUS) && gameScale >= 0.1) {
        gameScale /= 1.015;
    }
    else if (checkKeyHeld(SDL_SCANCODE_MINUS) && gameScale >= 0.1) {
        gameScale /= 1.005;
    }

    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_LEFTBRACKET)) {
        worldRotation -= 0.02;
        if (worldRotation < 0) {
            worldRotation += 6.28318530717958647692;
        }
        printf("Rotation: %f\n", worldRotation);
    }
    else if (checkKeyHeld(SDL_SCANCODE_LEFTBRACKET)) {
        worldRotation -= 0.004;
        if (worldRotation < 0) {
            worldRotation += 6.28318530717958647692;
        }
        printf("Rotation: %f\n", worldRotation);
    }

    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_RIGHTBRACKET)) {
        worldRotation += 0.02;
        if (worldRotation >= 6.28318530717958647692) {
            worldRotation -= 6.28318530717958647692;
        }
        printf("Rotation: %f\n", worldRotation);
    }
    else if (checkKeyHeld(SDL_SCANCODE_RIGHTBRACKET)) {
        worldRotation += 0.004;
        if (worldRotation >= 6.28318530717958647692) {
            worldRotation -= 6.28318530717958647692;
        }
        printf("Rotation: %f\n", worldRotation);
    }

    if (checkKeyHeld(SDL_SCANCODE_BACKSPACE)) {
        gameScale = 1;
        worldRotation = 0;
    }
    players[0].velocity.x *= 0.8;
    players[0].velocity.y *= 0.8;
}

void playerFrameUpdate () {
    playerUpdateStats(&players);
    playerFrameInput(&players);
}

void playerRender () {
    playerRect = makeRect((int)players[0].screenCoords.x, (int)players[0].screenCoords.y, (int)players[0].size.x, (int)players[0].size.y);

    SDL_RenderCopy(windows[0].renderer, texture, NULL, &playerRect);
}

void playerUpdateStats (Player* player[]) {
    for (int i = 0; i < numberOfPlayers; i++) {
        if (mainCamera.isStill) {
            players[0].screenCoords.x += players[0].velocity.x;
        }
        else {
            mainCamera.coords.x += players[0].velocity.x;
            mainCamera.coords.y -= players[0].velocity.y;
        }
    }
    // printf("Velocity: %lf\n", players[0].velocity.x);
}

void playerGravity (Player* player[]) {
    // if (mainCamera.coords.y < 1500) {
    //     players[0].velocity.y += players[0].gravity;
    // }
    // if (mainCamera.coords.y > 1500) {
    //     players[0].velocity.y = 0;
    // }
}

void playerJump (Player* player[]) {
    if (players[0].pressed.jump && players[0].velocity.y == 0) {
        players[0].velocity.y -= players[0].jumpPower;
        players[0].pressed.jump = false;
    }
}

void playerFrameInput (Player* player[]) {
    for (byte i = 0; i < numberOfPlayers; i++) {
        player[i]->size.x = DEFAULT_TILE_SIZE * gameScale;
        player[i]->size.y = DEFAULT_TILE_SIZE * gameScale;

        // player[i]->screenCoords.x = (windows[0].size.x/2) - player[i]->size.x/2;
        // player[i]->screenCoords.y = (windows[0].size.y/2) - player[i]->size.y/2;

        if (player[i]->controlsEnabled) {
            //Up
            if (checkKeyHeld(SDL_SCANCODE_W)) player[i]->pressed.up = true;
            if (checkKeyReleased(SDL_SCANCODE_W)) player[i]->pressed.up = false;
            //Left
            if (checkKeyHeld(SDL_SCANCODE_A)) player[i]->pressed.left = true;
            if (checkKeyReleased(SDL_SCANCODE_A)) player[i]->pressed.left = false;
            //Down
            if (checkKeyHeld(SDL_SCANCODE_S)) player[i]->pressed.down = true;
            if (checkKeyReleased(SDL_SCANCODE_S)) player[i]->pressed.down = false;
            //Right
            if (checkKeyHeld(SDL_SCANCODE_D)) player[i]->pressed.right = true;
            if (checkKeyReleased(SDL_SCANCODE_D)) player[i]->pressed.right = false;
            //Jump
            if (checkKeyHeld(SDL_SCANCODE_SPACE)) player[i]->pressed.jump = true;
            if (checkKeyReleased(SDL_SCANCODE_SPACE)) player[i]->pressed.jump = false;
            //Pause
            if (checkKeyHeld(SDL_SCANCODE_ESCAPE)) player[i]->pressed.pause = true;
            if (checkKeyReleased(SDL_SCANCODE_ESCAPE)) player[i]->pressed.pause = false;

            //Still Camera
            if (checkKeyPressed(SDL_SCANCODE_C)) mainCamera.isStill = true;
            if (checkKeyPressed(SDL_SCANCODE_V)) mainCamera.isStill = false;

            //Fullscreen Toggle
            if (checkKeyPressed(SDL_SCANCODE_F11)) {
                windows[0].bordered = !windows[0].bordered;
                SDL_GetDisplayBounds(0, &windows[0].squareCoords);
                SDL_SetWindowSize(windows[0].window, windows[0].size.x, windows[0].size.y);
                SDL_SetWindowBordered(windows[0].window, !windows[0].bordered);
                if (!windows[0].bordered) {
                    SDL_SetWindowFullscreen(windows[0].window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                else {
                    SDL_SetWindowFullscreen(windows[0].window, 0);
                    SDL_SetWindowSize(windows[0].window, windows[0].defaultSize.x, windows[0].defaultSize.y);
                    SDL_SetWindowPosition(windows[0].window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }
            }
        }
        else {
            player[i]->pressed.up = false;
            player[i]->pressed.left = false;
            player[i]->pressed.down = false;
            player[i]->pressed.right = false;
            player[i]->pressed.jump = false;
            player[i]->pressed.pause = false;
        }
    }
}

#endif