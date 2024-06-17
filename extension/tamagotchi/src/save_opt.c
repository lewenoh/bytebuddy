//
// Created by xth23 on 14/06/24.
//

#include "../include/save_opt.h"
#include <string.h>
#include <ncurses.h>

const char *confirmation[] = {
        "------------------------------",
        " Are you sure you want to go? ",
        "                              ",
        "                              ",
        "    y: yes, save and quit     ",
        "    n: no, go back            ",
        "                              ",
        "                              ",
        "                              ",
        "------------------------------"
};

bool save_opt(int row, int col){
    int confirmation_cols = strlen(confirmation[0]);
    int confirmation_rows = sizeof(confirmation)/sizeof(confirmation[0]);

    int start_row = row/2 - confirmation_rows/2;
    int start_col = col/2 - confirmation_cols/2;

    for(int i = 0; i<confirmation_rows; i++) {
        mvprintw(start_row + i, start_col, "%s", confirmation[i]);
    }

    bool final_choice;
    int choice = getch();

    if (choice == 'y' || choice == 'Y') {
        final_choice = true;
    } else {
        final_choice = false;
    }

    return final_choice;

    // this function is the confirmation screen that
    // lets user choose whether or not they want to leave


}
