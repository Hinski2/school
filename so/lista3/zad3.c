#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

void handle_winch(int sig) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("rows: %d, cols: %d, x_pixel: %d, y_pixel: %d\n\n", w.ws_row, w.ws_col, w.ws_xpixel, w.ws_ypixel);
    fflush(stdout);
}

int main() {
    signal(SIGWINCH, handle_winch);
    while(1)
        pause();
}