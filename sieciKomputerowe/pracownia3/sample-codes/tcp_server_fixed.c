#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


_Noreturn static void ERROR(const char* str)
{
    fprintf(stderr, "%s: %s\n", str, strerror(errno));  // NOLINT(*-err33-c)
    exit(EXIT_FAILURE);
}


// Warning: it may read beyond end_marker in the stream.
// These extra bytes are returned and removed from the TCP buffer.

typedef struct { size_t bytes_read; bool end_marker_found; } recv_info;

static recv_info recv_till_end_marker(int fd, uint8_t *buffer, size_t buffer_size, char end_marker)
{
    size_t total_bytes_read = 0;
    bool end_marker_found = false;
    while (total_bytes_read < buffer_size && !end_marker_found) {
        ssize_t bytes_read = recv(fd, buffer + total_bytes_read, buffer_size - total_bytes_read, 0);
        if (bytes_read < 0)
            ERROR("recv error");

        if (bytes_read == 0) {
            printf("DEBUG: Connection closed by client before end marker was found\n");
            break;
        }

        printf("DEBUG: %ld bytes read\n", bytes_read);
        end_marker_found = memchr(buffer + total_bytes_read, end_marker, (size_t)bytes_read) != NULL;
        total_bytes_read += (size_t)bytes_read;
    }
    return (recv_info){total_bytes_read, end_marker_found};
}


int main(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
        ERROR("socket error");

    struct sockaddr_in server_address = { 0 };
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(32345);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_fd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
        ERROR("bind error");

    if (listen (sock_fd, SOMAXCONN) < 0)
        ERROR("listen error");

    enum { BUFFER_SIZE = 5000000 };
    uint8_t recv_buffer[BUFFER_SIZE + 1];

    for (;;) {
        int connected_sock_fd = accept(sock_fd, NULL, NULL);
        if (connected_sock_fd < 0)
            ERROR("accept error");

        recv_info info = recv_till_end_marker(connected_sock_fd, recv_buffer, BUFFER_SIZE, 'X');
        recv_buffer[info.bytes_read] = '\0';


        enum { MAX_REPLY_LENGTH = 20 };
        uint8_t reply_buffer[MAX_REPLY_LENGTH + 1];

        size_t reply_length = info.bytes_read < MAX_REPLY_LENGTH ? info.bytes_read : MAX_REPLY_LENGTH;
        memcpy(reply_buffer, recv_buffer, reply_length);
        reply_buffer[reply_length] = '\0';
        printf("%zd bytes read, first %zd bytes: '%s'\n", info.bytes_read, reply_length, (const char*)reply_buffer);

        if (info.end_marker_found) {
            printf("End marker found, sending a reply.\n");
            ssize_t bytes_sent = send(connected_sock_fd, reply_buffer, strlen((char*)reply_buffer), 0);
            if (bytes_sent < 0)
                ERROR("send error");
        } else {
            printf("End marker not found, not sending a reply.\n");
        }

        if (close (connected_sock_fd) < 0)
            ERROR("close error");
    }
}
