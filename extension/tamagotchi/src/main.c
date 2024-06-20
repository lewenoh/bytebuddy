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

#define PORT 8080
#define BUFFER_SIZE 1024

int sock;
char name[50];
volatile int running = 1; // Define the shared variable
volatile bool sick_today = FALSE; // So that tama does not get sick more than once per day

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_read = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_read <= 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);
    }
    return NULL;
}

void send_message(char *message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
}

void initialize_network() {
    struct sockaddr_in serv_addr;

    printf("Enter your tamagotchi name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("146.169.53.134"); // configured to work host on oak14

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Connection Failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    pthread_t tid;
    pthread_create(&tid, NULL, receive_messages, NULL);
}

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

        pthread_t tama_thread;
        pthread_create(&tama_thread, NULL, display_tamagotchi, &args);
        pthread_join(tama_thread, NULL);

        pthread_t change_stats_thread;
        pthread_create(&change_stats_thread, NULL, change_stats, &args);
        pthread_join(change_stats_thread, NULL);
        previous_tm = *localtime(&previous_time);

        int opt = getch();
        select_menu(&s, opt);

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
    }

    getch(); // to close the program with any key
    endwin();
    close(sock);
    return 0;
}
