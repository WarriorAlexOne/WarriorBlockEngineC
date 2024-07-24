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

                    tiles[tileID].coords.x += (windows[0].size.x/2) - (mainCamera.coords.x * gameScale);
                    tiles[tileID].coords.y += (windows[0].size.y/2) - (mainCamera.coords.y * gameScale);

                    tiles[tileID].size.x = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0) + (worldRotation > 0 || worldRotation < 0 ? 1 : 0);
                    tiles[tileID].size.y = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0) + (worldRotation > 0 || worldRotation < 0 ? 1 : 0);
                    SDL_Point rotationPoint = {tiles[tileID].size.x/2, tiles[tileID].size.y/2};

                    tiles[tileID].rect = makeRect(tiles[tileID].coords.x, tiles[tileID].coords.y, tiles[tileID].size.x, tiles[tileID].size.y);
                    SDL_RenderCopyEx(windows[0].renderer, tiles[tileID].texture, NULL, &tiles[tileID].rect, worldRotation * 180/PI, &rotationPoint, SDL_FLIP_NONE);
                    break;
                }
            }
        }
    }
}

// for (
//         int x = zoom + (cameraX >= zoom ? (((int)cameraX/DEFAULT_TILE_SIZE)/gameScale) : zoom);
//         int x = offset + (cameraX >= offset ? (((int)cameraX/DEFAULT_TILE_SIZE)/gameScale) : offset);
//         x <= (((windowW/DEFAULT_TILE_SIZE) + ((int)cameraX/DEFAULT_TILE_SIZE)) + 512 < levelWidth ?  //If edge of screen + camera offset is less than the level width in tiles
//                 ((windowW/DEFAULT_TILE_SIZE) + ((int)cameraX/DEFAULT_TILE_SIZE)) + 512 :  //If true, tile render limit is set to window edge + camera offset.
//                     levelWidth);  //If false (meaning window edge + camera offset is larger than the level), tile render is set to max level size.
//         x++
//         ) {
//         for (
//             int y = zoom + (cameraY >= zoom ? (((int)cameraY/DEFAULT_TILE_SIZE)/gameScale) : zoom);
//             int y = offset + (cameraY >= offset ? (((int)cameraY/DEFAULT_TILE_SIZE)/gameScale) : offset);
//             y <= (((windowH/DEFAULT_TILE_SIZE) + ((int)cameraY/DEFAULT_TILE_SIZE)) + 256 < levelHeight ?  //If edge of screen + camera offset is less than the level width in tiles
//                 ((windowH/DEFAULT_TILE_SIZE) + ((int)cameraY/DEFAULT_TILE_SIZE)) + 256 :  //If true, tile render limit is set to window edge + camera offset.
//                     levelHeight);  //If false (meaning window edge + camera offset is larger than the level), tile render is set to max level size.
//             y++
//             ) {
//             for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
//                 if (levelData[x][y] == tileID) {
//                     tiles[tileID].tileDimensions.x = ((x * DEFAULT_TILE_SIZE) * gameScale) - (int)cameraX;
//                     tiles[tileID].tileDimensions.y = ((y * DEFAULT_TILE_SIZE) * gameScale) - (int)cameraY;
//                     tiles[tileID].tileDimensions.x = ((x * DEFAULT_TILE_SIZE) * gameScale) - (cameraX*gameScale);
//                     tiles[tileID].tileDimensions.y = ((y * DEFAULT_TILE_SIZE) * gameScale) - (cameraY*gameScale);
//                     tiles[tileID].tileDimensions.w = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
//                     tiles[tileID].tileDimensions.h = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
//                     SDL_RenderCopy(renderer, tiles[tileID].texture, NULL, &tiles[tileID].tileDimensions);
//                     break;
//                 }
//             }
//         }
//     }
// }

#endif