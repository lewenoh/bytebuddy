#include "../include/stats_opt.h"
#include "../include/stats_def.h"
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#define MAX_STAT 5
#define STAT_HAS_LEVEL "# "
#define STAT_NO_LEVEL ". "
#define STAT_DISPLAY_LENGTH 21
#define STAT_BAR_END_CHAR "|"

static void display_stat(int stat_level, char init_buffer[STAT_DISPLAY_LENGTH]) {
    // appends '#'
    for( int i = 0; i < stat_level; i ++){
        strcat( init_buffer, STAT_HAS_LEVEL);
    }

    // appends '.'
    for( int i = 0; i < (MAX_STAT - stat_level); i++) {
        strcat(init_buffer, STAT_NO_LEVEL);
    }

    strcat( init_buffer, STAT_BAR_END_CHAR);
}

static const char STAT_HEADER[STAT_DISPLAY_LENGTH] = "     statistics     ";
static const char STAT_BORDER[STAT_DISPLAY_LENGTH] = "--------------------";

void stats_opt(struct stats *s, int row, int col) {
    clear();
    int start_col = col/2 - STAT_DISPLAY_LENGTH/2;
    int start_row = row/2;

    char fullbuf[STAT_DISPLAY_LENGTH] = " Full  | ";
    char happybuff[STAT_DISPLAY_LENGTH] = " Happy | ";
    char agebuf[STAT_DISPLAY_LENGTH];
    snprintf(agebuf, STAT_DISPLAY_LENGTH, " Age    %d", s->age);
    display_stat(s->full, fullbuf);
    display_stat(s->happy, happybuff);

    mvprintw(start_row - 3, start_col, "%s", STAT_HEADER);
    mvprintw(start_row - 2, start_col, "%s", STAT_BORDER);
    mvprintw(start_row, start_col, "%s", fullbuf);
    mvprintw(start_row + 1, start_col, "%s", happybuff);
    mvprintw(start_row + 2, start_col, "%s", agebuf);
    mvprintw(start_row + 4, start_col, "%s", STAT_BORDER);
    refresh();
    sleep(2); // allows player to view stats before automatically closing in 2 seconds
}
