//
// Created by xth23 on 14/06/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/stats_def.h"
#include "../include/load_stats.h"
#define BUFFER_CAPACITY 100

void load_stats(struct stats *s){
    // this function will edit the stats based on the txt savefile
    char charBuffer[BUFFER_CAPACITY];
    FILE *saveFile = fopen("savefile.txt", "r");

    if (saveFile == NULL || ferror(saveFile)) {
        fprintf(stderr, "Error opening save file.\n");
        exit(1);
        }

    if (fseek(saveFile, 0, SEEK_END) == -1) {
        fclose(saveFile);
        fprintf(stderr, "Error seeking to end of file.\n");
        exit(1); // seek failure
    }

    // now at end of file
    long fileSize = ftell(saveFile); // in bytes
    rewind(saveFile); // return to start

    int numChars = fread(charBuffer, sizeof(char), BUFFER_CAPACITY, saveFile);
    if (numChars < fileSize) {
        fclose(saveFile);
        fprintf(stderr, "Error reading from file.\n");
        }

    charBuffer[BUFFER_CAPACITY] = '\0'; // null-terminating the buffer

    int currIndex = 0;
    char *currStat = strtok(charBuffer, ",");
    while (currStat != NULL) {
        switch (currIndex) {
            case 0:
                s->happy = atoi(currStat);
                break;
            case 1:
                // TODO calculate age by age = number of days from birth until now
                // TODO use a aging factor to vary rate of aging
                break;
            case 2:
                if (strcmp(currStat,"TRUE")) {s->poop = true;}
                else {s->poop = false;}
                break;
            case 3:
                if (strcmp(currStat,"TRUE")) {s->sick = true;}
                else {s->sick = false;}
                break;
            case 4:
                // TODO figure out how to convert string to tm
                // struct tm time = mktime(s->time_last_played);
            case 5:

        }
        currIndex++;
        currStat = strtok(NULL, ",");
    // calculate age by age = number of days from birth until now
}
