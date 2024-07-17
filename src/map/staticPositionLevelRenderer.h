#ifndef STATICPOSITIONLEVELRENDERER_H
#define STATICPOSITIONLEVELRENDERER_H


void renderStaticLevel ();


void renderStaticLevel () {
    for (int x = 0; x < staticLevelData.size.x; x++) {
        for (int y = 0; y < staticLevelData.size.y; y++) {
            for (short tileID = 0; tileID <= numberOfTiles; tileID++) {
                if (staticLevelData.data[y][x] == tileID) {
                    tiles[tileID].tileDimensions.x = (windows[0].size.x/2) + (((x * DEFAULT_TILE_SIZE) - DEFAULT_TILE_SIZE/2) * gameScale);
                    tiles[tileID].tileDimensions.y = (windows[0].size.y/2) + (((y * DEFAULT_TILE_SIZE) - DEFAULT_TILE_SIZE/2) * gameScale);
                    tiles[tileID].tileDimensions.w = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    tiles[tileID].tileDimensions.h = (DEFAULT_TILE_SIZE * gameScale) + (fmod(gameScale, 1) == 0 ? 0 : 1) + (gameScale < 1 ? 1 : 0);
                    SDL_RenderCopy(windows[0].renderer, tiles[tileID].texture, NULL, &tiles[tileID].tileDimensions);
                    break;
                }
            }
        }
    }
}


#endif