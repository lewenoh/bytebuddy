//
// Created by xth23 on 14/06/24.
//

#include "../include/poop_opt.h"
#include "../include/stats_def.h"
#include <ncurses.h>
#include "../include/happy_emote.h"

void poop_opt(struct stats *s, int row, int col) {
        clear();

        // play cleaning emote

        s->poop = 0;
        happy_emote(row, col);
        refresh();
}
