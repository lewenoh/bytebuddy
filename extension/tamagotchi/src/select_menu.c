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
                stats_opt(s, row, col);
                refresh();
                break;
            case 'q':
                bool choice = save_opt(row, col);
                if (choice) {
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