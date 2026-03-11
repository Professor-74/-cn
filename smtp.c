#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 25
#define BUFFER_SIZE 4096

void send_cmd(int sock, const char *cmd) {
    char buffer[BUFFER_SIZE];
    printf("C: %s", cmd);
    send(sock, cmd, strlen(cmd), 0);

    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    const char *server_ip = "127.0.0.1";      // SMTP server IP
    const char *from = "sender@example.com";
    const char *to = "recipient@example.com";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer);

    send_cmd(sock, "HELO localhost\r\n");

    char cmd[BUFFER_SIZE];

    snprintf(cmd, sizeof(cmd), "MAIL FROM:<%s>\r\n", from);
    send_cmd(sock, cmd);

    snprintf(cmd, sizeof(cmd), "RCPT TO:<%s>\r\n", to);
    send_cmd(sock, cmd);

    send_cmd(sock, "DATA\r\n");

    const char *message =
        "Subject: Test Mail\r\n"
        "From: sender@example.com\r\n"
        "To: recipient@example.com\r\n"
        "\r\n"
        "Hello, this is a test email sent from a C SMTP client.\r\n"
        ".\r\n";

    send_cmd(sock, message);

    send_cmd(sock, "QUIT\r\n");

    close(sock);
    return 0;
}
