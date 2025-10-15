#include "csapp.h"
#include <sys/wait.h>
#include <unistd.h>

static char buf[256];

#define LINE1 49
#define LINE2 33
#define LINE3 78

static void print_pos(int fd) {
	// SEEK_CUR - the file offset i set to its current location plus offset bytes
	off_t offset = Lseek(fd, 0, SEEK_CUR);
	printf("pid: %d, cursor: %d\n\n", (int) getpid(), (int) offset);
	fflush(stdout);
}

static void do_read(int fd) {
	/* TODO: Spawn a child. Read from the file descriptor in both parent and
	 child. Check how file cursor value has changed in both processes. */

	pid_t pid = Fork();
	if(pid == 0) { // child
		usleep(500 * 1000); // 500ms
		printf("child pos before read\n");
		print_pos(fd);

		size_t n = Read(fd, buf, LINE2);

		printf("child pos after read\n");
		print_pos(fd);

	} else {
		printf("parent pos before read\n");
		print_pos(fd);

		ssize_t n = Read(fd, buf, LINE1);

		printf("parent pos after read\n");
		print_pos(fd);

		int wstatus;
		wait(&wstatus);
	}

	exit(0);
}

static void do_close(int fd) {
	/* TODO: In the child close file descriptor, in the parent wait for child to
	 die and check if the file descriptor is still accessible. */

	pid_t pid = Fork();
	if(pid == 0) { // child
		Close(fd);
	} else {
		int wstatus;
		wait(&wstatus);

		printf("parent before read\n");
		print_pos(fd);

		ssize_t n = Read(fd, buf, LINE1); 
		if(n < 0) {
			printf("error\n");
		} else {
			printf("ok operation\n");
		}

		printf("parent pos after read\n");
		print_pos(fd);
	}

	exit(0);
}

int main(int argc, char **argv) {
	if (argc != 2)
		app_error("Usage: %s [read|close]", argv[0]);

	int fd = Open("test.txt", O_RDONLY, 0);

  	if (!strcmp(argv[1], "read"))
    	do_read(fd);
  	if (!strcmp(argv[1], "close"))
    	do_close(fd);
  	app_error("Unknown variant '%s'", argv[1]);
}
