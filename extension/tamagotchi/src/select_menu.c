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
#include "../include/send_chat.h"

#include <unistd.h>

extern volatile int running;

void select_menu(struct stats *s, int opt) {
    int row, col;
    getmaxyx(stdscr, row, col);

    nodelay(stdscr, FALSE);
    switch(opt) {
        case 'f':
            food_opt(s, row, col);
            break;

        case 'p':
            play_opt(s, row, col);
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
        case 'c':
            send_chat(row, col);
            clear();
            break;
        case 'q':
            bool choice = save_opt(row, col);
            if (choice) {
                save_stats(s);
                refresh();
                sleep(1); // Simulate saving
                running = 0; // Stop the loop
            } else {
                break;
            }
            break;

        default:
                break;
    }
    clear();
    nodelay(stdscr, TRUE);
}