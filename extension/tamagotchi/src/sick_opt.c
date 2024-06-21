#include "../include/sick_opt.h"
#include <ncurses.h>
#include "../include/happy_emote.h"

void sick_opt(struct stats *s, int row, int col) {
    clear();
    s->sick = 0;
    happy_emote(row, col);
    refresh();
}
