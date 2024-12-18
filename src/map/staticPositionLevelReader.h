#ifndef STATICPOSITIONLEVELREADER_H
#define STATICPOSITIONLEVELREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    char levelName[128];
    Vec2_Int size;
    short** data;
    short** metaData;
} StaticLevel;

const char sLevelFilePath[32] = "staticLevels/level";
const char sBGLevelFilePath[32] = "staticLevels/bglevel";
const char sLevelFormat[8] = ".txt";

StaticLevel staticLevelData;
StaticLevel staticBGLevelData;

bool staticBGLevelEnabled = true;


void readLevel (int levelID);
void readBGLevel (int bgLevelID);
void generateBlankLevel ();
void generateBlankBGLevel ();


void readLevel (int levelID) {
    char levelPath[48];

    sprintf(levelPath, "%s%i%s", sLevelFilePath, levelID, sLevelFormat);

    FILE *file = fopen(levelPath, "r");
    if (file == NULL) {
        printf("Missing Level Data!\n");
        generateBlankLevel();
        fclose(file);
        return;
    }

    char line[1024*12];

    //Read Level Name (TODO: NEEDS SAFETY CHECKS)
    fgets(line, sizeof(line), file);  //Skips "LevelName:" Keyword
    fgets(line, sizeof(line), file);  //Reads LevelName String
    sscanf(line, "%127[^\n]", staticLevelData.levelName);  //Detects level string. Ends search after 127 chars, or newline.
    printf("LevelName: %s\n", staticLevelData.levelName);  //Temp debugging

    //Read Width (TODO: NEEDS SAFETY CHECKS)
    fgets(line, sizeof(line), file);  //Skips "Width:" Keyword
    fgets(line, sizeof(line), file);  //Reads Width Value
    sscanf(line, "%i", &staticLevelData.size.x);  //Assigns value to memory
    printf("LevelWidth: %i\n", staticLevelData.size.x);  //Temp debugging

    //Read Height (TODO: NEEDS SAFETY CHECKS)
    fgets(line, sizeof(line), file);  //Skips "Height:" Keyword
    fgets(line, sizeof(line), file);  //Reads Height Value
    sscanf(line, "%i", &staticLevelData.size.y);  //Assigns value to memory
    printf("LevelHeight: %i\n", staticLevelData.size.y);  //Temp debugging

    //Checks if Level Data is within X Bounds.
    if (staticLevelData.size.x >= 24 && staticLevelData.size.x <= 10000 && staticLevelData.size.y >= 14 && staticLevelData.size.y <= 10000) {

        //Expand X Coordinates to correct level size.
        staticLevelData.data = malloc(staticLevelData.size.x * sizeof(int*));
        staticLevelData.metaData = malloc(staticLevelData.size.x * sizeof(int*));

        //Expand Y Coordinates to correct size. Expands downwards from the X Coordinates.
        for (int i = 0; i < staticLevelData.size.x; ++i) {
            staticLevelData.data[i] = malloc(staticLevelData.size.y * sizeof(int));
            staticLevelData.metaData[i] = malloc(staticLevelData.size.y * sizeof(int));
        }

        fgets(line, sizeof(line), file);  //Skips "LevelData:" Keyword

        for (int y = 0; y < staticLevelData.size.y; ++y) {  //Checks every Y Coordinate (Starts with Y because X Data is all on 1 Y line).
            fgets(line, sizeof(line), file);  //Gets raw Data
            char* token = strtok(line, " ");  //Delimiter. Used to filter out unneeded data during processing.
                                              //Scans the current line, then cuts the raw data at the first piece of matching data.

            for (int x = 0; x < staticLevelData.size.x; ++x) {  //Checks every X coordinate for every Y coordinate.
                int data, metaData;  //Quick memory storage
                sscanf(token, "%d.%d", &data, &metaData);  //Processes "raw data" and stores "cooked data" to data & metaData.

                if (data >= 0 && data <= numberOfTiles) {  //Safety Check: If the data matches a tile ID, it is added to the loaded level.
                    staticLevelData.data[x][y] = data;
                    staticLevelData.metaData[x][y] = metaData;
                }
                else {  //Safety Check 2: If data does not match a tile ID, tile is set to 0 in the loaded level.
                    staticLevelData.data[x][y] = 0;
                    staticLevelData.metaData[x][y] = 0;
                }
                
                token = strtok(NULL, " ");  //Token is set to the next piece of data on the current line. (TODO: NEEDS SAFETY CHECKS)
            }
        }

        //Print Level Data
        // for (int y = 0; y < staticLevelData.size.y; ++y) {
        //     for (int x = 0; x < staticLevelData.size.x; ++x) {
        //         printf("%d.%d ", staticLevelData.data[x][y], staticLevelData.metaData[x][y]);
        //     }
        //     printf("\n");
        // }
    }
    else {
        if (staticLevelData.size.x < 24 && staticLevelData.size.y < 14) {
            printf("Invalid Level Size: (Width:%i, Height:%i)! Level must be between 24*14 and 10,000*10,000!\n", staticLevelData.size.x, staticLevelData.size.y);
        }
        else if (staticLevelData.size.x < 24) {
            printf("Invalid Level Width: %i! Level must be between 24*14 and 10,000*10,000!\n", staticLevelData.size.x);
        }
        else if (staticLevelData.size.y < 14) {
            printf("Invalid Level Height: %i! Level must be between 24*14 and 10,000*10,000!\n", staticLevelData.size.y);
        }
        generateBlankLevel();
    }

    // fgets(line, sizeof(line), file);


        // printf("%s", line);

        // if (strstr(line, "Width:")) {
        //     printf("Width Found!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        // }
        // sscanf(line, "Width:\n%d\n", &width);



    // printf("\n");

    fclose(file);

    // char str1[] = "Hello,world,this,is,a,test";
    // char *token;

    //Get the first token
    // token = strtok(str1, ",");

    //Get the rest of the tokens
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, ",");
    // }
}

