#ifndef STATICPOSITIONLEVELREADER_H
#define STATICPOSITIONLEVELREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char levelName[128];
    Vec2_Int size;
    short** data;
    short** metaData;
} staticLevel;

const char sLevelFilePath[32] = "src/map/staticLevels/level";
const char sLevelFormat[8] = ".txt";

staticLevel staticLevelData;


void readLevel (int levelID);


void readLevel (int levelID) {
    char levelPath[48];
    sprintf(levelPath, "%s%i%s", sLevelFilePath, levelID, sLevelFormat);

    FILE *file = fopen(levelPath, "r");
    if (file == NULL) {
        perror("Error opening file");
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
    if (staticLevelData.size.x <= 10000 && staticLevelData.size.x >= 24) {

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
        printf("Invalid Level Size! Must be 24x14 or bigger!");

        //Create and Load Blank Level
        staticLevelData.data = malloc(24 * sizeof(int*));
        staticLevelData.metaData = malloc(24 * sizeof(int*));

        for (int x = 0; x < 24; x++) {
            staticLevelData.data[x] = malloc(14 * sizeof(int));
            staticLevelData.metaData[x] = malloc(14 * sizeof(int));
            for (int y = 0; y < 14; y++) {
                staticLevelData.data[x][y] = 1;
                staticLevelData.metaData[x][y] = 1;
            }
        }
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

#endif