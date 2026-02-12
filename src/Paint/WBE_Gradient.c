#include "WBE/Paint/WBE_Gradient.h"

SDL_Texture* WBE_CreateGradient (SDL_Renderer* renderer, ubyte r1, ubyte g1, ubyte b1, ubyte r2, ubyte g2, ubyte b2) {
    float r_diff = r1 > r2 ? r1 - r2 : r2 - r1;
    float g_diff = g1 > g2 ? g1 - g2 : g2 - g1;
    float b_diff = b1 > b2 ? b1 - b2 : b2 - b1;

    float biggestDiff = 0;

    if (r_diff >= g_diff && r_diff >= b_diff) biggestDiff = r_diff;
    if (g_diff >= b_diff && g_diff >= r_diff) biggestDiff = g_diff;
    if (b_diff >= r_diff && b_diff >= g_diff) biggestDiff = b_diff;

    float r_steps = r_diff / biggestDiff;
    float g_steps = g_diff / biggestDiff;
    float b_steps = b_diff / biggestDiff;

    float r = r1;
    float g = g1;
    float b = b1;

    SDL_Surface* newGradient = SDL_CreateSurface(biggestDiff+1, 1, SDL_PIXELFORMAT_RGBA8888);
    for (int i = 0; i <= biggestDiff+1; i++) {
        SDL_WriteSurfacePixel(newGradient, i, 0, (int)r, (int)g, (int)b, 255);

        r += r1 > r2 ? -r_steps : r_steps;
        g += g1 > g2 ? -g_steps : g_steps;
        b += b1 > b2 ? -b_steps : b_steps;
    }

    SDL_Texture* finalGradient = SDL_CreateTextureFromSurface(renderer, newGradient);

    return finalGradient;
}
