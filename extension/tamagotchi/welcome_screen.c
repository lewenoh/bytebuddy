//
// Created by Xi Ting Hoh on 13/06/2024.
//
#include "welcome_screen.h"
#include <ncurses.h>
#include <string.h>

const char *welcome_message[] = {
        "      Welcome to...        ",
        "    !!! TAMAGOTCHI !!!     ",
        "          yay :>           ",
        " Press any key to continue ",
};

void welcome_screen(int row, int col) {
    int welcome_rows = sizeof(welcome_message)/sizeof(welcome_message[0]);
    int welcome_cols = strlen(welcome_message[0]);

    // calculating window start x and y
    int startx = (row - welcome_rows) / 2;
    int starty = (col - welcome_cols) / 2;

    WINDOW *window = newwin(welcome_rows + 10, welcome_cols + 10, startx, starty);

    box(window, 0, 0);
    for (int i = 0; i<welcome_rows; i++) {
        mvwprintw(window, i + 1, 1, "%s", welcome_message[i]);
    }
    wrefresh(window);

    getch();

    // deleting the screen after player enters any key
    wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(window);

    delwin(window);
}

