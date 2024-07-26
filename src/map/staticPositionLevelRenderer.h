#ifndef STATICPOSITIONLEVELRENDERER_H
#define STATICPOSITIONLEVELRENDERER_H

#include <math.h>

#include "../map/tiles.h"


void rotate_point (double angle, double *x, double *y);
void renderStaticLevel ();


void rotate_point (double angle, double *x, double *y) {
    double s = sin(angle);
    double c = cos(angle);

    //Rotate point
    double xnew = *x * c - *y * s;
    double ynew = *x * s + *y * c;

    //Translate point back:
    *x = xnew;
    *y = ynew;
}

void renderStaticLevel () {
    for (
        int x = ((mainCamera.coords.x)-(windows[0].size.x/2) > 0 ? ((mainCamera.coords.x)-(windows[0].size.x/2))/DEFAULT_TILE_SIZE : 0);
        x < ((mainCamera.coords.x/DEFAULT_TILE_SIZE) + ((windows[0].size.x/2)/DEFAULT_TILE_SIZE)+1 < staticLevelData.size.x ?
             (mainCamera.coords.x/DEFAULT_TILE_SIZE) + ((windows[0].size.x/2)/DEFAULT_TILE_SIZE)+1 : staticLevelData.size.x);
        x++
        ) {
        for (
            int y = ((mainCamera.coords.y)-(windows[0].size.y/2) > 0 ? ((mainCamera.coords.y)-(windows[0].size.y/2))/DEFAULT_TILE_SIZE : 0);
            y < ((mainCamera.coords.y/DEFAULT_TILE_SIZE) + ((windows[0].size.y/2)/DEFAULT_TILE_SIZE)+1 < staticLevelData.size.y ?
                 (mainCamera.coords.y/DEFAULT_TILE_SIZE) + ((windows[0].size.y/2)/DEFAULT_TILE_SIZE)+1 : staticLevelData.size.y);
            y++
        ) {
            for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
                if (staticLevelData.data[x][y] == tileID) {
                    double tileCenterX = ((x * DEFAULT_TILE_SIZE) * gameScale);
                    double tileCenterY = ((y * DEFAULT_TILE_SIZE) * gameScale);

                    rotate_point(worldRotation, &tileCenterX, &tileCenterY);

                    tiles[tileID].coords.x = (tileCenterX - tiles[tileID].size.x / 2);
                    tiles[tileID].coords.y = (tileCenterY - tiles[tileID].size.y / 2);

                    tiles[tileID].coords.x += (windows[0].size.x/2) - (mainCamera.coords.x * gameScale);  //Coords start at middle of screen
                    tiles[tileID].coords.y += (windows[0].size.y/2) - (mainCamera.coords.y * gameScale);

                    tiles[tileID].size.x =
                        (DEFAULT_TILE_SIZE * gameScale) +    //Default is 16
                        (fmod(gameScale, 1) == 0 ? 0 : 1) +  //Increase scale by 1 pixel if it is not a multiple of 1. Fixes render bug.
                        (gameScale < 1 ? 1 : 0) +                          //If gameScale is less than 1, add 1 pixel. Fixes render bug.
                        (worldRotation > 0 || worldRotation < 0 ? 1 : 0);      //If the world is rotated, add 1 pixel. Fixes render bug.

                    tiles[tileID].size.y =
                        (DEFAULT_TILE_SIZE * gameScale) +
                        (fmod(gameScale, 1) == 0 ? 0 : 1) +
                        (gameScale < 1 ? 1 : 0) +
                        (worldRotation > 0 || worldRotation < 0 ? 1 : 0);

                    SDL_Point rotationPoint = {tiles[tileID].size.x/2, tiles[tileID].size.y/2};
                    SDL_Rect tileRect = makeRect(tiles[tileID].coords.x, tiles[tileID].coords.y, tiles[tileID].size.x, tiles[tileID].size.y);
                    SDL_RenderCopyEx(windows[0].renderer, tiles[tileID].texture, NULL, &tileRect, worldRotation * 180/PI, &rotationPoint, SDL_FLIP_NONE);
                    break;
                }
            }
        }
    }
}

#endif