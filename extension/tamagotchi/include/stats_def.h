//
// Created by xth23 on 14/06/24.
//

#ifndef EXTENSION_STATS_DEF_H
#define EXTENSION_STATS_DEF_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

struct stats {
    int full;
    int happy;
    int age;
    bool poop;
    bool sick;
    time_t time_last_played;
    time_t tamagotchi_birthday;
};

#endif //EXTENSION_STATS_DEF_H
