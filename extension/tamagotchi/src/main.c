#include <stdio.h>
#include <ncurses.h>
#include <pthread.h> // this enables the tamagotchi idle animation
#include <unistd.h>
#include <string.h>
#include "../include/display_tamagotchi.h"
#include "../include/welcome_screen.h"
#include "../include/food_opt.h"

const char*menu[] = {
        "f: food        p: play  ",
        "m: med         t: toilet",
        "________________________",
        "s: stats   q: quit & save"
};

void print_menu(int row, int col) {

    int menu_rows = sizeof(menu) / sizeof(menu[0]);
    int menu_cols = strlen(menu[0]);

    for (int i = 0; i < menu_rows; i++) {
        mvprintw((row * 0.75) + i, (col / 2 - menu_cols / 2), "%s", menu[i]);
    }
    refresh();
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE); // disables use of cursor
    nodelay(stdscr, TRUE);

    pthread_t tama_thread;

    pthread_create(&tama_thread, NULL, display_tamagotchi, NULL);

    int row, col;
    getmaxyx(stdscr, row, col);

    print_menu(row, col);

    int opt;
    while ((opt = getch()) != 'q') {
        switch (opt) {
            case 'f':
                food_opt(row, col);
                print_menu(row, col); // Redraw menu after action
                break;
            case 'p':
                mvprintw(row / 2, col / 2 - 10, "Playing with Tamagotchi...");
                refresh();
                usleep(1000000); // Simulate playing
                clear();
                print_menu(row, col); // Redraw menu after action
                break;
            case 'm':
                mvprintw(row / 2, col / 2 - 10, "Giving medicine to Tamagotchi...");
                refresh();
                usleep(1000000); // Simulate giving medicine
                clear();
                print_menu(row, col); // Redraw menu after action
                break;
            case 't':
                mvprintw(row / 2, col / 2 - 10, "Tamagotchi is using the toilet...");
                refresh();
                usleep(1000000); // Simulate toilet use
                clear();
                print_menu(row, col); // Redraw menu after action
                break;
            case 's':
                mvprintw(row / 2, col / 2 - 10, "Displaying stats...");
                refresh();
                usleep(1000000); // Simulate displaying stats
                clear();
                print_menu(row, col); // Redraw menu after action
                break;
            default:
                break;
        }
    }

    pthread_join(tama_thread, NULL);
    pthread_cancel(tama_thread);

    getch(); // to close the program with any key
    endwin();
}
