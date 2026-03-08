#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>
#include <SDL3/SDL.h>
#include "WBE/Util/WBE_Math.h"

// World Bounds
// #define WORLDX 16
// #define WORLDY 16
// #define WORLDZ 16

#define WORLD_SIZE 2
#define BLOCK_SIZE 1.0f

int*** blocks = NULL;

Mesh worldMesh = {0};
Texture2D blockTexture = {0};
Material blockMaterial = {0};


void MyMesh () {
    worldMesh.vertices = SDL_malloc((sizeof(float) * 18)*6);
    worldMesh.texcoords = SDL_malloc((sizeof(float) * 12)*6);

    // Quad 1
    // Tri 1
    worldMesh.vertices[0] = 0;
    worldMesh.vertices[1] = 0;
    worldMesh.vertices[2] = 0;

    worldMesh.vertices[3] = 0;
    worldMesh.vertices[4] = 1;
    worldMesh.vertices[5] = 0;

    worldMesh.vertices[6] = 1;
    worldMesh.vertices[7] = 1;
    worldMesh.vertices[8] = 0;

    // Tri 2
    worldMesh.vertices[9] = 1;
    worldMesh.vertices[10] = 1;
    worldMesh.vertices[11] = 0;

    worldMesh.vertices[12] = 1;
    worldMesh.vertices[13] = 0;
    worldMesh.vertices[14] = 0;

    worldMesh.vertices[15] = 0;
    worldMesh.vertices[16] = 0;
    worldMesh.vertices[17] = 0;

    // Texture Coords
    // Triangle 1
    worldMesh.texcoords[0] = 1;
    worldMesh.texcoords[1] = 1;

    worldMesh.texcoords[2] = 0;
    worldMesh.texcoords[3] = 1;

    worldMesh.texcoords[4] = 0;
    worldMesh.texcoords[5] = 0;

    // Triangle 2
    worldMesh.texcoords[6] = -1;
    worldMesh.texcoords[7] = -1;

    worldMesh.texcoords[8] = 0;
    worldMesh.texcoords[9] = -1;

    worldMesh.texcoords[10] = 0;
    worldMesh.texcoords[11] = 0;


    /////////////////////////////////////////////////////2
    // Quad 2
    // Tri 1
    worldMesh.vertices[18] = 0;
    worldMesh.vertices[19] = 0;
    worldMesh.vertices[20] = 0;

    worldMesh.vertices[21] = 0;
    worldMesh.vertices[22] = 0;
    worldMesh.vertices[23] = 1;

    worldMesh.vertices[24] = 0;
    worldMesh.vertices[25] = 1;
    worldMesh.vertices[26] = 1;

    // Tri 2
    worldMesh.vertices[27] = 0;
    worldMesh.vertices[28] = 1;
    worldMesh.vertices[29] = 1;

    worldMesh.vertices[30] = 0;
    worldMesh.vertices[31] = 1;
    worldMesh.vertices[32] = 0;

    worldMesh.vertices[33] = 0;
    worldMesh.vertices[34] = 0;
    worldMesh.vertices[35] = 0;

    // Texture Coords
    // Triangle 1
    worldMesh.texcoords[12] = 1;
    worldMesh.texcoords[13] = 0;

    worldMesh.texcoords[14] = 1;
    worldMesh.texcoords[15] = 1;

    worldMesh.texcoords[16] = 0;
    worldMesh.texcoords[17] = 1;

    // Triangle 2
    worldMesh.texcoords[18] = -1;
    worldMesh.texcoords[19] = 0;

    worldMesh.texcoords[20] = -1;
    worldMesh.texcoords[21] = -1;

    worldMesh.texcoords[22] = 0;
    worldMesh.texcoords[23] = -1;


    /////////////////////////////////////////////////////3
    // Quad 3
    // Tri 1
    worldMesh.vertices[36] = 0;
    worldMesh.vertices[37] = 1;
    worldMesh.vertices[38] = 1;

    worldMesh.vertices[39] = 0;
    worldMesh.vertices[40] = 0;
    worldMesh.vertices[41] = 1;

    worldMesh.vertices[42] = 1;
    worldMesh.vertices[43] = 1;
    worldMesh.vertices[44] = 1;

    // Tri 2
    worldMesh.vertices[45] = 1;
    worldMesh.vertices[46] = 0;
    worldMesh.vertices[47] = 1;

    worldMesh.vertices[48] = 1;
    worldMesh.vertices[49] = 1;
    worldMesh.vertices[50] = 1;

    worldMesh.vertices[51] = 0;
    worldMesh.vertices[52] = 0;
    worldMesh.vertices[53] = 1;

    // Texture Coords
    // Triangle 1
    worldMesh.texcoords[24] = 0;
    worldMesh.texcoords[25] = 0;

    worldMesh.texcoords[26] = 1;
    worldMesh.texcoords[27] = 0;

    worldMesh.texcoords[28] = 0;
    worldMesh.texcoords[29] = 1;

    // Triangle 2
    worldMesh.texcoords[30] = 0;
    worldMesh.texcoords[31] = 0;

    worldMesh.texcoords[32] = -1;
    worldMesh.texcoords[33] = 0;

    worldMesh.texcoords[34] = 0;
    worldMesh.texcoords[35] = -1;


    /////////////////////////////////////////////////////4
    // Quad 4
    // Tri 1
    worldMesh.vertices[54] = 1;
    worldMesh.vertices[55] = 0;
    worldMesh.vertices[56] = 1;

    worldMesh.vertices[57] = 1;
    worldMesh.vertices[58] = 0;
    worldMesh.vertices[59] = 0;

    worldMesh.vertices[60] = 1;
    worldMesh.vertices[61] = 1;
    worldMesh.vertices[62] = 1;

    // Tri 2
    worldMesh.vertices[63] = 1;
    worldMesh.vertices[64] = 1;
    worldMesh.vertices[65] = 0;

    worldMesh.vertices[66] = 1;
    worldMesh.vertices[67] = 1;
    worldMesh.vertices[68] = 1;

    worldMesh.vertices[69] = 1;
    worldMesh.vertices[70] = 0;
    worldMesh.vertices[71] = 0;

    // Texture Coords
    // Triangle 1
    worldMesh.texcoords[36] = 1;
    worldMesh.texcoords[37] = 0;

    worldMesh.texcoords[38] = 1;
    worldMesh.texcoords[39] = 1;

    worldMesh.texcoords[40] = 0;
    worldMesh.texcoords[41] = 0;

    // Triangle 2
    worldMesh.texcoords[42] = -1;
    worldMesh.texcoords[43] = 0;

    worldMesh.texcoords[44] = -1;
    worldMesh.texcoords[45] = -1;

    worldMesh.texcoords[46] = 0;
    worldMesh.texcoords[47] = 0;


    /////////////////////////////////////////////////////5
    // Quad 5
    // Tri 1
    worldMesh.vertices[72] = 1;
    worldMesh.vertices[73] = 1;
    worldMesh.vertices[74] = 0;

    worldMesh.vertices[75] = 0;
    worldMesh.vertices[76] = 1;
    worldMesh.vertices[77] = 0;

    worldMesh.vertices[78] = 1;
    worldMesh.vertices[79] = 1;
    worldMesh.vertices[80] = 1;

    // Tri 2
    worldMesh.vertices[81] = 0;
    worldMesh.vertices[82] = 1;
    worldMesh.vertices[83] = 1;

    worldMesh.vertices[84] = 1;
    worldMesh.vertices[85] = 1;
    worldMesh.vertices[86] = 1;

    worldMesh.vertices[87] = 0;
    worldMesh.vertices[88] = 1;
    worldMesh.vertices[89] = 0;

    // Texture Coords
    // Triangle 1
    worldMesh.texcoords[48] = 0;
    worldMesh.texcoords[49] = 1;

    worldMesh.texcoords[50] = 0;
    worldMesh.texcoords[51] = 0;

    worldMesh.texcoords[52] = 1;
    worldMesh.texcoords[53] = 1;

    // Triangle 2
    worldMesh.texcoords[54] = 0;
    worldMesh.texcoords[55] = -1;

    worldMesh.texcoords[56] = 0;
    worldMesh.texcoords[57] = 0;

    worldMesh.texcoords[58] = -1;
    worldMesh.texcoords[59] = -1;


    /////////////////////////////////////////////////////6
    // Quad 6
    // Tri 1
    worldMesh.vertices[90] = 0;
    worldMesh.vertices[91] = 0;
    worldMesh.vertices[92] = 0;

    worldMesh.vertices[93] = 1;
    worldMesh.vertices[94] = 0;
    worldMesh.vertices[95] = 0;

    worldMesh.vertices[96] = 1;
    worldMesh.vertices[97] = 0;
    worldMesh.vertices[98] = 1;

    // Tri 2
    worldMesh.vertices[99] = 1;
    worldMesh.vertices[100] = 0;
    worldMesh.vertices[101] = 1;

    worldMesh.vertices[102] = 0;
    worldMesh.vertices[103] = 0;
    worldMesh.vertices[104] = 1;

    worldMesh.vertices[105] = 0;
    worldMesh.vertices[106] = 0;
    worldMesh.vertices[107] = 0;

    // Texture Coords
    // Triangle 1
    worldMesh.texcoords[60] = 1;
    worldMesh.texcoords[61] = 1;

    worldMesh.texcoords[62] = 0;
    worldMesh.texcoords[63] = 1;

    worldMesh.texcoords[64] = 0;
    worldMesh.texcoords[65] = 0;

    // Triangle 2
    worldMesh.texcoords[66] = -1;
    worldMesh.texcoords[67] = -1;

    worldMesh.texcoords[68] = 0;
    worldMesh.texcoords[69] = -1;

    worldMesh.texcoords[70] = 0;
    worldMesh.texcoords[71] = 0;


    // Counts
    worldMesh.vertexCount = 6*6;
    worldMesh.triangleCount = 2*6;

    UploadMesh(&worldMesh, false);
}


int main () {
    InitWindow(1700, 1000, "WBE Raylib Test");
    SetTargetFPS(60);

    // Initialize camera
    Camera3D camera = {0};
    camera.position = (Vector3){WORLD_SIZE/2, (WORLD_SIZE/2)-2, WORLD_SIZE/2};
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

        // DrawCube((Vector3){0.5f, -0.5f, 0.5f}, 1, 1, 1, ORANGE);
        DrawMesh(worldMesh, blockMaterial, MatrixIdentity());

        EndMode3D();


        // Draw center reticle
        DrawRectangle(GetScreenWidth()/2-8, GetScreenHeight()/2-1, 16, 2, WHITE);
        DrawRectangle(GetScreenWidth()/2-1, GetScreenHeight()/2-8, 2, 16, WHITE);

        // Draw FPS and coords
        DrawFPS(10, 10);
        DrawText(TextFormat("Coords: (%.1f, %.1f, %.1f)", camera.position.x, camera.position.y, camera.position.z), 10, 30, 20, LIGHTGRAY);
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
