#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define MAX_PENDING_CONNECTIONS 10
#define BUFFER_SIZE 104857600

void *handle_client(void *arg) {
    int client_file_descriptor = *((int *)arg);
    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

    // Receive request data from client and store into buffer
    ssize_t bytes_received = recv(client_file_descriptor, buffer,
                                  BUFFER_SIZE, 0);

    char* hello = "hello";
    send(client_file_descriptor, hello, strlen(hello), 0);

    free(arg);
    free(buffer);
}

void run_server() {
    int socket_file_descriptor;
    struct sockaddr_in socket_address;

    // Create a socket on IP v4, with TCP and the default protocol for the socket type
    if((socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the socket
    socket_address.sin_family = AF_INET; // Use IP v4
    socket_address.sin_addr.s_addr = INADDR_ANY; // Accepts connections from any server interface
    socket_address.sin_port = htons(PORT); // Set the port (in network byte order)

    // Bind the socket to the port
    if(bind(socket_file_descriptor, (struct sockaddr *)&socket_address, 
            sizeof(socket_address)) < 0) {
        perror("Socket failed to bind to port");
        exit(EXIT_FAILURE);
    }

    // Start listening
    if(listen(socket_file_descriptor, MAX_PENDING_CONNECTIONS) < 0) {
        perror("Socket failed to listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Client info
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int *client_file_descriptor = malloc(sizeof(int));

        // Accept client connection
        if ((*client_file_descriptor = accept(socket_file_descriptor, 
                                (struct sockaddr *)&client_address, 
                                &client_address_length )) < 0) {
            perror("accept failed");
            continue;
        }

        // Create a new thread to handle client request
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *)client_file_descriptor);
        pthread_detach(thread_id);
    }

    close(socket_file_descriptor);
}

