#include <stdio.h>
#include <ncurses.h>
#include <pthread.h> // this enables the tamagotchi idle animation
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../include/display_tamagotchi.h"
#include "../include/welcome_screen.h"
#include "../include/food_opt.h"
#include "../include/select_menu.h"
#include "../include/stats_def.h"
#include "../include/change_stats.h"
#include "../include/load_stats.h"

volatile int running = 1; // Define the shared variable
volatile bool sick_today = FALSE; // So that tama does not get sick more than once per day

int main(void) {
    time_t boot_time = time(NULL); // just a placeholder for the last two fields
    struct stats s = { 5, 5, 3, TRUE, TRUE, boot_time, boot_time};

    load_stats(&s);

    initscr();
    cbreak();
    noecho();
    curs_set(FALSE); // disables use of cursor
    nodelay(stdscr, TRUE);

    // keeping track of time to change stats - snapshot of current time
    time_t previous_time = time(NULL);
    struct tm previous_tm = *localtime(&previous_time);


    while(running){
        ThreadArgs args = {&s, previous_tm};

        pthread_t tama_thread;
        pthread_create(&tama_thread, NULL, display_tamagotchi, &args);
        pthread_join(tama_thread, NULL);
        //display_tamagotchi();


        pthread_t change_stats_thread;
        pthread_create(&change_stats_thread, NULL, change_stats, &args);
        pthread_join(change_stats_thread, NULL);
        previous_tm = *localtime(&previous_time);

        int opt = getch();
        select_menu(&s, opt);
    }


    // pthread_create(&select_menu_thread, NULL, select_menu, NULL);


    // pthread_join(select_menu_thread, NULL);

    //save_stats(&s);


    getch(); // to close the program with any key
    endwin();
    return 0;

    // TODO TOMORROW:
    // TRY MAKING BOTH DISPLAY TAMAGOTCHI AND SELECT MENU INTO WINDOWS
}