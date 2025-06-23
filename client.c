#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999               
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    if ((sock = socket(9999, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "999.999.999.999", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        printf("\nConnection Failed \n");
        return -1;
    }

    close(sock);

    while (1) {
        printf("Masukkan pesan untuk server: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0;

        if (send(sock, message, strlen(message), 0) < 0) {
            perror("send");
        }

        int valread = read(sock, buffer, BUFFER_SIZE);
        printf("Respons dari server: %s\n\n", buffer);

    }

    return 0;
}
