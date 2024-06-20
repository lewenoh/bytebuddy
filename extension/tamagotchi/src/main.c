#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../include/display_tamagotchi.h"
#include "../include/welcome_screen.h"
#include "../include/food_opt.h"
#include "../include/select_menu.h"
#include "../include/stats_def.h"
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
    struct stats s = {5, 5, 3, TRUE, TRUE, boot_time, boot_time};

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
        display_tamagotchi(&args);

        //pthread_t tama_thread;
        //pthread_create(&tama_thread, NULL, display_tamagotchi, &args);
        //pthread_join(tama_thread, NULL);

        pthread_t change_stats_thread;
        pthread_create(&change_stats_thread, NULL, change_stats, &args);
        pthread_join(change_stats_thread, NULL);
        previous_tm = *localtime(&previous_time);
        
//        char optBuffer[10];
//        printf(optBuffer, opt);
//        if (strcmp(optBuffer, "f") < 0) {break;}
        int opt = getch();  // Non-blocking getch
        if (opt != ERR) {
            select_menu(&s, opt);
            // Clear input buffer to prevent backlog
            while ((opt = getch()) != ERR) {
                // Consume all characters in the input buffer
            }
        }
        refresh();
        // TODO handle message sending in case statement in select_menu.c
        // if (opt == 'm') { // Assuming 'm' key is used to send a message
            // char message[BUFFER_SIZE];
            // echo(); // Enable echo to get user input
            // mvprintw(LINES - 1, 0, "Enter message: ");
            // getstr(message);
            // noecho(); // Disable echo after getting input
            // char full_message[BUFFER_SIZE];
            // snprintf(full_message, BUFFER_SIZE, "%s: %s", name, message);
            // send_message(full_message);
            // mvprintw(LINES - 1, 0, ""); // Clear the message prompt
        }
    endwin();
    close(sock);
    return 0;
}

