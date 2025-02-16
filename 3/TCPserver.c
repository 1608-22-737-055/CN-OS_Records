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
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    printf("\nWaiting for client request...\n");
    
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }
    
    if (listen(sockfd, 10) < 0) {
        perror("Listen failed");
        close(sockfd);
        return 1;
    }
    
    socklen_t client_address_len = sizeof(client_address);
    if ((confd = accept(sockfd, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        perror("Accept failed");
        close(sockfd);
        return 1;
    }
    
    printf("\nClient request accepted...\n");
    
    if (read(confd, buffer1, sizeof(buffer1)) < 0) {
        perror("Read failed");
        close(confd);
        close(sockfd);
        return 1;
    }
    int nH = atoi(buffer1);
    printf("\nFrom Client: No. of Hours: %d\n", nH);
    
    if (read(confd, buffer2, sizeof(buffer2)) < 0) {
        perror("Read failed");
        close(confd);
        close(sockfd);
        return 1;
    }
    int aH = atoi(buffer2);
    printf("\nFrom Client: Amount per Hour: %d\n", aH);
    
    int Sal = nH * aH;
    snprintf(buffer1, sizeof(buffer1), "%d", Sal);
    
    if (write(confd, buffer1, sizeof(buffer1)) < 0) {
        perror("Write failed");
        close(confd);
        close(sockfd);
        return 1;
    }
    printf("\nSent to Client: %s\n", buffer1);
    
    close(confd);
    close(sockfd);
    return 0;
}
