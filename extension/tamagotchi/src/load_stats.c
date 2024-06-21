#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/stats_def.h"
#include "../include/load_stats.h"
#define BUFFER_CAPACITY 100
#define AGING_FACTOR 10
#define SECS_IN_A_DAY 86400

extern void load_stats(struct stats *s) {
    // this function will edit the stats based on the txt savefile
    char charBuffer[BUFFER_CAPACITY];
    FILE *saveFile = fopen("../savefile.txt", "r");

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
    struct tm last_played;
    struct tm bday;

    while (currIndex < 7) {
        //printf("index: %d, currstat: %s\n", currIndex, currStat);
        switch (currIndex) {
            case 0:
                s->full = atoi(currStat);
                break;
            case 1:
                s->happy = atoi(currStat);
                break;
            case 3:
                if (strcmp(currStat,"TRUE") == 0) {s->poop = true;}
                else {s->poop = false;}
                break;
            case 4:
                if (strcmp(currStat,"TRUE") == 0) {s->sick = true;}
                else {s->sick = false;}
                break;
            case 5:
                memset(&last_played, 0, sizeof(struct tm)); // initialise fields of bday to zero
                // Example format: "YYYY-MM-DD HH:MM:SS"
                if (sscanf(currStat, "%d-%d-%d %d:%d:%d",
                    &last_played.tm_year, &last_played.tm_mon, &last_played.tm_mday,
                    &last_played.tm_hour, &last_played.tm_min, &last_played.tm_sec) != 6) {
                    fprintf(stderr, "Failed to parse time string: %s\n", currStat);
                    exit(1);
                }
                last_played.tm_hour = last_played.tm_hour - 1; // accounting for DST

                s->time_last_played = mktime(&last_played);
                break;
            case 6:
                memset(&bday, 0, sizeof(struct tm)); // initialise fields of bday to zero
                // Example format: "YYYY-MM-DD HH:MM:SS"
                if (sscanf(currStat, "%d-%d-%d %d:%d:%d",
                       &bday.tm_year, &bday.tm_mon, &bday.tm_mday,
                       &bday.tm_hour, &bday.tm_min, &bday.tm_sec) != 6) {
                    fprintf(stderr, "Failed to parse time string: %s\n", currStat);
                    exit(1);
                }
                bday.tm_hour = bday.tm_hour - 1; // accounting for DST

                s->tamagotchi_birthday = mktime(&bday);

                break;
        }
        currIndex++;
        currStat = strtok(NULL, ",");
    }
    // calculate age by age = number of days from birth until now * aging factor
    time_t currTime = time(NULL);
    int age = (int) (difftime(currTime, s->tamagotchi_birthday) * AGING_FACTOR / SECS_IN_A_DAY);
    // tamagotchi will age AGING_FACTOR years every day.
    s->age = age;

	fclose(saveFile);
}
