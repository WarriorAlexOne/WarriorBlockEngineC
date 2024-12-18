#ifndef RENDERING_H
#define RENDERING_H

#define MAX_RENDER_COUNT 128


typedef struct {
    int id;
    void (*function) ();
} Renderer;


void initRenderers ();
void updateRenderers ();
void addRenderFunction (int id, void (*function) ());
void swapRenderPosition (int id_1, int id_2);
void updateRenderPosition ();

#endif