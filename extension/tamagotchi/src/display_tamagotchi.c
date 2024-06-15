#include "../include/display_tamagotchi.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

extern volatile int running;

const char *tamagotchi[2][8] = {
        {
                "     ******             ",
                "  ***      ***          ",
                "**+-- %%   ==**   ******",
                " ***+    -=++*  ++****  ",
                "***      +*-==*****     ",
                "***        **=***       ",
                " **++*++*++++**         ",
                "   *=- +-+              "
        },
        {
                "     ******             ",
                "  ***      ***          ",
                "**+-- --   ==**         ",
                " ***+    -=++*          ",
                "***      +*-==********  ",
                "***        **=** ++*****",
                " **++*++*++++**         ",
                "   *=- +-+              "
        }
};

void first_state(int row, int col, int tama_rows, int tama_cols) {
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row / 2 - tama_rows / 2 + i, col / 2 - tama_cols / 2, "%s", tamagotchi[0][i]);
    }
    refresh();
}

void second_state(int row, int col, int tama_rows, int tama_cols) {
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row / 2 - tama_rows / 2 + i, col / 2 - tama_cols / 2, "%s", tamagotchi[1][i]);
    }
    refresh();
}

void clear_frame(int row, int col, int tama_rows, int tama_cols) {
    int start_row = row / 2 - tama_rows / 2;
    int start_col = col / 2 - tama_cols / 2;
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(start_row + i, start_col, "%-*s", tama_cols, ""); // Clear the line with spaces
    }
    refresh();
}

void *display_tamagotchi(void *arg) {
    int tama_rows = sizeof(tamagotchi[0]) / sizeof(tamagotchi[0][0]);
    int tama_cols = strlen(tamagotchi[0][0]);

    int row, col;
    getmaxyx(stdscr, row, col);

    while(running) {
        clear_frame(row, col, tama_rows, tama_cols);
        first_state(row, col, tama_rows, tama_cols);
        refresh();
        usleep(500000); // 500 milliseconds delay

        clear_frame(row, col, tama_rows, tama_cols);
        second_state(row, col, tama_rows, tama_cols);
        refresh();
        usleep(500000); // 500 milliseconds delay
    }

    return NULL;
}