#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_QUEUE_KEY 1234
#define CLIENT_QUEUE_KEY 5678
#define MAX_MESSAGE_SIZE 256

struct message_buffer {
    long message_type;
    char message_text[MAX_MESSAGE_SIZE];
};

int main() {
    struct message_buffer message;
    int client_queue, server_queue;

    // Create or get the client message queue
    client_queue = msgget(CLIENT_QUEUE_KEY, 0666 | IPC_CREAT);
    if (client_queue == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get the server message queue
    server_queue = msgget(SERVER_QUEUE_KEY, 0666);
    if (server_queue == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Send client's queue ID to the server
    sprintf(message.message_text, "%d", client_queue);
    message.message_type = 1;

    if (msgsnd(server_queue, &message, sizeof(message.message_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to server.\n");

    // Start chat
    while (1) {
        // Receive message from server
        if (msgrcv(client_queue, &message, sizeof(message.message_text), 2, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Server: %s", message.message_text);

        if (strncmp(message.message_text, "exit", 4) == 0) {
            break;
        }

        printf("Client: Enter message ('exit' to quit): ");
        fgets(message.message_text, sizeof(message.message_text), stdin);
        message.message_type = 1;

        // Send message to server
        if (msgsnd(server_queue, &message, sizeof(message.message_text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    // Clean up message queue
    msgctl(client_queue, IPC_RMID, NULL);

    return 0;
}

