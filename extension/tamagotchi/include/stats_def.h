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
    unsigned int full;
    unsigned int happy;
    unsigned int age;
    time_t time_last_played;
    unsigned int no_poops;
    bool sick;
};

#endif //EXTENSION_STATS_DEF_H
