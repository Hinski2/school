#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static void print_ids() {
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    printf("ruid = %d, euid = %d, suid = %d\n", ruid, euid, suid);
} 

int main() {
    print_ids();

    // a
    printf("setuid(2000)\n");
    setuid(2000);
    print_ids();

    // b
    printf("setreuid(-1, 2000)\n");
    setreuid(-1, 2000);
    print_ids();

    // c
    printf("seteuid(2000)\n");
    seteuid(2000);
    print_ids();

    // d
    printf("setresuid(-1, 2000, 3000)\n");
    setresuid(-1, 2000, 3000);
    print_ids();
}