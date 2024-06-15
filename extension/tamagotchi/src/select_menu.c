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

/*const char* menu[] = {
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
}*/

void select_menu(struct stats *s, int opt) {
    int row, col;
    getmaxyx(stdscr, row, col);
    int centre_x = row/2;
    int centre_y = col/2;


    if (opt != ERR) {
        nodelay(stdscr, FALSE);
        switch(opt) {
            case 'f':
                food_opt(s, row, col);
                break;

            case 'p':
                mvprintw(row - 2, 5, "%s", "play option");
                refresh();
                break;

            case 'm':
                sick_opt(s, row, col);
                refresh();
                break;

            case 't':
                poop_opt(s, row, col);
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
        sleep(1);
        clear();
    }
    nodelay(stdscr, TRUE);
}