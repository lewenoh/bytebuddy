//
// Created by xth23 on 14/06/24.
//

#include "../include/food_opt.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../include/centre_helper.h"

int select_food_menu(int row, int col) {
     char *options[] = {
            "        1 - Burger        ",
            "        2 - Candy         ",
            "                          ",
            "Select an option from above"

    };
    // centre_helper(options, row, col);
    refresh();

    int food_opt = getch();

    return food_opt;

}

void food_opt(int centre_x, int centre_y) {

    int food_opt = select_food_menu(centre_x, centre_y);
    switch(food_opt) {
        case 1:
            mvprintw(centre_x, centre_y, "%s", "burger");
            refresh();
            return;

        case 2:
            mvprintw(centre_x, centre_y, "%s", "candy");
            refresh();
            return;

        default:
            return;
    }


    // this function will allow player to choose between food choices
    // this function will increment tamagotchi food by 1
    // and play the eating animation
}
