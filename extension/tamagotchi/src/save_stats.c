//
// Created by xth23 on 14/06/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/stats_def.h"
#include "../include/save_stats.h"
#define BUFFER_CAPACITY 100

void save_stats(struct stats *s) {
    // this function will save the stats of the tamagotchi
    // in the save file
    FILE *outputFile = fopen("savefile.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening savefile.");
        exit(1);
    }

    char charBuffer[BUFFER_CAPACITY];
    char tempAgeBuffer[BUFFER_CAPACITY];
    char tempHappyBuffer[BUFFER_CAPACITY];
    char tempFullBuffer[BUFFER_CAPACITY];
    time_t lastPlayed;

    int currIndex = 0;
    while (currIndex < 7) {
        switch (currIndex) {
            case 0:
                sprintf(tempFullBuffer, "%d", s->full);
                strcat(charBuffer, tempFullBuffer);
            break;
            case 1:
                sprintf(tempHappyBuffer, "%d", s->happy);
                strcat(charBuffer, tempHappyBuffer);
            break;
            case 2:
                sprintf(tempAgeBuffer, "%d", s->age);
                strcat(charBuffer, tempAgeBuffer);
            break;
            case 3:
                if (s->poop) {strcat(charBuffer, "TRUE");}
                else {strcat(charBuffer, "FALSE");}
            break;
            case 4:
                if (s->sick) {strcat(charBuffer, "TRUE");}
                else {strcat(charBuffer, "FALSE");}
            break;
            case 5:
                lastPlayed = time(NULL);
                strcat(charBuffer, ctime(&lastPlayed));
            break;
            case 6:
                strcat(charBuffer, ctime(&s->tamagotchi_birthday));
            break;
        }
        currIndex++;
        strcat(charBuffer, ",");
    }

    size_t charsWritten = fwrite(charBuffer, sizeof(char), strlen(charBuffer), outputFile);

    if (charsWritten < strlen(charBuffer)) {
        perror("Error writing to savefile.\n");
        exit(1);
    }

    fclose(outputFile);
}
