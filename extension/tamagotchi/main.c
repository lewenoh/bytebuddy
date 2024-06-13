#include <stdio.h>
#include <ncurses.h>
#include "display_tamagotchi.h"
#include "welcome_screen.h"

int main(void) {
    int row, col;
    initscr();

    getmaxyx(stdscr, row, col); // finds centre of current terminal size

    welcome_screen(row, col);
    getch();
    clear();
    refresh();

    display_tamagotchi(row, col);
    refresh();
    getch(); // to close the program with any key
    endwin();
}
