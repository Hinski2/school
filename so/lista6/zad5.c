#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static volatile sig_atomic_t got_int = 0;

static void handler(int sig) {
    got_int = 1;
}

int main() {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigaction(SIGINT, &sa, NULL);

    printf("start");
    while(1) {
        if(got_int) {
            fflush(NULL);
            _exit(0);
        }
    }
}