#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>
#include <SDL3/SDL.h>
#include "WBE/Util/WBE_Math.h"

// World Bounds
// #define WORLDX 16
// #define WORLDY 16
// #define WORLDZ 16

#define WORLD_SIZE 92
#define BLOCK_SIZE 1.0f

int*** blocks = NULL;

Mesh worldMesh = {0};
Texture2D blockTexture = {0};
Material blockMaterial = {0};

bool cullFaces = true;

bool worldIsBuilt = false;


bool CheckBlock (int*** world, int blockID, int x, int y, int z) {
    if (world[x][y][z] == blockID) {
        return true;
    }
    return false;
}

void MyMesh () {
    if (worldIsBuilt) {
        UnloadMesh(worldMesh);
        worldMesh = (Mesh){0};
    }
    int cubeVerts = 18;
    int cubeTexUVCoords = 12;

    // Stored cube data
    float quad1[18] = {0, 0, 0,  0, 1, 0,  1, 1, 0,    1, 1, 0,  1, 0, 0,  0, 0, 0};
    float quad1Tex[6] = {1, 1,  0, 1,  0, 0};

    float quad2[18] = {0, 0, 0,  0, 0, 1,  0, 1, 1,    0, 1, 1,  0, 1, 0,  0, 0, 0};
    float quad2Tex[6] = {1, 0,  1, 1,  0, 1};

    float quad3[18] = {0, 1, 1,  0, 0, 1,  1, 1, 1,    1, 0, 1,  1, 1, 1,  0, 0, 1};
    float quad3Tex[6] = {0, 0,  1, 0,  0, 1};

    float quad4[18] = {1, 0, 1,  1, 0, 0,  1, 1, 1,    1, 1, 0,  1, 1, 1,  1, 0, 0};
    float quad4Tex[6] = {1, 0,  1, 1,  0, 0};

    float quad5[18] = {1, 1, 0,  0, 1, 0,  1, 1, 1,    0, 1, 1,  1, 1, 1,  0, 1, 0};
    float quad5Tex[6] = {0, 1,  0, 0,  1, 1};

    float quad6[18] = {0, 0, 0,  1, 0, 0,  1, 0, 1,    1, 0, 1,  0, 0, 1,  0, 0, 0};
    float quad6Tex[6] = {1, 1,  0, 1,  0, 0};


    bool firstRun = true;
    int allFaceCount = 0;
    int vertCount = 0;
    int texCount = 0;
    for (int run = 0; run < 2; run++) {
        // SDL_Log("Running!");
        if (!firstRun) {
            SDL_Log("Face Count: %i", allFaceCount);
            worldMesh.vertices = SDL_malloc(((sizeof(float) * cubeVerts) * allFaceCount));
            worldMesh.texcoords = SDL_malloc(((sizeof(float) * cubeTexUVCoords) * allFaceCount));

            worldMesh.vertexCount = (6 * allFaceCount);
            worldMesh.triangleCount = (2 * allFaceCount);
        }
        for (int x = 0; x < WORLD_SIZE; x++) {
            for (int y = 0; y < WORLD_SIZE; y++) {
                for (int z = 0; z < WORLD_SIZE; z++) {
                    // X+ Face
                    if ((z == 0 && CheckBlock(blocks, 1, x, y, z)) || (CheckBlock(blocks, 1, x, y, z) && CheckBlock(blocks, 0, x, y, z-1 >= 0 ? z-1 : z))) {
                        if (firstRun) {
                            allFaceCount++;
                            goto face1Checked;
                        }
                        // SDL_Log("First Face!");
                        for (int verts = 0; verts < 6; verts++) { // Face 1
                            worldMesh.vertices[vertCount++] = quad1[verts*3]+x;
                            worldMesh.vertices[vertCount++] = quad1[(verts*3)+1]+y;
                            worldMesh.vertices[vertCount++] = quad1[(verts*3)+2]+z;
                        }

                        for (int verts = 0; verts < 3; verts++) { // Face 1
                            worldMesh.texcoords[texCount++] = quad1Tex[verts*2];
                            worldMesh.texcoords[texCount++] = quad1Tex[(verts*2)+1];
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 1
                            worldMesh.texcoords[texCount++] = -quad1Tex[verts*2];
                            worldMesh.texcoords[texCount++] = -quad1Tex[(verts*2)+1];
                        }
                    }

                    face1Checked:
                    // Z+ Face
                    if ((x == 0 && CheckBlock(blocks, 1, x, y, z)) || (CheckBlock(blocks, 1, x, y, z) && CheckBlock(blocks, 0, x-1 >= 0 ? x-1 : x, y, z))) {
                        if (firstRun) {
                            allFaceCount++;
                            goto face2Checked;
                        }
                        // SDL_Log("Second Face!");
                        for (int verts = 0; verts < 6; verts++) { // Face 2
                            worldMesh.vertices[vertCount++] = quad2[verts*3]+x;
                            worldMesh.vertices[vertCount++] = quad2[(verts*3)+1]+y;
                            worldMesh.vertices[vertCount++] = quad2[(verts*3)+2]+z;
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 2
                            worldMesh.texcoords[texCount++] = quad2Tex[verts*2];
                            worldMesh.texcoords[texCount++] = quad2Tex[(verts*2)+1];
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 2
                            worldMesh.texcoords[texCount++] = -quad2Tex[verts*2];
                            worldMesh.texcoords[texCount++] = -quad2Tex[(verts*2)+1];
                        }
                    }

                    face2Checked:
                    // X- Face
                    if ((z == WORLD_SIZE-1 && CheckBlock(blocks, 1, x, y, z)) || (CheckBlock(blocks, 1, x, y, z) && CheckBlock(blocks, 0, x, y, z+1 < WORLD_SIZE ? z+1 : z))) {
                        if (firstRun) {
                            allFaceCount++;
                            goto face3Checked;
                        }
                        // SDL_Log("Third Face!");
                        for (int verts = 0; verts < 6; verts++) { // Face 3
                            worldMesh.vertices[vertCount++] = quad3[verts*3]+x;
                            worldMesh.vertices[vertCount++] = quad3[(verts*3)+1]+y;
                            worldMesh.vertices[vertCount++] = quad3[(verts*3)+2]+z;
                        }

                        for (int verts = 0; verts < 3; verts++) { // Face 3
                            worldMesh.texcoords[texCount++] = quad3Tex[verts*2];
                            worldMesh.texcoords[texCount++] = quad3Tex[(verts*2)+1];
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 3
                            worldMesh.texcoords[texCount++] = -quad3Tex[verts*2];
                            worldMesh.texcoords[texCount++] = -quad3Tex[(verts*2)+1];
                        }
                    }

                    face3Checked:
                    // Z- Face
                    if ((x == WORLD_SIZE-1 && CheckBlock(blocks, 1, x, y, z)) || (CheckBlock(blocks, 1, x, y, z) && CheckBlock(blocks, 0, x+1 < WORLD_SIZE ? x+1 : x, y, z))) {
                        if (firstRun) {
                            allFaceCount++;
                            goto face4Checked;
                        }
                        // SDL_Log("Forth Face!");
                        for (int verts = 0; verts < 6; verts++) { // Face 4
                            worldMesh.vertices[vertCount++] = quad4[verts*3]+x;
                            worldMesh.vertices[vertCount++] = quad4[(verts*3)+1]+y;
                            worldMesh.vertices[vertCount++] = quad4[(verts*3)+2]+z;
                        }

                        for (int verts = 0; verts < 3; verts++) { // Face 4
                            worldMesh.texcoords[texCount++] = quad4Tex[verts*2];
                            worldMesh.texcoords[texCount++] = quad4Tex[(verts*2)+1];
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 4
                            worldMesh.texcoords[texCount++] = -quad4Tex[verts*2];
                            worldMesh.texcoords[texCount++] = -quad4Tex[(verts*2)+1];
                        }
                    }

                    face4Checked:
                    // Y+ Face
                    if ((y == WORLD_SIZE-1 && CheckBlock(blocks, 1, x, y, z)) || (CheckBlock(blocks, 1, x, y, z) && CheckBlock(blocks, 0, x, y+1 < WORLD_SIZE ? y+1 : y, z))) {
                        if (firstRun) {
                            allFaceCount++;
                            goto face5Checked;
                        }
                        // SDL_Log("Fifth Face!");
                        for (int verts = 0; verts < 6; verts++) { // Face 5
                            worldMesh.vertices[vertCount++] = quad5[verts*3]+x;
                            worldMesh.vertices[vertCount++] = quad5[(verts*3)+1]+y;
                            worldMesh.vertices[vertCount++] = quad5[(verts*3)+2]+z;
                        }

                        for (int verts = 0; verts < 3; verts++) { // Face 5
                            worldMesh.texcoords[texCount++] = quad5Tex[verts*2];
                            worldMesh.texcoords[texCount++] = quad5Tex[(verts*2)+1];
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 5
                            worldMesh.texcoords[texCount++] = -quad5Tex[verts*2];
                            worldMesh.texcoords[texCount++] = -quad5Tex[(verts*2)+1];
                        }
                    }

                    face5Checked:
                    // Y- Face
                    if ((y == 0 && CheckBlock(blocks, 1, x, y, z)) || (CheckBlock(blocks, 1, x, y, z) && CheckBlock(blocks, 0, x, y-1 >= 0 ? y-1 : y, z))) {
                        if (firstRun) {
                            allFaceCount++;
                            goto face6Checked;
                        }
                        // SDL_Log("Sixth Face!");
                        for (int verts = 0; verts < 6; verts++) { // Face 6
                            worldMesh.vertices[vertCount++] = quad6[verts*3]+x;
                            worldMesh.vertices[vertCount++] = quad6[(verts*3)+1]+y;
                            worldMesh.vertices[vertCount++] = quad6[(verts*3)+2]+z;
                        }

                        for (int verts = 0; verts < 3; verts++) { // Face 6
                            worldMesh.texcoords[texCount++] = quad6Tex[verts*2];
                            worldMesh.texcoords[texCount++] = quad6Tex[(verts*2)+1];
                        }
                        for (int verts = 0; verts < 3; verts++) { // Face 6
                            worldMesh.texcoords[texCount++] = -quad6Tex[verts*2];
                            worldMesh.texcoords[texCount++] = -quad6Tex[(verts*2)+1];
                        }
                    }
                    face6Checked:
                }
            }
        }
        firstRun = false;
    }
    // SDL_Log("Done!");

    UploadMesh(&worldMesh, false);
    worldIsBuilt = true;
}


