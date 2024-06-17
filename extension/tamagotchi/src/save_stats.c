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
    char tempLPBuffer[BUFFER_CAPACITY];
    char tempBdayBuffer[BUFFER_CAPACITY];
    struct tm *lastPlayed;
    struct tm *birthday;

    memset(charBuffer, 0, sizeof(charBuffer)); // clearing buffer before use

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
                sprintf(tempAgeBuffer, "%d", s->age); // age doesn't have to be saved correctly as it is
                strcat(charBuffer, tempAgeBuffer);    // recalculated whenever load_stats is called.
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
                time_t currTime = time(NULL);
                lastPlayed = localtime(&currTime);
                lastPlayed->tm_year = lastPlayed->tm_year - 1900; // to ensure compatability with load_stats.
                lastPlayed->tm_mon = lastPlayed->tm_mon - 1; // to ensure compatability with load_stats.
                strftime(tempLPBuffer, sizeof(charBuffer), "%Y-%m-%d %H:%M:%S", lastPlayed);
                strcat(charBuffer, tempLPBuffer);
            break;
            case 6:
                birthday = localtime(&s->tamagotchi_birthday);
                birthday->tm_year = birthday->tm_year - 1900; // to ensure compatability with load_stats.
                birthday->tm_mon = birthday->tm_mon - 1; // to ensure compatability with load_stats.
                strftime(tempBdayBuffer, sizeof(charBuffer), "%Y-%m-%d %H:%M:%S", birthday);
                strcat(charBuffer, tempBdayBuffer);
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
