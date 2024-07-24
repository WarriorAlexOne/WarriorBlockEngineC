#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include "../map/proceduralChunkGenerator.h"


void renderChunks (int levelID);


void renderChunks (int levelID) {
    for (int x = 0; x <= levelWidth; x++) {
        for (int y = 0; y <= levelHeight; y++) {
            for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
                if (chunkData[levelID][x][y] == tileID) {
                    tiles[tileID].coords.x = (x * DEFAULT_TILE_SIZE);
                    tiles[tileID].coords.y = (y * DEFAULT_TILE_SIZE);
                    tiles[tileID].size.x = DEFAULT_TILE_SIZE;
                    tiles[tileID].size.y = DEFAULT_TILE_SIZE;
                    
                    tiles[tileID].rect = makeRect(tiles[tileID].coords.x, tiles[tileID].coords.y, tiles[tileID].size.x, tiles[tileID].size.y);
                    SDL_RenderCopy(windows[0].renderer, tiles[tileID].texture, NULL, &tiles[tileID].rect);
                    break;
                }
            }
        }
    }
}

#endif