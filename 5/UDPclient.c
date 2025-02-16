#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    char s1[MAXLINE], s2[MAXLINE], s3[MAXLINE];

    printf("\nEnter S1 Marks: ");
    scanf("%s", s1);

    printf("\nEnter S2 Marks: ");
    scanf("%s", s2);

    printf("\nEnter S3 Marks: ");
    scanf("%s", s3);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    sendto(sockfd, (const char *)s1, strlen(s1), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, (const char *)s2, strlen(s2), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, (const char *)s3, strlen(s3), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';

    printf("Server : Grade - %s\n", buffer);

    close(sockfd);
    return 0;
}
