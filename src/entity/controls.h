#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdio.h>

#include "../entity/player.h"


void initControls ();
void frameUpdateControls ();
void tickUpdateControls ();


void initControls () {
    addFrameFunction(frameUpdateControls);
    addTickFunction(tickUpdateControls);

    printf("Controls Initialized!\n");
}

void frameUpdateControls () {

}

void tickUpdateControls () {
    for (byte i = 0; i < numberOfPlayers; i++) {
        if (players[0].pressed.left) {
            if (players[0].velocity.x > -100) {
                players[0].velocity.x -= players[0].speed;
            }
        }
        if (players[0].pressed.right) {
            if (players[0].velocity.x < 100) {
                players[0].velocity.x += players[0].speed;
            }
        }
        if (players[0].pressed.down) {
            if (players[0].velocity.y > -100) {
                players[0].velocity.y -= players[0].speed;
            }
        }
        if (players[0].pressed.up) {
            if (players[0].velocity.y < 100) {
                players[0].velocity.y += players[0].speed;
            }
        }
    }
}

#endif