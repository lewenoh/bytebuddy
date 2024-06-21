#include "../include/poop_opt.h"
#include <ncurses.h>
#include "../include/happy_emote.h"

void poop_opt(struct stats *s, int row, int col) {
        clear();
        s->poop = 0;
        happy_emote(row, col);
        refresh();
}
