#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include "../map/proceduralChunkGenerator.h"


void renderChunks (int levelID);


void renderChunks (int levelID) {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
                if (chunkData[levelID][x][y] == tileID) {
                    tiles[tileID].tileDimensions.x = (x * DEFAULT_TILE_SIZE);
                    tiles[tileID].tileDimensions.y = (y * DEFAULT_TILE_SIZE);
                    tiles[tileID].tileDimensions.w = DEFAULT_TILE_SIZE;
                    tiles[tileID].tileDimensions.h = DEFAULT_TILE_SIZE;
                    SDL_RenderCopy(windows[0].renderer, tiles[tileID].texture, NULL, &tiles[tileID].tileDimensions);
                    break;
                }
            }
        }
    }
}

#endif