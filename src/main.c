#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <Raylib/raylib.h>
#include "WBE_Startup.h"
#include "Tests/Test_WBE_Math.h"
#include "WBE_Clock.h"

#include "WBE_Cleanup.h"

int main (int argc, char *argv[]) {
    WBE_Startup();
    
    InitWindow(800, 600, "Raylib in C!");
    SetTargetFPS(60);
    
    DisableCursor();

    // WBE_Clock* gameClock = WBE_CreateClock();
    Camera3D camera = { 0 };

    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };

    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    // bool running = true;
    while (!WindowShouldClose()) {
        // WBE_UpdateClock(gameClock);
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground((Color){0,0,255,255});

        BeginMode3D(camera);

        for (int i = 0; i < 10; i++) {
            DrawCube((Vector3){4-i+0.5, i+0.5, 0.5f}, 1.0f, 1.0f, 1.0f, RED);
            DrawCubeWires((Vector3){4-i+0.5, i+0.5, 0.5f}, 1.0f, 1.0f, 1.0f, BLACK);
        }
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }


    CloseWindow();
    WBE_Cleanup();
    return 0;
}
