#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_address;
    char send_buffer[100], recv_buffer[100];
    
    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server IP

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    printf("\nConnected to the Server...");
    
    // Input string to send
    printf("\nEnter a string: ");
    fgets(send_buffer, sizeof(send_buffer), stdin);
    send_buffer[strcspn(send_buffer, "\n")] = 0; // Remove trailing newline

    // Send string to server
    printf("\nSending to Server...");
    if (write(sockfd, send_buffer, strlen(send_buffer) + 1) < 0) {
        perror("Write failed");
        close(sockfd);
        return 1;
    }

    // Receive echo from server
    if (read(sockfd, recv_buffer, sizeof(recv_buffer)) < 0) {
        perror("Read failed");
        close(sockfd);
        return 1;
    }

    printf("\nFrom Server: '%s'\n", recv_buffer);

    // Close socket
    close(sockfd);
    return 0;
}
