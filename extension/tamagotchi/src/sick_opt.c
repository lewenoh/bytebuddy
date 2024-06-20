//
// Created by xth23 on 14/06/24.
//

#include "../include/sick_opt.h"
#include <ncurses.h>
#include "../include/happy_emote.h"

void sick_opt(struct stats *s, int row, int col) {
    clear();

    // play healing emote

    s->sick = 0;
    happy_emote(row, col);
    refresh();
}
