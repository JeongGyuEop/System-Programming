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
    int server_queue, client_queue;

    // Create or get the server message queue
    server_queue = msgget(SERVER_QUEUE_KEY, 0666 | IPC_CREAT);
    if (server_queue == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Server: Waiting for client...\n");

    // Receive client's queue ID
    if (msgrcv(server_queue, &message, sizeof(message.message_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    client_queue = atoi(message.message_text);
    printf("Server: Connected to client.\n");

    // Start chat
    while (1) {
        printf("Server: Enter message ('exit' to quit): ");
        fgets(message.message_text, sizeof(message.message_text), stdin);
        message.message_type = 2;

        // Send message to client
        if (msgsnd(client_queue, &message, sizeof(message.message_text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        if (strncmp(message.message_text, "exit", 4) == 0) {
            break;
        }

        // Receive message from client
        if (msgrcv(server_queue, &message, sizeof(message.message_text), 2, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Client: %s", message.message_text);
    }

    // Clean up message queues
    msgctl(server_queue, IPC_RMID, NULL);
    msgctl(client_queue, IPC_RMID, NULL);

    return 0;
}