void readBGLevel (int bgLevelID) {
    char bgLevelPath[48];

    sprintf(bgLevelPath, "%s%i%s", sBGLevelFilePath, bgLevelID, sLevelFormat);

    FILE *file = fopen(bgLevelPath, "r");
    if (file == NULL) {
        printf("Missing Background Level Data!\n");
        generateBlankBGLevel();
        fclose(file);
        return;
    }

    char line[1024*12];

    //Read Level Name (TODO: NEEDS SAFETY CHECKS)
    fgets(line, sizeof(line), file);  //Skips "LevelName:" Keyword
    fgets(line, sizeof(line), file);  //Reads LevelName String
    sscanf(line, "%127[^\n]", staticBGLevelData.levelName);  //Detects level string. Ends search after 127 chars, or newline.
    printf("LevelName: %s\n", staticBGLevelData.levelName);  //Temp debugging

    //Read Width (TODO: NEEDS SAFETY CHECKS)
    fgets(line, sizeof(line), file);  //Skips "Width:" Keyword
    fgets(line, sizeof(line), file);  //Reads Width Value
    sscanf(line, "%i", &staticBGLevelData.size.x);  //Assigns value to memory
    printf("LevelWidth: %i\n", staticBGLevelData.size.x);  //Temp debugging

    //Read Height (TODO: NEEDS SAFETY CHECKS)
    fgets(line, sizeof(line), file);  //Skips "Height:" Keyword
    fgets(line, sizeof(line), file);  //Reads Height Value
    sscanf(line, "%i", &staticBGLevelData.size.y);  //Assigns value to memory
    printf("LevelHeight: %i\n", staticBGLevelData.size.y);  //Temp debugging

    //Checks if Level Data is within X Bounds.
    if (staticBGLevelData.size.x >= 24 && staticBGLevelData.size.x <= 10000 && staticBGLevelData.size.y >= 14 && staticBGLevelData.size.y <= 10000) {

        //Expand X Coordinates to correct level size.
        staticBGLevelData.data = malloc(staticBGLevelData.size.x * sizeof(int*));
        staticBGLevelData.metaData = malloc(staticBGLevelData.size.x * sizeof(int*));

        //Expand Y Coordinates to correct size. Expands downwards from the X Coordinates.
        for (int i = 0; i < staticBGLevelData.size.x; ++i) {
            staticBGLevelData.data[i] = malloc(staticBGLevelData.size.y * sizeof(int));
            staticBGLevelData.metaData[i] = malloc(staticBGLevelData.size.y * sizeof(int));
        }

        fgets(line, sizeof(line), file);  //Skips "LevelData:" Keyword

        for (int y = 0; y < staticBGLevelData.size.y; ++y) {  //Checks every Y Coordinate (Starts with Y because X Data is all on 1 Y line).
            fgets(line, sizeof(line), file);  //Gets raw Data
            char* token = strtok(line, " ");  //Delimiter. Used to filter out unneeded data during processing.
                                              //Scans the current line, then cuts the raw data at the first piece of matching data.

            for (int x = 0; x < staticBGLevelData.size.x; ++x) {  //Checks every X coordinate for every Y coordinate.
                int data, metaData;  //Quick memory storage
                sscanf(token, "%d.%d", &data, &metaData);  //Processes "raw data" and stores "cooked data" to data & metaData.

                if (data >= 0 && data <= numberOfTiles) {  //Safety Check: If the data matches a tile ID, it is added to the loaded level.
                    staticBGLevelData.data[x][y] = data;
                    staticBGLevelData.metaData[x][y] = metaData;
                }
                else {  //Safety Check 2: If data does not match a tile ID, tile is set to 0 in the loaded level.
                    staticBGLevelData.data[x][y] = 0;
                    staticBGLevelData.metaData[x][y] = 0;
                }
                
                token = strtok(NULL, " ");  //Token is set to the next piece of data on the current line. (TODO: NEEDS SAFETY CHECKS)
            }
        }

        //Print Level Data
        // for (int y = 0; y < staticLevelData.size.y; ++y) {
        //     for (int x = 0; x < staticLevelData.size.x; ++x) {
        //         printf("%d.%d ", staticLevelData.data[x][y], staticLevelData.metaData[x][y]);
        //     }
        //     printf("\n");
        // }
    }
    else {
        if (staticBGLevelData.size.x < 24 && staticBGLevelData.size.y < 14) {
            printf("Invalid Level Size: (Width:%i, Height:%i)! Level must be between 24*14 and 10,000*10,000!\n", staticBGLevelData.size.x, staticBGLevelData.size.y);
        }
        else if (staticBGLevelData.size.x < 24) {
            printf("Invalid Level Width: %i! Level must be between 24*14 and 10,000*10,000!\n", staticBGLevelData.size.x);
        }
        else if (staticBGLevelData.size.y < 14) {
            printf("Invalid Level Height: %i! Level must be between 24*14 and 10,000*10,000!\n", staticBGLevelData.size.y);
        }
        generateBlankLevel();
    }

    // fgets(line, sizeof(line), file);


        // printf("%s", line);

        // if (strstr(line, "Width:")) {
        //     printf("Width Found!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        // }
        // sscanf(line, "Width:\n%d\n", &width);



    // printf("\n");

    fclose(file);

    // char str1[] = "Hello,world,this,is,a,test";
    // char *token;

    //Get the first token
    // token = strtok(str1, ",");

    //Get the rest of the tokens
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, ",");
    // }
}

