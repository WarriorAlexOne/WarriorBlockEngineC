#include <SDL2/SDL.h>

#include "../../include/util/clocks.h"
#include "../../include/main/window.h"
#include "../../include/main/rendering.h"


Renderer renderList[MAX_RENDER_COUNT];

void (*renderFunctions[MAX_RENDER_COUNT]) ();
int renderFunctionCount = 0;


void initRenderers () {
    for (int i = 0; i < MAX_RENDER_COUNT; i++) {
        renderList[i].id = -1;
    }
    addFrameFunction(updateRenderers);
    SDL_Log("Renderers Initialized!\n");
}

void updateRenderers () {
    for (int i = 0; i < renderFunctionCount; i++) {
        SDL_SetRenderDrawColor(windowList[i].renderer, 25, 51, 153, 255);
        SDL_RenderClear(windowList[i].renderer);
        renderFunctions[i]();
    }
    for (int i = 0; i < windowsAdded; i++) {
        SDL_RenderPresent(windowList[i].renderer);
    }
}

void addRenderFunction (int renderID, void (*function) ()) {
    if (renderID > MAX_RENDER_COUNT) {
        SDL_Log("ADD RENDER FUNCTION: Window ID value is above the max value! Please use a different ID or increase the MAX_WINDOW_COUNT limit. Current ID is: %i. Max value is: %i.\n", renderID, MAX_RENDER_COUNT);
        return;
    }
    if (renderID < 0) {
        SDL_Log("ADD RENDER FUNCTION: Render ID value is too low! Please use an available ID above 0. Current ID is: %i.\n", renderID);
        return;
    }
    if (renderList[renderID].id != -1) {
        SDL_Log("ADD RENDER FUNCTION: A Render Function with this ID has already been added! Please use a different ID. Current ID is: %i.\n", renderList[renderID].id);
        return;
    }
    renderList[renderID].id = renderID;
    renderList[renderID].function = function;
    renderFunctionCount++;
    SDL_Log("Renderer Added!\n");
    updateRenderPosition();
}

void swapRenderPosition (int id_1, int id_2) {
    if (id_1 > MAX_RENDER_COUNT) {
        SDL_Log("CHANGE RENDER POSITION: id_1 value is above the max value! Please use a different ID. Current ID is: %i.\n", id_1);
        return;
    }
    if (id_2 > MAX_RENDER_COUNT) {
        SDL_Log("CHANGE RENDER POSITION: id_2 value is above the max value! Please use a different ID. Current ID is: %i.\n", id_2);
        return;
    }
    if (id_1 < 0) {
        SDL_Log("CHANGE RENDER POSITION: id_1 value is too low! Please use an ID above 0. Current ID is: %i.\n", id_1);
        return;
    }
    if (id_2 < 0) {
        SDL_Log("CHANGE RENDER POSITION: id_2 value is too low! Please use an ID above 0. Current ID is: %i.\n", id_2);
        return;
    }
    if (renderList[id_1].id == -1) {
        SDL_Log("CHANGE RENDER POSITION: Render Function doesn't exist for id_1! Please add a Render Function with this ID first. Current ID is: %i\n", id_1);
        return;
    }
    if (renderList[id_2].id == -1) {
        SDL_Log("CHANGE RENDER POSITION: Render Function doesn't exist for id_2! Please add a Render Function with this ID first. Current ID is: %i\n", id_2);
        return;
    }
    void (*storeFunction) () = renderList[id_1].function;
    
    renderList[id_1].function = renderList[id_2].function;
    renderList[id_2].function = storeFunction;
    updateRenderPosition();
    SDL_Log("Render ID %i And %i Swapped!", id_1, id_2);
}

void updateRenderPosition () {
    int functionCount = 0;
    for (int i = 0; i < MAX_RENDER_COUNT; i++) {
        if (renderList[i].id == i) {
            renderFunctions[functionCount] = renderList[i].function;
            functionCount++;
        }
    }
    SDL_Log("Render Positions Updated!\n");
}
