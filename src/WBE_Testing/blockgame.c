#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>
#include <SDL3/SDL.h>
#include "WBE/Util/WBE_Math.h"

// World Bounds
// #define WORLDX 16
// #define WORLDY 16
// #define WORLDZ 16

#define WORLD_SIZE 8
#define BLOCK_SIZE 1.0f

int*** blocks = NULL;

Mesh worldMesh = {0};
Texture2D blockTexture = {0};
Material blockMaterial = {0};


void MyMesh () {
    worldMesh.vertices = SDL_malloc(sizeof(float) * 18);
    worldMesh.texcoords = SDL_malloc(sizeof(float) * 12);

    // Verts
    // Tri 1
    worldMesh.vertices[0] = 0;
    worldMesh.vertices[1] = 0;
    worldMesh.vertices[2] = 0;

    worldMesh.vertices[3] = 1;
    worldMesh.vertices[4] = 0;
    worldMesh.vertices[5] = 0;

    worldMesh.vertices[6] = 1;
    worldMesh.vertices[7] = 1;
    worldMesh.vertices[8] = 0;

    // Tri 2
    worldMesh.vertices[9] = 1;
    worldMesh.vertices[10] = 1;
    worldMesh.vertices[11] = 0;

    worldMesh.vertices[12] = 0;
    worldMesh.vertices[13] = 1;
    worldMesh.vertices[14] = 0;

    worldMesh.vertices[15] = 0;
    worldMesh.vertices[16] = 0;
    worldMesh.vertices[17] = 0;

    // Texture Coords
    worldMesh.texcoords[0] = 0;
    worldMesh.texcoords[1] = 0;

    worldMesh.texcoords[2] = 1;
    worldMesh.texcoords[3] = 0;

    worldMesh.texcoords[4] = 1;
    worldMesh.texcoords[5] = 1;

    worldMesh.texcoords[6] = 1;
    worldMesh.texcoords[7] = 1;

    worldMesh.texcoords[8] = 0;
    worldMesh.texcoords[9] = 1;

    worldMesh.texcoords[10] = 0;
    worldMesh.texcoords[11] = 0;

    // Counts
    worldMesh.vertexCount = 6;
    worldMesh.triangleCount = 2;

    UploadMesh(&worldMesh, false);
}


int main () {
    InitWindow(1500, 900, "WBE Raylib Test");
    SetTargetFPS(60);

    // Initialize camera
    Camera3D camera = {0};
    camera.position = (Vector3){WORLD_SIZE/2, (WORLD_SIZE/2)+2, WORLD_SIZE/2};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Initialize world
    blocks = SDL_malloc(WORLD_SIZE * sizeof(int**));
    for (int x = 0; x < WORLD_SIZE; x++) {
        blocks[x] = SDL_malloc(WORLD_SIZE * sizeof(int*));
        for (int y = 0; y < WORLD_SIZE; y++) {
            blocks[x][y] = SDL_malloc(WORLD_SIZE * sizeof(int));
        }
    }

    // Set blocks up to half the world's height
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                if (y >= WORLD_SIZE/2) {
                    blocks[x][y][z] = 0;
                }
                else {
                    blocks[x][y][z] = 1;
                }
            }
        }
    }

    Vector3 worldSize = {WORLD_SIZE, WORLD_SIZE, WORLD_SIZE};

    // Create Cube Mesh
    // Texture2D cubeTexture = LoadTexture("assets/textures/tiles/titanium_block.png");
    // Model cubeModel = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
    // cubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cubeTexture;


    blockTexture = LoadTexture("assets/textures/tiles/titanium_block.png");

    blockMaterial = LoadMaterialDefault();
    blockMaterial.maps[MATERIAL_MAP_ALBEDO].texture = blockTexture;

    MyMesh();

    DisableCursor();


    // Game loop
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        // Get ray from the center of the screen
        Vector2 screenCenter = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
        Ray mouseRay = GetScreenToWorldRay(screenCenter, camera);

        // Find the closest hit block
        float minDistance = 1000.0f;
        int closestX = -1, closestY = -1, closestZ = -1;
        RayCollision closestHit;
        bool hasHit = false;

        // Check hit collision
        for (int x = 0; x < WORLD_SIZE; x++) {
            for (int y = 0; y < WORLD_SIZE; y++) {
                for (int z = 0; z < WORLD_SIZE; z++) {
                    if (blocks[x][y][z] == 1) {
                        Vector3 pos = {(float)x, (float)y, (float)z};
                        BoundingBox box = {
                            {pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f},
                            {pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f}
                        };
                        RayCollision hit = GetRayCollisionBox(mouseRay, box);
                        if (hit.hit && hit.distance < minDistance) {
                            minDistance = hit.distance;
                            closestX = x;
                            closestY = y;
                            closestZ = z;
                            closestHit = hit;
                            hasHit = true;
                        }
                    }
                }
            }
        }

        // Render world
        BeginDrawing();
        ClearBackground((Color){25, 51, 153, 255});
        BeginMode3D(camera);

        // // Draw textured cubes
        // for (int x = 0; x < WORLD_SIZE; x++) {
        //     for (int y = 0; y < WORLD_SIZE; y++) {
        //         for (int z = 0; z < WORLD_SIZE; z++) {

        //             // If block ID is 1, block is solid
        //             if (blocks[x][y][z] == 1) {
        //                 Vector3 pos = {(float)x, (float)y, (float)z};

        //                 // If player is facing a cube, color it red
        //                 if (hasHit && x == closestX && y == closestY && z == closestZ) {
        //                     DrawModel(cubeModel, pos, 1.0f, RED);
        //                 }
        //                 // All other cubes are normal color
        //                 else {
        //                     DrawModel(cubeModel, pos, 1.0f, WHITE);
        //                 }
        //             }
        //         }
        //     }
        // }

        DrawCube((Vector3){3, 3, 3}, 1, 1, 1, ORANGE);
        DrawMesh(worldMesh, blockMaterial, MatrixIdentity());

        EndMode3D();


        // Draw center reticle
        DrawRectangle(GetScreenWidth()/2-8, GetScreenHeight()/2-1, 16, 2, WHITE);
        DrawRectangle(GetScreenWidth()/2-1, GetScreenHeight()/2-8, 2, 16, WHITE);

        // Draw FPS and coords
        DrawFPS(10, 10);
        DrawText(TextFormat("Coords: (%.1f, %.1f, %.1f)", camera.position.x, camera.position.y, camera.position.z), 10, 30, 20, WHITE);
        EndDrawing();

        // Handle mouse clicks for destruction and placement
        if (hasHit) {
            // Destroy block
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                blocks[closestX][closestY][closestZ] = 0;
            }
            // Place block
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                Vector3 hitPos = {(float)closestX, (float)closestY, (float)closestZ};
                Vector3 newPos = Vector3Add(hitPos, closestHit.normal);
                // SDL_Log("closestHit normal: %f\n", closestHit.normal.x);
                int nx = (int)(newPos.x + 0.5f);
                int ny = (int)(newPos.y + 0.5f);
                int nz = (int)(newPos.z + 0.5f);
                if (nx >= 0 && nx < WORLD_SIZE && ny >= 0 && ny < WORLD_SIZE && nz >= 0 && nz < WORLD_SIZE) {
                    if (blocks[nx][ny][nz] == 0) {
                        blocks[nx][ny][nz] = 1;
                    }
                }
            }
        }
    }
}
