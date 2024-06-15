#include <stdio.h>
#include <ncurses.h>
#include <pthread.h> // this enables the tamagotchi idle animation
#include <unistd.h>
#include <string.h>
#include "../include/display_tamagotchi.h"
#include "../include/welcome_screen.h"
#include "../include/food_opt.h"
#include "../include/select_menu.h"
#include "../include/stats_def.h"

volatile int running = 1; // Define the shared variable

int main(void) {

    time_t boot_time = time(NULL); // just a placeholder for the last two fields
    struct stats s = { 0, 0, 0, FALSE, TRUE, boot_time, boot_time};

    // load_stats(&s)

    initscr();
    cbreak();
    noecho();
    curs_set(FALSE); // disables use of cursor
    nodelay(stdscr, TRUE);

    while(running){
        pthread_t tama_thread;
        pthread_create(&tama_thread, NULL, display_tamagotchi, NULL);
        pthread_join(tama_thread, NULL);
        //display_tamagotchi();

        int opt = getch();
        select_menu(&s, opt);
    }


    // pthread_create(&select_menu_thread, NULL, select_menu, NULL);


    // pthread_join(select_menu_thread, NULL);


    getch(); // to close the program with any key
    endwin();
    return 0;

    // TODO TOMORROW:
    // TRY MAKING BOTH DISPLAY TAMAGOTCHI AND SELECT MENU INTO WINDOWS
}