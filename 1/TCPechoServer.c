#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int sockfd, confd;
    struct sockaddr_in server_address, client_address;
    char buffer[100];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind socket
    printf("\nWaiting for client request...");
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    // Listen for client connections
    if (listen(sockfd, 10) < 0) {
        perror("Listen failed");
        close(sockfd);
        return 1;
    }

    // Accept client connection
    socklen_t client_address_len = sizeof(client_address);
    if ((confd = accept(sockfd, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        perror("Accept failed");
        close(sockfd);
        return 1;
    }

    printf("\nClient request accepted...");

    // Read data from client
    if (read(confd, buffer, sizeof(buffer)) < 0) {
        perror("Read failed");
        close(confd);
        close(sockfd);
        return 1;
    }

    printf("\nFrom Client: '%s'\n", buffer);

    // Echo data back to client
    if (write(confd, buffer, strlen(buffer) + 1) < 0) {
        perror("Write failed");
        close(confd);
        close(sockfd);
        return 1;
    }

    printf("\nSent to Client: '%s'\n", buffer);

    // Close connections
    close(confd);
    close(sockfd);
    return 0;
}
