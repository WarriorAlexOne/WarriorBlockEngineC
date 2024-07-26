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
#include "../entity/camera.h"


typedef struct {
    bool up;
    bool left;
    bool down;
    bool right;
    bool jump;
    bool run;
    bool mining;
    bool placing;
} Controls;

typedef struct {
    bool up;
    bool left;
    bool down;
    bool right;
} Direction;

typedef struct {
    //IDs
    byte ID;

    //Controls
    Controls pressed;
    bool controlsEnabled;

    //Coordinates
    Vec2 coords;
    Vec2 size;
    Vec2 screenCoords;
    Vec2 screenTileCoords;

    //Speed
    Vec2 accel;
    Vec2 velocity;
    double gravity;

    //Stats
    bool isJumping;
    bool isFalling;

    //Collision
    Direction facing;
    Direction collided;
} Player;

//Global Buttons
bool fullscreen;
bool pause;
bool resetGame;
bool newBlankLevel;

Player* players;
byte numberOfPlayers = 1;

SDL_Rect playerRect;

SDL_Texture* texture;

bool playerInit = false;


void initPlayers ();
void playerTickUpdate ();
void playerFrameUpdate ();
void playerRender ();
void playerInput ();
void playerWalk ();
void updatePlayerStats ();
void playerCollision ();
void rotateWorld ();
void zoomCamera ();
void pauseGame ();
void setFullscreen ();
void resetStats ();


void initPlayers () {
    players = malloc(numberOfPlayers * sizeof(Player));
    for (int i = 0; i < numberOfPlayers; i++) {
        //IDs
        players[i].ID = i + 1;

        //Controls
        players[i].pressed.up = false;
        players[i].pressed.left = false;
        players[i].pressed.down = false;
        players[i].pressed.right = false;
        players[i].pressed.jump = false;
        players[i].pressed.run = false;
        players[i].controlsEnabled = true;

        //Coordinates
        players[i].coords.x = 0;
        players[i].coords.y = 0;
        players[i].size.x = DEFAULT_TILE_SIZE * gameScale;
        players[i].size.y = DEFAULT_TILE_SIZE * gameScale;
        players[i].screenCoords.x = 0;  //-1024*10
        players[i].screenCoords.y = 0;  //-1024*10
        players[i].screenTileCoords.x = 0;
        players[i].screenTileCoords.y = 0;


        //Speed
        players[i].accel.x = 1.25;
        players[i].accel.y = 1.25;
        players[i].velocity.x = 0;
        players[i].velocity.y = 0;
        players[i].gravity = 0.25;

        //Stats
        players[i].isJumping = false;
        players[i].isFalling = false;

        //Collision
        players[i].facing.up = false;
        players[i].facing.left = false;
        players[i].facing.down = false;
        players[i].facing.right = false;
        players[i].collided.up = false;
        players[i].collided.left = false;
        players[i].collided.down = false;
        players[i].collided.right = false;
    }
    addFrameFunction(playerFrameUpdate);
    addTickFunction(playerTickUpdate);

    //If 1 player, remove s from text.
    if (numberOfPlayers == 1) {
        printf("1 Player Initialized!\n");
    }
    else {
        printf("%i Players Initialized!\n", numberOfPlayers);
    }
}

void playerTickUpdate () {
    playerWalk();
    updatePlayerStats();
    playerCollision();
    rotateWorld();
    zoomCamera();
    pauseGame();
    setFullscreen();
}

void playerFrameUpdate () {
    playerRender();
    playerInput();
    resetStats();
}

void playerRender () {
    playerRect = makeRect((int)players[0].screenCoords.x, (int)players[0].screenCoords.y, (int)players[0].size.x, (int)players[0].size.y);

    SDL_RenderCopy(windows[0].renderer, texture, NULL, &playerRect);
    // SDL_SetRenderDrawColor(windows[0].renderer, 255, 0, 0, 255);
    // SDL_RenderFillRect(windows[0].renderer, &playerRect);
}

void playerInput () {
    for (int i = 0; i < numberOfPlayers; i++) {
        if (players[i].controlsEnabled) {
            //Up
            if (checkKeyHeld(SDL_SCANCODE_W)) players[i].pressed.up = true;
            if (checkKeyReleased(SDL_SCANCODE_W)) players[i].pressed.up = false;
            //Left
            if (checkKeyHeld(SDL_SCANCODE_A)) players[i].pressed.left = true;
            if (checkKeyReleased(SDL_SCANCODE_A)) players[i].pressed.left = false;
            //Down
            if (checkKeyHeld(SDL_SCANCODE_S)) players[i].pressed.down = true;
            if (checkKeyReleased(SDL_SCANCODE_S)) players[i].pressed.down = false;
            //Right
            if (checkKeyHeld(SDL_SCANCODE_D)) players[i].pressed.right = true;
            if (checkKeyReleased(SDL_SCANCODE_D)) players[i].pressed.right = false;
            //Jump
            if (checkKeyHeld(SDL_SCANCODE_SPACE)) players[i].pressed.jump = true;
            if (checkKeyReleased(SDL_SCANCODE_SPACE)) players[i].pressed.jump = false;
            //Run

            //Mining
            if (checkMouseHeld(MOUSE_LEFT)) players[0].pressed.mining = true;
            if (checkMouseReleased(MOUSE_LEFT)) players[0].pressed.mining = false;
            //Placing
            if (checkMousePressed(MOUSE_RIGHT)) {
                players[0].pressed.placing = true;
            }
            else if (players[0].pressed.placing) {
                players[0].pressed.placing = false;
            }
            //Fullscreen
            if (checkKeyPressed(SDL_SCANCODE_F11)) fullscreen = true;
            //Pause
            if (checkKeyPressed(SDL_SCANCODE_ESCAPE)) pause = !pause;
            //Reset Game
            if (checkKeyHeld(SDL_SCANCODE_BACKSPACE)) resetGame = true;
            if (checkKeyReleased(SDL_SCANCODE_BACKSPACE)) resetGame = false;
            //New Blank Level
            if (checkKeyPressed(SDL_SCANCODE_DELETE)) {
                newBlankLevel = true;
            }
            else if (newBlankLevel) {
                newBlankLevel = false;
            }
            //Still Camera
            if (checkKeyPressed(SDL_SCANCODE_C)) mainCamera.isStill = true;
            if (checkKeyPressed(SDL_SCANCODE_V)) mainCamera.isStill = false;
        }
        else {
            players[i].pressed.up = false;
            players[i].pressed.left = false;
            players[i].pressed.down = false;
            players[i].pressed.right = false;
            players[i].pressed.jump = false;
            pause = false;
        }
    }
}