void generateBlankLevel () {
    //If there is no level data, create new level.
    if (staticLevelData.data == NULL) {
        printf("Generating Blank Level...\n");
        staticLevelData.size.x = 24;
        staticLevelData.size.y = 14;

        //Create and Load Blank Level
        staticLevelData.data = malloc(staticLevelData.size.x * sizeof(int*));
        staticLevelData.metaData = malloc(staticLevelData.size.x * sizeof(int*));

        for (int x = 0; x < staticLevelData.size.x; x++) {
            staticLevelData.data[x] = malloc(staticLevelData.size.y * sizeof(int));
            staticLevelData.metaData[x] = malloc(staticLevelData.size.y * sizeof(int));
            for (int y = 0; y < staticLevelData.size.y; y++) {
                staticLevelData.data[x][y] = 0;
                staticLevelData.metaData[x][y] = 0;
            }
        }
    }
    //If there is level data, clear current level.
    else if (staticLevelData.data != NULL && staticLevelData.size.x >= 24 && staticLevelData.size.x <= 10000 && staticLevelData.size.y >= 14 && staticLevelData.size.y <= 10000) {
        printf("Clearing Level...\n");
        staticLevelData.size.x = 24;
        staticLevelData.size.y = 14;

        staticLevelData.data = realloc(staticLevelData.data, staticLevelData.size.x * sizeof(int*));
        staticLevelData.metaData = realloc(staticLevelData.metaData, staticLevelData.size.x * sizeof(int*));
        for (int x = 0; x < staticLevelData.size.x; x++) {
            staticLevelData.data[x] = realloc(staticLevelData.data[x], staticLevelData.size.y * sizeof(int));
            staticLevelData.metaData[x] = realloc(staticLevelData.metaData[x], staticLevelData.size.y * sizeof(int));
            for (int y = 0; y < staticLevelData.size.y; y++) {
                staticLevelData.data[x][y] = 0;
                staticLevelData.metaData[x][y] = 0;
            }
        }
    }
}