int main () {
    InitWindow(1700, 1000, "WBE Raylib Test");
    SetTargetFPS(60);

    // Initialize camera
    Camera3D camera = {0};
    camera.position = (Vector3){WORLD_SIZE/2, (WORLD_SIZE/2)+2, WORLD_SIZE/2};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    // rlSetClipPlanes(0.0001, 1000000.0);

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

    blocks[1][1][1] = 0;

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
                            {pos.x, pos.y, pos.z},
                            {pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f}
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


        // Draw textured cubes
        for (int x = 0; x < WORLD_SIZE; x++) {
            for (int y = 0; y < WORLD_SIZE; y++) {
                for (int z = 0; z < WORLD_SIZE; z++) {

                    // If block ID is 1, block is solid
                    if (blocks[x][y][z] == 1) {
                        Vector3 pos = {(float)x, (float)y, (float)z+0.5f};

                        // If player is facing a cube, color it red
                        if (hasHit && x == closestX && y == closestY && z == closestZ) {
                            float outlineSize = 0.01f;

                            pos.x += 1;
                            DrawCube(pos, outlineSize, outlineSize, 1.0f+outlineSize, BLACK);
                            pos.y += 1;
                            DrawCube(pos, outlineSize, outlineSize, 1.0f+outlineSize, BLACK);
                            pos.x -= 1;
                            DrawCube(pos, outlineSize, outlineSize, 1.0f+outlineSize, BLACK);
                            pos.y -= 1;
                            DrawCube(pos, outlineSize, outlineSize, 1.0f+outlineSize, BLACK);
                            
                            pos.x += 0.5f;
                            pos.z += 0.5f;
                            DrawCube(pos, 1.0f+outlineSize, outlineSize, outlineSize, BLACK);
                            pos.y += 1;
                            DrawCube(pos, 1.0f+outlineSize, outlineSize, outlineSize, BLACK);
                            pos.z -= 1;
                            DrawCube(pos, 1.0f+outlineSize, outlineSize, outlineSize, BLACK);
                            pos.y -= 1;
                            DrawCube(pos, 1.0f+outlineSize, outlineSize, outlineSize, BLACK);

                            pos.x += 0.5f;
                            pos.y += 0.5f;
                            DrawCube(pos, outlineSize, 1.0f+outlineSize, outlineSize, BLACK);
                            pos.x -= 1;
                            DrawCube(pos, outlineSize, 1.0f+outlineSize, outlineSize, BLACK);
                            pos.z += 1;
                            DrawCube(pos, outlineSize, 1.0f+outlineSize, outlineSize, BLACK);
                            pos.x += 1;
                            DrawCube(pos, outlineSize, 1.0f+outlineSize, outlineSize, BLACK);
                        }
                    }
                }
            }
        }

        

        DrawCube((Vector3){0.5f, -0.5f, 0.5f}, 1, 1, 1, YELLOW);
        DrawCube((Vector3){1.5f, -0.5f, 0.5f}, 1, 1, 1, ORANGE);
        DrawCube((Vector3){2.5f, -0.5f, 0.5f}, 1, 1, 1, RED);
        DrawCube((Vector3){3.5f, -0.5f, 0.5f}, 1, 1, 1, MAGENTA);
        DrawCube((Vector3){4.5f, -0.5f, 0.5f}, 1, 1, 1, RED);

        DrawMesh(worldMesh, blockMaterial, MatrixIdentity());

        EndMode3D();


        // Draw center reticle
        DrawRectangle(GetScreenWidth()/2-8, GetScreenHeight()/2-1, 16, 2, WHITE);
        DrawRectangle(GetScreenWidth()/2-1, GetScreenHeight()/2-8, 2, 16, WHITE);

        // Draw FPS and coords
        DrawFPS(10, 10);
        DrawText(TextFormat("Coords: (%.1f, %.1f, %.1f)", camera.position.x, camera.position.y, camera.position.z), 10, 30, 20, LIGHTGRAY);
        DrawText("Titanium Block Texture By Dedede2!", 10, 50, 20, LIGHTGRAY);
        DrawText(TextFormat("World Size: %i", WORLD_SIZE), 10, 70, 20, LIGHTGRAY);
        
        EndDrawing();

        // Handle mouse clicks for destruction and placement
        if (hasHit) {
            // Destroy block
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                blocks[closestX][closestY][closestZ] = 0;
                MyMesh();
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
                MyMesh();
            }
        }
    }
}
