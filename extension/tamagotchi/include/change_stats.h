//
// Created by xth23 on 16/06/24.
//

#ifndef TAMAGOTCHI_CHANGE_STATS_H
#define TAMAGOTCHI_CHANGE_STATS_H

typedef struct {
    struct stats *s;
    struct tm previous_tm;
} ThreadArgs;

void *change_stats(void *args);

#endif //TAMAGOTCHI_CHANGE_STATS_H