void playerWalk () {
    if (players[0].pressed.left) {
        if (players[0].velocity.x > -100) {
            players[0].velocity.x -= players[0].accel.x;
        }
    }
    if (players[0].pressed.right) {
        if (players[0].velocity.x < 100) {
            players[0].velocity.x += players[0].accel.x;
        }
    }
    if (players[0].pressed.down) {
        if (players[0].velocity.y > -100) {
            players[0].velocity.y -= players[0].accel.x;
        }
    }
    if (players[0].pressed.up) {
        if (players[0].velocity.y < 100) {
            players[0].velocity.y += players[0].accel.x;
        }
    }
}

void updatePlayerStats () {
    // players[0].size.x = DEFAULT_TILE_SIZE * gameScale;
    // players[0].size.y = DEFAULT_TILE_SIZE * gameScale;

    // players[0].screenCoords.x = (windows[0].size.x/2) - players[0].size.x/2;
    // players[0].screenCoords.y = (windows[0].size.y/2) - players[0].size.y/2;
    players[0].screenTileCoords.x = (players[0].screenCoords.x / DEFAULT_TILE_SIZE) / gameScale;
    players[0].screenTileCoords.y = (players[0].screenCoords.y / DEFAULT_TILE_SIZE) / gameScale;
    if (mainCamera.isStill) {
        players[0].screenCoords.x += players[0].velocity.x;
        players[0].screenCoords.y -= players[0].velocity.y;
    }
    else {
        mainCamera.coords.x += players[0].velocity.x;
        mainCamera.coords.y -= players[0].velocity.y;
    }

    players[0].velocity.x *= 0.75;
    players[0].velocity.y *= 0.75;

    // printf("Scale: %f", gameScale);
}

int idffegjgrhiugre = 0;
void playerCollision () {
    if (checkCollision(players[0].screenCoords.x, players[0].screenCoords.y, players[0].size.x, players[0].size.y,500, 500, 200, 200)) {
        idffegjgrhiugre++;
        printf("COLLISION DETECTED!!! %i\n", idffegjgrhiugre);
    }
    // if (players[0].screenTileCoords.x + mainCamera.tileCoords.x + 1 == staticLevelData.data[(int)players[0].screenTileCoords.x + (int)mainCamera.tileCoords.x][(int)players[0].screenTileCoords.y]) {

    // }
}

void rotateWorld () {
    //Counter-Clockwise
    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_LEFTBRACKET)) {
        worldRotation -= 0.02;
        if (worldRotation < 0) {
            worldRotation += 6.28318530717958647692;
        }
    }
    else if (checkKeyHeld(SDL_SCANCODE_LEFTBRACKET)) {
        worldRotation -= 0.004;
        if (worldRotation < 0) {
            worldRotation += 6.28318530717958647692;
        }
    }

    //Clockwise
    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_RIGHTBRACKET)) {
        worldRotation += 0.02;
        if (worldRotation >= 6.28318530717958647692) {
            worldRotation -= 6.28318530717958647692;
        }
    }
    else if (checkKeyHeld(SDL_SCANCODE_RIGHTBRACKET)) {
        worldRotation += 0.004;
        if (worldRotation >= 6.28318530717958647692) {
            worldRotation -= 6.28318530717958647692;
        }
    }
}

void zoomCamera () {
    //Zoom In
    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_EQUALS)) {
        gameScale *= 1.015;
    }
    else if (checkKeyHeld(SDL_SCANCODE_EQUALS)) {
        gameScale *= 1.005;
    }

    //Zoom Out
    if (checkKeyHeld(SDL_SCANCODE_LSHIFT) && checkKeyHeld(SDL_SCANCODE_MINUS) && gameScale >= 0.1) {
        gameScale /= 1.015;
    }
    else if (checkKeyHeld(SDL_SCANCODE_MINUS) && gameScale >= 0.1) {
        gameScale /= 1.005;
    }
}

void pauseGame () {

}

void setFullscreen () {
    if (fullscreen) {
        fullscreen = false;
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

void resetStats () {
    if (resetGame) {
        gameScale = 1;
        worldRotation = 0;
    }
}

#endif