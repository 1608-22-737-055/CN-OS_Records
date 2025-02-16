// Server Program
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int sockfd, confd;
    struct sockaddr_in server_address, client_address;
    char buffer[100];
    time_t t;

    time(&t);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create socket\n");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("\nWaiting for Client request......\n");

    if ((bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0) {
        printf("Could not bind socket\n");
        return 1;
    }

    if (listen(sockfd, 10) < 0) {
        printf("Could not open socket for listening\n");
        return 1;
    }

    int client_address_len = sizeof(client_address);
    if ((confd = accept(sockfd, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        printf("Could not open a socket to accept data\n");
        return 1;
    }

    printf("\nClient request Accepted......\n");
    strcpy(buffer, ctime(&t));

    if (write(confd, buffer, strlen(buffer)) < 0) {
        printf("Could not write data\n");
        return 1;
    }

    printf("\nSent to Client: '%s'\n", buffer);

    close(confd);
    close(sockfd);

    return 0;
}