//
// Created by xth23 on 14/06/24.
//

#include "../include/food_opt.h"
#include "../include/stats_def.h"
#include "../animation/tamagotchi_frames.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

static int select_food_menu(int row, int col) {
     char *options[] = {
            "        1 - Burger        ",
            "        2 - Candy         ",
            "                          ",
            "Select an option from above"

    };

    int options_rows = sizeof(options) / sizeof(options[0]);
    int options_cols = strlen(options[0]);

    int option_start_row = row * 0.75;
    for (int i = 0; i < options_rows; i++) {
        mvprintw(option_start_row + i, (col / 2 - options_cols / 2), "%s", options[i]);
    }

    int food_rows = sizeof(food_options[0])/sizeof(food_options[0][0]);
    int food_graphic_row = option_start_row - food_rows - 2;
    int burger_start_col = col/2 - strlen(food_options[0][0]) - 1;
    int candy_start_col = col/2 + 1;

    for( int i = 0; i < food_rows; i++) {
        mvprintw(food_graphic_row + i, candy_start_col, "%s", food_options[0][i]);
        mvprintw(food_graphic_row + i, burger_start_col, "%s", food_options[1][i]);
    }

    refresh();
    int food_opt = getch();
    return food_opt;
}

void food_opt(struct stats *s, int row, int col) {
    clear();
    int food_opt = select_food_menu(row, col);
    switch(food_opt) {
        case '1':
            clear();
            s->full > 5 ? 5 : s->full++;
            mvprintw(row/2, col/2, "%s", "burger");
            mvprintw(row/2 + 1, col/2, "full %u happy %u", s-> full, s->happy);
            refresh();
            sleep(1);
            nodelay(stdscr, TRUE);
            return;

        case '2':
            clear();
            s->happy > 5 ? 5 : s->happy++;
            mvprintw(row/2, col/2, "%s", "candy");
            mvprintw(row/2 + 1, col/2, "full %u happy %u", s-> full, s->happy);
            refresh();
            sleep(1);
            nodelay(stdscr, TRUE);
            return;

        default:
            mvprintw(row/2, col/2, "%s", "other");
            refresh();
            sleep(1);
            nodelay(stdscr, TRUE);
            return;
    }
}
