#include "../include/display_tamagotchi.h"
#include "../animation/tamagotchi_frames.h"
#include "../animation/menu_frames.h"
#include "../animation/status_frames.h"
#include "../include/stats_def.h"
#include "../include/change_stats.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

extern volatile int running;

static void print_menu(int row, int col) {
    int menu_rows = sizeof(menu) / sizeof(menu[0]);
    int menu_cols = strlen(menu[0]);

    for (int i = 0; i < menu_rows; i++) {
        mvprintw((row - 2*(menu_rows)) + i, (col / 2 - menu_cols / 2), "%s", menu[i]);
    }
    refresh();
}

static void first_state(int row, int col, int tama_rows, int tama_cols) {
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row / 2 - tama_rows / 2 + i, col / 2 - tama_cols / 2, "%s", tamagotchi[0][i]);
    }
    refresh();
}

static void second_state(int row, int col, int tama_rows, int tama_cols) {
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row / 2 - tama_rows / 2 + i, col / 2 - tama_cols / 2, "%s", tamagotchi[1][i]);
    }
    refresh();
}

static void normal_state(int row, int col, int tama_rows, int tama_cols) {
    first_state(row, col, tama_rows, tama_cols);
    refresh();
    usleep(500000); // 500 milliseconds delay between frames

    //clear_frame(row, col, tama_rows, tama_cols);
    second_state(row, col, tama_rows, tama_cols);
    refresh();
    usleep(500000); // 500 milliseconds delay

}

static void print_poop(int row, int col, int tama_rows, int tama_cols) {
    int tama_end_row = (row/2) + tama_rows;
    int tama_end_col = col/2 + tama_cols;
    int poop_rows = sizeof(poop)/sizeof(poop[0]);
    int start_row = tama_end_row - poop_rows;
    int poop_cols = strlen(poop[0]);
    for( int i = 0; i < poop_rows; i++) {
        mvprintw(start_row + i, tama_end_col - poop_cols, "%s", poop[i]);
    }
}

static void print_sick(int row, int col, int tama_rows, int tama_cols) {
    int start_row = row/2 - tama_rows;
    int start_col = col/2 - tama_cols;
    int cross_rows = sizeof(cross)/sizeof(cross[0]);
    for( int i = 0; i < cross_rows; i++){
        mvprintw(start_row + i, start_col, "%s", cross[i]);
    }
    refresh();
}

static void clear_frame(int row, int col, int tama_rows, int tama_cols) {
    int start_row = row / 2 - tama_rows / 2;
    int start_col = col / 2 - tama_cols / 2;
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(start_row + i, start_col, "%-*s", tama_cols, ""); // Clear the line with spaces
    }
    refresh();
}

static void poop_animation(int row, int col, int tama_rows, int tama_cols) {
    first_state(row, col, tama_rows, tama_cols);
    refresh();
    sleep(1);
    second_state(row, col, tama_rows, tama_cols);
    refresh();
    usleep(250000);
    clear_frame(row, col, tama_rows, tama_cols);
    second_state(row, col+1, tama_rows, tama_cols+1);
    refresh();
    usleep(250000);
    clear_frame(row, col+1, tama_rows, tama_cols+1);
    second_state(row, col, tama_rows, tama_cols);
    refresh();
    usleep(250000);
    clear_frame(row, col, tama_rows, tama_cols);
    second_state(row, col+1, tama_rows, tama_cols+1);
    refresh();
    usleep(250000);
    clear_frame(row, col+1, tama_rows, tama_cols+1);
    second_state(row, col, tama_rows, tama_cols);
    refresh();
    usleep(500000);
    print_poop(row, col, tama_rows, tama_cols);
    refresh();
}

static void sick_state(int row, int col, int tama_rows, int tama_cols) {
    print_sick(row, col, tama_rows, tama_cols);
    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row / 2 - tama_rows / 2 + i, col / 2 - tama_cols / 2, "%s", tamagotchi[2][i]);
    }
    refresh();
    sleep(1);

    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row / 2 - tama_rows / 2 + i, col / 2 - tama_cols / 2, "%s", tamagotchi[3][i]);
    }
    refresh();
    usleep(500000);
}

bool previous_poop = false;

void *display_tamagotchi(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    struct stats *s = args->s;

    int tama_rows = sizeof(tamagotchi[0]) / sizeof(tamagotchi[0][0]);
    int tama_cols = strlen(tamagotchi[0][0]);

    int row, col;
    getmaxyx(stdscr, row, col);

    if((!previous_poop) && (s->poop == 1)) {
        poop_animation(row, col, tama_rows, tama_cols);
        mvprintw(0, col - 1, "%s", "pooped");
        previous_poop = true;
    }

    if(s->poop) {
        print_poop(row, col, tama_rows, tama_cols);
    } else {
        previous_poop = false;
    }

    print_menu(row, col);
    //clear_frame(row, col, tama_rows, tama_cols);
    if(s->sick) {
        //print_sick(row, col, tama_rows, tama_cols);
        sick_state(row, col, tama_rows, tama_cols);
    } else {
        normal_state(row, col, tama_rows, tama_cols);
    }

    return NULL;
}