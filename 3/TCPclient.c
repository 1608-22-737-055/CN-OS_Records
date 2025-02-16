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
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server's IP if not localhost
    
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }
    
    printf("\nConnected to the Server...\n");
    
    printf("\nEnter No. of Hours: ");
    scanf("%s", send_buffer1);
    if (write(sockfd, send_buffer1, strlen(send_buffer1) + 1) < 0) {
        perror("Write failed");
        close(sockfd);
        return 1;
    }
    
    printf("\nEnter Amount per Hour: ");
    scanf("%s", send_buffer2);
    if (write(sockfd, send_buffer2, strlen(send_buffer2) + 1) < 0) {
        perror("Write failed");
        close(sockfd);
        return 1;
    }
    
    if (read(sockfd, recv_buffer, sizeof(recv_buffer)) < 0) {
        perror("Read failed");
        close(sockfd);
        return 1;
    }
    
    printf("\nFrom Server: Total Salary: %s\n", recv_buffer);
    
    close(sockfd);
    return 0;
}
