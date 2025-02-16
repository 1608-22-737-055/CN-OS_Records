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
    char s1[MAXLINE], s2[MAXLINE], s3[MAXLINE];
    char *GRADE;
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        int len, n;
        len = sizeof(cliaddr);

        n = recvfrom(sockfd, (char *)s1, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        s1[n] = '\0';

        n = recvfrom(sockfd, (char *)s2, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        s2[n] = '\0';

        n = recvfrom(sockfd, (char *)s3, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        s3[n] = '\0';

        printf("Client S1: %s\n", s1);
        printf("Client S2: %s\n", s2);
        printf("Client S3: %s\n", s3);

        int sub1 = atoi(s1);
        int sub2 = atoi(s2);
        int sub3 = atoi(s3);
        int avg = (sub1 + sub2 + sub3) / 3;

        if (avg > 75 && avg <= 100) {
            GRADE = "A";
        } else if (avg > 50 && avg <= 75) {
            GRADE = "B";
        } else {
            GRADE = "C";
        }

        sendto(sockfd, (const char *)GRADE, strlen(GRADE), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("GRADE sent.\n");
    }

    return 0;
}
