#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int sockfd, confd;
    struct sockaddr_in server_address, client_address;
    char buffer1[100], buffer2[100];
    socklen_t client_address_len;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = INADDR_ANY;

    printf("Waiting for Client request...\n");

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Socket binding failed");
        close(sockfd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(sockfd, 10) < 0) {
        perror("Socket listening failed");
        close(sockfd);
        return 1;
    }

    client_address_len = sizeof(client_address);

    // Accept client connection
    if ((confd = accept(sockfd, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        perror("Connection acceptance failed");
        close(sockfd);
        return 1;
    }
    printf("Client request accepted...\n");

    // Read data from client
    if (read(confd, buffer1, sizeof(buffer1)) <= 0) {
        perror("Failed to read data from client");
        close(confd);
        close(sockfd);
        return 1;
    }
    int nH = atoi(buffer1);
    printf("From Client: Number of Hours: %d\n", nH);

    if (read(confd, buffer2, sizeof(buffer2)) <= 0) {
        perror("Failed to read data from client");
        close(confd);
        close(sockfd);
        return 1;
    }
    int aH = atoi(buffer2);
    printf("From Client: Amount per Hour: %d\n", aH);

    // Calculate salary and send it to the client
    int salary = nH * aH;
    snprintf(buffer1, sizeof(buffer1), "%d", salary);
    if (write(confd, buffer1, strlen(buffer1)) <= 0) {
        perror("Failed to send data to client");
        close(confd);
        close(sockfd);
        return 1;
    }
    printf("Sent to Client: Total Salary: %s\n", buffer1);

    // Close connections
    close(confd);
    close(sockfd);
    return 0;
}
