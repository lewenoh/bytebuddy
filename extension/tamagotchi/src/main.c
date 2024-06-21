#include <string.h>
#include <pthread.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include "../include/display_tamagotchi.h"
#include "../include/food_opt.h"
#include "../include/select_menu.h"
#include "../include/change_stats.h"
#include "../include/load_stats.h"
#include "../include/send_chat.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int sock;
volatile int running = 1; // Define the shared variable
volatile bool sick_today = FALSE; // So that tama does not get sick more than once per day

int main(void) {
    initialize_network();

    time_t boot_time = time(NULL); // just a placeholder for the last two fields
    struct stats s = {0, 0, 0, FALSE, FALSE, boot_time, boot_time};

    load_stats(&s);

    initscr();
    cbreak();
    noecho();
    curs_set(FALSE); // disables use of cursor
    nodelay(stdscr, TRUE);

    // keeping track of time to change stats - snapshot of current time
    time_t previous_time = time(NULL);
    struct tm previous_tm = *localtime(&previous_time);

    while (running) {

        ThreadArgs args = {&s, previous_tm};
        // display_tamagotchi(&args);

        pthread_t tama_thread;
        pthread_create(&tama_thread, NULL, display_tamagotchi, &args);
        pthread_join(tama_thread, NULL);

        pthread_t change_stats_thread;
        pthread_create(&change_stats_thread, NULL, change_stats, &args);
        pthread_join(change_stats_thread, NULL);
        previous_tm = *localtime(&previous_time);

        int opt = getch();  // Non-blocking getch
        if (opt != ERR) {
            select_menu(&s, opt);
            // Clear input buffer to prevent backlog
            while ((opt = getch()) != ERR) {
                // Consume all characters in the input buffer
            }
        }
        refresh();
        }
    endwin();
    close(sock);
    return 0;
}

