//
// Created by xth23 on 14/06/24.
//

#include "../include/sick_opt.h"
#include <ncurses.h>

void sick_opt(struct stats *s, int row, int col) {
    clear();

    // play healing emote

    s->sick = 0;
    mvprintw(row/2 + 1, col/2, "sick %d", s->sick);
    refresh();
}
