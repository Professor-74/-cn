#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd;
    char buffer[1024];
    char *message = "Hello from client";
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);

    printf("Server message: %s\n", buffer);

    close(sockfd);

    return 0;
}
