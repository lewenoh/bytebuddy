//
// Created by xth23 on 15/06/24.
//

#include "../include/select_menu.h"
#include <string.h>
#include <ncurses.h>

#include "../include/food_opt.h"
#include "../include/play_opt.h"
#include "../include/sick_opt.h"
#include "../include/poop_opt.h"
#include "../include/stats_opt.h"
#include "../include/save_opt.h"
#include "../include/save_stats.h"

#include <unistd.h>

extern volatile int running;

const char* menu[] = {
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

void* select_menu(void* arg) {
    int row, col;
    getmaxyx(stdscr, row, col);
    print_menu(row, col);

    while (running) {
        int opt = getch();
        if (opt != ERR) {
            switch(opt) {
                case 'f':
                    mvprintw(row - 2, 5, "%s", "food option");
                    refresh();
                    break;
                case 'p':
                    mvprintw(row - 2, 5, "%s", "play option");
                    refresh();
                    break;
                case 'm':
                    mvprintw(row - 2, 5, "%s", "sick option");
                    refresh();
                    break;
                case 't':
                    mvprintw(row - 2, 5, "%s", "poop option");
                    refresh();
                    break;
                case 's':
                    mvprintw(row - 2, 5, "%s", "statistics option");
                    refresh();
                    break;
                case 'q':
                    mvprintw(row - 2, 5, "%s", "Do you want to save? (y/n)");
                    refresh();
                    int dummy_opt = getch();
                    if (dummy_opt == 'y') {
                        mvprintw(row - 2, 5, "%s", "save stats - exit");
                        refresh();
                        sleep(1); // Simulate saving
                        running = 0; // Stop the loop
                    } else {
                        mvprintw(row - 2, 5, "%s", "cancel save");
                        refresh();
                    }
                    break;
                default:
                    mvprintw(row - 2, 5, "%s", "Invalid option");
                    refresh();
                    break;
            }
        }
    }
    return NULL;
}