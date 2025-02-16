#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_address;
    char send_buffer1[100], send_buffer2[100], recv_buffer[100];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server IP if needed

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        return 1;
    }
    printf("Connected to the Server...\n");

    // Get input from user and send it to the server
    printf("Enter Number of Hours: ");
    scanf("%s", send_buffer1);
    if (write(sockfd, send_buffer1, strlen(send_buffer1)) <= 0) {
        perror("Failed to send data to server");
        close(sockfd);
        return 1;
    }

    printf("Enter Amount per Hour: ");
    scanf("%s", send_buffer2);
    if (write(sockfd, send_buffer2, strlen(send_buffer2)) <= 0) {
        perror("Failed to send data to server");
        close(sockfd);
        return 1;
    }

    // Receive response from server
    if (read(sockfd, recv_buffer, sizeof(recv_buffer)) <= 0) {
        perror("Failed to receive data from server");
        close(sockfd);
        return 1;
    }
    recv_buffer[strlen(recv_buffer)] = '\0';
    printf("From Server: Total Salary: %s\n", recv_buffer);

    // Close connection
    close(sockfd);
    return 0;
}
