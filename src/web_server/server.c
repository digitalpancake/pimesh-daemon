#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_PENDING_CONNECTIONS 10

void start_socket() {
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
    if(bind(socket_file_descriptor, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        perror("Socket failed to bind to port");
        exit(EXIT_FAILURE);
    }

    if(listen(socket_file_descriptor, MAX_PENDING_CONNECTIONS) < 0) {
        perror("Socket failed to listen");
        exit(EXIT_FAILURE);
    }

    /*
     * Down here we need to accept incoming connections, client data and requests
     */
}

