#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


_Noreturn static void ERROR(const char* str)
{
    fprintf(stderr, "%s: %s\n", str, strerror(errno));  // NOLINT(*-err33-c)
    exit(EXIT_FAILURE);
}


int main(void)
{
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0)
        ERROR("socket error");

    struct sockaddr_in server_address = { 0 };
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(32345);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    const char* message = "Hello server!";
    size_t message_len = strlen(message);
    if (sendto(sock_fd, message, message_len, 0, (struct sockaddr*) &server_address, sizeof(server_address)) != (ssize_t)message_len)
        ERROR("sendto error");

    close(sock_fd);
    return EXIT_SUCCESS;
}

