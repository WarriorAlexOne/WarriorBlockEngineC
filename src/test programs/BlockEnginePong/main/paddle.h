#ifndef PADDLE_H
#define PADDLE_H

#include "../../../src/util/common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../../src/util/drawing_tools.h"
#include "../../../src/util/clocks.h"
#include "../../../src/main/window.h"
#include "../../../src/main/rendering.h"


typedef struct {
    double x;
    double y;
    double sizeX;
    double sizeY;
    double speed;
    bool up;
    bool down;
} Paddle;


Paddle paddle1;
Paddle paddle2;


void initPaddles ();
void updatePaddles ();
void renderUpdatePaddles ();


void initPaddles () {
    paddle1.sizeX = 20;
    paddle1.sizeY = 100;
    paddle1.x = 10;
    paddle1.y = (windowList[0].size.y/2) - paddle1.sizeY/2;
    paddle1.speed = 2;
    paddle1.up = false;
    paddle1.down = false;

    paddle2.sizeX = 20;
    paddle2.sizeY = 100;
    paddle2.x = windowList[0].size.x - paddle2.sizeX - 10;
    paddle2.y = (windowList[0].size.y/2) - paddle1.sizeY/2;
    paddle2.speed = 2;
    paddle2.up = false;
    paddle2.down = false;


    addFrameFunction(updatePaddles);
    addRenderFunction(1, renderUpdatePaddles);
    SDL_Log("Paddles Initialized!\n");
}

void updatePaddles () {
    paddle1.x = 10;
    paddle2.x = windowList[0].size.x - paddle2.sizeX - 10;
    if (checkKeyHeld(SDL_SCANCODE_W) && paddle1.y > 0) {
        paddle1.y -= (paddle1.speed * 60) * frameDelta;
        SDL_Log("Y: %f   Delta: %f\n", paddle1.y, frameDelta);
    }
    if (checkKeyHeld(SDL_SCANCODE_S) && paddle1.y < windowList[0].size.y) {
        paddle1.y += (paddle1.speed * 60) * frameDelta;
        SDL_Log("Y: %f   Delta: %f\n", paddle1.y, frameDelta);
    }
    if (paddle1.y < 0) {
        paddle1.y = 0;
    }
    if ((paddle1.y + paddle1.sizeY) > windowList[0].size.y) {
        paddle1.y = windowList[0].size.y - paddle1.sizeY;
    }

    if (checkKeyHeld(SDL_SCANCODE_UP) && paddle2.y > 0) {
        paddle2.y -= (paddle2.speed * 60) * frameDelta;
        SDL_Log("Y: %f   Delta: %f\n", paddle2.y, frameDelta);
    }
    if (checkKeyHeld(SDL_SCANCODE_DOWN) && paddle2.y < windowList[0].size.y) {
        paddle2.y += (paddle2.speed * 60) * frameDelta;
        SDL_Log("Y: %f   Delta: %f\n", paddle2.y, frameDelta);
    }
    if (paddle2.y < 0) {
        paddle2.y = 0;
    }
    if ((paddle2.y + paddle2.sizeY) > windowList[0].size.y) {
        paddle2.y = windowList[0].size.y - paddle2.sizeY;
    }
}

void renderUpdatePaddles () {
    drawRect(0, paddle1.x, paddle1.y, paddle1.sizeX, paddle1.sizeY, 255, 255, 255, 255);
    drawRect(0, paddle2.x, paddle2.y, paddle2.sizeX, paddle2.sizeY, 255, 255, 255, 255);
    drawRect(0, (windowList[0].size.x/2)-5, 0, 10, windowList[0].size.y, 255, 255, 255, 255);
}

#endif