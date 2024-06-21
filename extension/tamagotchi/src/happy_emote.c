#include "../include/happy_emote.h"
#include "../animation/tamagotchi_frames.h"
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
// happy emote is 5, 6

void happy_emote(int row, int col) {
    clear();
    int tama_rows = sizeof(tamagotchi[5])/sizeof(tamagotchi[5][0]);
    int tama_cols = strlen(tamagotchi[5][0]);
    int start_row = (row - tama_rows) / 2;
    int start_col = (col - tama_cols) / 2;

    for( int u = 0; u < 2; u++) {
        for( int i = 0; i < tama_rows; i++) {
            mvprintw(start_row + i, start_col, "%s", tamagotchi[5][i]);
        }
        refresh();
        usleep(500000);
        clear();

        for( int i = 0; i < tama_rows; i++) {
            mvprintw(start_row + i, start_col, "%s", tamagotchi[6][i]);
        }
        refresh();
        usleep(500000);
        clear();
    }
}
