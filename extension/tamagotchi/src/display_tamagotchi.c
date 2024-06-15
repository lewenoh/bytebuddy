#include "../include/display_tamagotchi.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

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
/*

const char*menu[] = {
        "f: food        p: play  ",
        "m: med         t: toilet",
        "________________________",
        "s: stats   q: quit & save"
};

*/

void first_state(int row, int col, int tama_rows, int tama_cols) {
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row/2 - tama_rows/2 + i, col/2 - tama_cols/2, "%s", tamagotchi[0][i]);
    };
}

void second_state(int row, int col, int tama_rows, int tama_cols) {
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row/2 - tama_rows/2 + i, col/2 - tama_cols/2, "%s", tamagotchi[1][i]);
    };
}

void clear_frame(int row, int col, int tama_rows, int tama_cols) {
    row = row / 2 - tama_rows / 2;
    col = col / 2 - tama_cols / 2;
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row + i, col, "%s", "                        "); // Clear the line with spaces
    }
}

void *display_tamagotchi(void *arg) {
    int tama_rows = sizeof(tamagotchi[0]) / sizeof(tamagotchi[0][0]);
    int tama_cols = strlen(tamagotchi[0][0]);

/*    int menu_rows = sizeof(menu) / sizeof(menu[0]);
    int menu_cols = strlen(menu[0]);*/

    int row, col;
    getmaxyx(stdscr, row, col);
/*
    for (int i = 0; i < menu_rows; i++) {
        mvprintw((row * 0.75) + i, (col / 2 - menu_cols / 2), "%s", menu[i]);
    }*/

    refresh();

    while (1) {
        first_state(row, col, tama_rows, tama_cols);
        refresh();
        usleep(500000); // 500 milliseconds delay

        clear_frame(row, col, tama_rows, tama_cols);
        refresh();

        second_state(row, col, tama_rows, tama_cols);
        refresh();
        usleep(500000); // 500 milliseconds delay

        clear_frame(row, col, tama_rows, tama_cols);
        refresh();
    }
}