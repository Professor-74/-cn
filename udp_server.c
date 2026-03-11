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
    char *message = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    int len;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&cliaddr, &len);

    printf("Client message: %s\n", buffer);

    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);

    return 0;
}
