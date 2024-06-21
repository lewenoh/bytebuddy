//
// Created by xth23 on 20/06/24.
//

#include "../include/send_chat.h"
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

#define BUFFER_SIZE 1024
#define PORT 8080
#define MAX_MESSAGES 100  // Maximum number of messages to store

char name[50];
char message_buffer[MAX_MESSAGES][BUFFER_SIZE];  // Buffer to store messages
int message_count = 0;  // Count of messages in buffer

// Function to refresh the chat window
void refresh_chat_window() {
    clear();  // Clear the screen
    int start = message_count - LINES + 2;  // Calculate starting message index
    if (start < 0) start = 0;  // Ensure start index is not negative
    int line = LINES - 3;  // Start printing from the second last line
    for (int i = message_count - 1; i >= start; i--) {
        mvprintw(line--, 0, "%s", message_buffer[i]);  // Print message
    }
    mvprintw(LINES - 2, 0, "Enter message: ");  // Prompt for new message
    refresh();  // Refresh the screen
}

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_read = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_read <= 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0';
        strncpy(message_buffer[message_count++], buffer, BUFFER_SIZE);  // Store received message
        if (message_count >= MAX_MESSAGES) {
            message_count = MAX_MESSAGES;  // Cap message count to max messages
            memmove(message_buffer, message_buffer + 1, (MAX_MESSAGES - 1) * BUFFER_SIZE);  // Shift messages up
        }
        refresh_chat_window();  // Refresh chat window to display new message
    }
    return NULL;
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

void send_message(char *message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    strncpy(message_buffer[message_count++], message, BUFFER_SIZE);  // Store sent message
    if (message_count >= MAX_MESSAGES) {
        message_count = MAX_MESSAGES;  // Cap message count to max messages
        memmove(message_buffer, message_buffer + 1, (MAX_MESSAGES - 1) * BUFFER_SIZE);  // Shift messages up
    }
    refresh_chat_window();  // Refresh chat window to display new message
}

void send_chat(int row, int col) {
    clear();
    char message[BUFFER_SIZE];
    echo(); // Enable echo to get user input
    mvprintw(LINES - 1, 0, "Press 'enter' key with no message to exit.");
    mvprintw(LINES - 2, 0, "Enter message: ");
    getstr(message);
    while (strcmp(message, "") != 0) {
        noecho(); // Disable echo after getting input
        char full_message[BUFFER_SIZE];
        snprintf(full_message, BUFFER_SIZE, "%s: %s", name, message);
        send_message(full_message);
        mvprintw(LINES - 1, 0, ""); // Clear the message prompt
        echo(); // Enable echo to get user input
        mvprintw(LINES - 2, 0, "Enter message: ");
        mvprintw(LINES - 1, 0, "Press 'enter' key with no message to exit.");
        getstr(message);
    }
    noecho();
}

/*

// extern int sock;
char name[50];


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


void send_message(char *message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
}

void send_chat(int row, int col) {
    clear();
    char message[BUFFER_SIZE];
    echo(); // Enable echo to get user input
    mvprintw(LINES - 1, 0, "Enter message: ");
    getstr(message);
    while (strcmp(message, "") != 0) {
        noecho(); // Disable echo after getting input
        char full_message[BUFFER_SIZE];
        snprintf(full_message, BUFFER_SIZE, "%s: %s", name, message);
        send_message(full_message);
        mvprintw(LINES - 1, 0, ""); // Clear the message prompt
        echo(); // Enable echo to get user input
        mvprintw(LINES - 1, 0, "Enter message: ");
        getstr(message);
    }

}
*/
