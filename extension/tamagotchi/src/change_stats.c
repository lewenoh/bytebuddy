//
// Created by xth23 on 16/06/24.
//

#include "../include/stats_def.h"
#include "../include/change_stats.h"
#include "../include/character_profile.h"
#include "../include/pass_away.h"

// can delete
#include <ncurses.h>

extern volatile int sick_today;


void *change_stats(void *arg){

    ThreadArgs *args = (ThreadArgs *)arg;

    struct stats *s = args->s;
    struct tm previous_tm = args->previous_tm;

    time_t current_time = time(NULL);
    struct tm *current_tm = localtime(&current_time);

    if(current_tm->tm_min != previous_tm.tm_min) {
        if (current_tm->tm_min % default_profile.happy_dec == 0) {
            (s->happy <= 0) ? 0 : s->happy--;
        }

        if (current_tm->tm_min % default_profile.full_dec == 0) {
            (s->full <= 0) ? 0 : s->full--;
        }
    }

    if (current_tm->tm_hour != previous_tm.tm_hour) {
        if( current_tm->tm_hour % default_profile.poop_frequency == 0) {
            s->poop = true;
        }
    }

    time_t time_since_last_played = difftime(current_time, s->time_last_played);
    if(!sick_today & (time_since_last_played > default_profile.sick_frequency)) {
        s->sick = TRUE;
        sick_today = TRUE;
    }

    if(s->age > default_profile.lifespan) {
        pass_away();
    }

    // for testing purposes only
    mvprintw(1, 2, "min: %d", current_tm->tm_min);
    mvprintw(2, 2, "second: %d", current_tm->tm_sec);
    mvprintw(2, 2, "hour: %d", current_tm->tm_hour);
    mvprintw(3, 2, "happy %d", s->happy);
    mvprintw(4, 2, "full %d", s->full);
    mvprintw(5, 2, "poop %d", s->poop);
}

// maybe make this a thread?
// delete initial_second later - for testing only
