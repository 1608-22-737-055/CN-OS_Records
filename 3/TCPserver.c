#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);
    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE], result[BUFFER_SIZE * 2];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept a connection
    if ((client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");

    // Read the first string
    if (read(client_fd, buffer1, BUFFER_SIZE) < 0) {
        perror("Failed to read first string");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Received first string: %s\n", buffer1);

    // Read the second string
    if (read(client_fd, buffer2, BUFFER_SIZE) < 0) {
        perror("Failed to read second string");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Received second string: %s\n", buffer2);

    // Concatenate strings
    snprintf(result, sizeof(result), "%s%s", buffer1, buffer2);
    printf("Concatenated result: %s\n", result);

    // Send concatenated result back to client
    if (write(client_fd, result, strlen(result)) < 0) {
        perror("Failed to send result");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Result sent to client.\n");

    // Close connections
    close(client_fd);
    close(server_fd);

    return 0;
}
