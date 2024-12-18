#include <SDL2/SDL.h>

#include "../../include/util/global_variables.h"
#include "../../include/main/window.h"
#include "../../include/util/drawing_tools.h"


void setColor (int windowID, ubyte r, ubyte g, ubyte b, ubyte a) {
    SDL_SetRenderDrawColor(windowList[windowID].renderer, r, g, b, a);
}

void drawRect (int windowID, double x, double y, double w, double h) {
    SDL_RenderFillRect(windowList[windowID].renderer, &(SDL_Rect){(int)x, (int)y, (int)w, (int)h});
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {   // Don't use. Just for fun.
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y) {
        // 8 symmetrical points of the circle
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void drawFilledCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {   // Don't use. Just for fun.
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}