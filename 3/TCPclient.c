#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_address;
    char string1[BUFFER_SIZE], string2[BUFFER_SIZE], result[BUFFER_SIZE * 2];

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost for testing

    // Connect to the server
    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection to server failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");

    // Get input strings
    printf("Enter the first string: ");
    scanf("%s", string1);
    printf("Enter the second string: ");
    scanf("%s", string2);

    // Send the first string
    if (write(client_fd, string1, strlen(string1)) < 0) {
        perror("Failed to send first string");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send the second string
    if (write(client_fd, string2, strlen(string2)) < 0) {
        perror("Failed to send second string");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Receive concatenated result
    if (read(client_fd, result, BUFFER_SIZE) < 0) {
        perror("Failed to receive result");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    result[BUFFER_SIZE - 1] = '\0'; // Ensure null termination
    printf("Concatenated result from server: %s\n", result);

    // Close connection
    close(client_fd);

    return 0;
}
