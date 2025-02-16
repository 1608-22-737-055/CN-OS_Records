
// Client Program
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_address;
    char recv_buffer[100];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create socket\n");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0) {
        printf("Could not connect \n");
        return 1;
    }

    printf("\nConnected to the Server.........\n");

    if (read(sockfd, recv_buffer, sizeof(recv_buffer)) < 0) {
        printf("Could not read data\n");
        return 1;
    }

    printf("\nFrom Server Current Date And Time: '%s'\n", recv_buffer);

    close(sockfd);

    return 0;
}

