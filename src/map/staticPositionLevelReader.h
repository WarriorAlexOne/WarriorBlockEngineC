#ifndef STATICPOSITIONLEVELREADER_H
#define STATICPOSITIONLEVELREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char levelName[128];
    Vec2_Int size;
    int** data;
    int** metaData;
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

    char line[256];

    //Read level name
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    sscanf(line, "%127[^\n]", staticLevelData.levelName);
    printf("%s\n", staticLevelData.levelName);

    //Read width
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    sscanf(line, "%i", &staticLevelData.size.x);
    printf("%i\n", staticLevelData.size.x);

    //Read height
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    sscanf(line, "%i", &staticLevelData.size.y);
    printf("%i\n", staticLevelData.size.y);

    if (staticLevelData.size.y <= 10000 && staticLevelData.size.y >= 14) {
        staticLevelData.data = malloc(staticLevelData.size.y * sizeof(int*));
        staticLevelData.metaData = malloc(staticLevelData.size.y * sizeof(int*));

        for (int i = 0; i < staticLevelData.size.y; ++i) {
            staticLevelData.data[i] = malloc(staticLevelData.size.x * sizeof(int));
            staticLevelData.metaData[i] = malloc(staticLevelData.size.x * sizeof(int));
        }

        //Read level data
        fgets(line, sizeof(line), file);

        for (int y = 0; y < staticLevelData.size.y; ++y) {
            fgets(line, sizeof(line), file);
            char* token = strtok(line, " ");

            for (int x = 0; x < staticLevelData.size.x; ++x) {
                int data, metaData;
                sscanf(token, "%d.%d", &data, &metaData);

                staticLevelData.data[y][x] = data;
                staticLevelData.metaData[y][x] = metaData;

                token = strtok(NULL, " ");
            }
        }

        //Print Level Data
        for (int y = 0; y < staticLevelData.size.y; ++y) {
            for (int x = 0; x < staticLevelData.size.x; ++x) {
                printf("%d.%d ", staticLevelData.data[y][x], staticLevelData.metaData[y][x]);
            }
            printf("\n");
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