void generateBlankBGLevel () {
    //If there is no level data, create new level.
    if (staticBGLevelData.data == NULL) {
        printf("Generating Blank Level...\n");
        staticBGLevelData.size.x = 24;
        staticBGLevelData.size.y = 14;

        //Create and Load Blank Level
        staticBGLevelData.data = malloc(staticBGLevelData.size.x * sizeof(int*));
        staticBGLevelData.metaData = malloc(staticBGLevelData.size.x * sizeof(int*));

        for (int x = 0; x < staticBGLevelData.size.x; x++) {
            staticBGLevelData.data[x] = malloc(staticBGLevelData.size.y * sizeof(int));
            staticBGLevelData.metaData[x] = malloc(staticBGLevelData.size.y * sizeof(int));
            for (int y = 0; y < staticBGLevelData.size.y; y++) {
                staticBGLevelData.data[x][y] = 0;
                staticBGLevelData.metaData[x][y] = 0;
            }
        }
    }
    //If there is level data, clear current level.
    else if (staticBGLevelData.data != NULL && staticBGLevelData.size.x >= 24 && staticBGLevelData.size.x <= 10000 && staticBGLevelData.size.y >= 14 && staticBGLevelData.size.y <= 10000) {
        printf("Clearing Background Level...\n");
        staticBGLevelData.size.x = 24;
        staticBGLevelData.size.y = 14;

        staticBGLevelData.data = realloc(staticBGLevelData.data, staticBGLevelData.size.x * sizeof(int*));
        staticBGLevelData.metaData = realloc(staticBGLevelData.metaData, staticBGLevelData.size.x * sizeof(int*));
        for (int x = 0; x < staticLevelData.size.x; x++) {
            staticBGLevelData.data[x] = realloc(staticBGLevelData.data[x], staticBGLevelData.size.y * sizeof(int));
            staticBGLevelData.metaData[x] = realloc(staticBGLevelData.metaData[x], staticBGLevelData.size.y * sizeof(int));
            for (int y = 0; y < staticBGLevelData.size.y; y++) {
                staticBGLevelData.data[x][y] = 0;
                staticBGLevelData.metaData[x][y] = 0;
            }
        }
    }
}

#endif