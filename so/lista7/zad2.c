#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void private_file() {
    int fd = open("a.txt", O_RDWR);
    if(fd == -1) exit(1);

    char *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(addr == MAP_FAILED) exit(1);

    addr[0] = 'X';
    munmap(addr, 4096);
    close(fd);
}

void shared_file() {
    int fd = open("a.txt", O_RDWR);
    if(fd == -1) exit(1);

    char *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) exit(1);

    addr[0] = 'X';
    munmap(addr, 4096);
    close(fd);
}

void private_anonymous() {
    char *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(addr == MAP_FAILED) exit(1);

    addr[0] = 67;
    pid_t pid = fork();

    if(pid == 0) {  // chid
        addr[0] = 42; // copy on write
        _exit(0);
    } else {        // parrent
        wait(NULL);
        if(addr[0] == 67) exit(2); // powinno się wywołać
    }

    munmap(addr, 4096);
}


void shared_anonymous() {
    // fd = -1
    char *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(addr == MAP_FAILED) exit(1);

    for(int i = 0; i < 4096; i++)
        if(addr[i]) printf("grrrr");

    munmap(addr, 4096);
}

int main() {

    // private_file();
    // shared_file();
    private_anonymous();
    // shared_anonymous();

    printf("OK");
}