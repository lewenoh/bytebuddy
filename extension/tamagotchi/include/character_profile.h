//
// Created by xth23 on 16/06/24.
//

#ifndef TAMAGOTCHI_CHARACTER_PROFILE_H
#define TAMAGOTCHI_CHARACTER_PROFILE_H

typedef struct profile {
        int full_dec; // minutes between decrements to full
        int happy_dec; // minutes between decrements to happy
        int poop_frequency; // hours between poops
        int sick_frequency; // days between sickness
        int lifespan; // maximum lifespan
} profile;

struct profile default_profile = {
        10,
        15,
        12,
        6,
        12
};

#endif //TAMAGOTCHI_CHARACTER_PROFILE_H
