#include "csapp.h"
#include <sys/wait.h>

ssize_t Rio_writen(int fd, const void *usrbuf, size_t n);

static int conflict(int x1, int y1, int x2, int y2) {
	return x1 == x2
		|| y1 == y2
		|| x1 + y1 == x2 + y2
		|| x1 - y1 == x2 - y2;
}

static int try_conflict(int x1, int y1, int size, int *board) {
	for(int i = 0; i < size; i++) {
		if(conflict(x1, y1, i, board[i])) return 1;
	}

	return 0;
}

static void print_line_sep(int size) {
	for (int i = 0; i < size; ++i) 
		printf("+---");
	printf("+\n");
}

static void print_line_sep_atomic(int size, char* buf, size_t* off) {
	for(int i = 0; i < size; i++)
		*off += sprintf(buf + *off, "+---");
	*off += sprintf(buf + *off, "+\n");
}

static void print_board(int size, int board[size]) {
	for (int i = 0; i < size; ++i) {
		print_line_sep(size);
		for (int j = 0; j < size; ++j)
			printf("|%s", board[i] == j ? " Q " : "   ");
		printf("|\n");
	}
	print_line_sep(size);
	printf("\n");
}


static void print_board_atomic(int size, int board[size]) {
 	char buf[4096];
	size_t off = 0;

	for(int i = 0; i < size; i++) {
		print_line_sep_atomic(size, buf, &off);
		for(int j = 0; j < size; j++)
			off += sprintf(buf + off, "|%s", board[i] == j ? " Q " : "   ");
		off += sprintf(buf + off, "|\n");
	}
	print_line_sep_atomic(size, buf, &off);
	off += sprintf(buf + off, "\n");

	Rio_writen(STDOUT_FILENO, buf, off);
}

static void put_het(size_t line, int size, int board[size]) {
	if(line == size) {
		print_board_atomic(size, board);
		exit(0);
	}

	size_t pids_no = 0;
	pid_t pids[size];

	for(int i = 0; i < size; i++) {
		if(try_conflict(line, i, line, board)) continue;

		pid_t pid = Fork();
		if(pid == 0) { // child
			board[line] = i;
			put_het(line + 1, size, board);	
			exit(0);
		} else {
			pids[pids_no++] = pid;
		}
	}

	for(int i = 0; i < pids_no; i++) {
		int wstate;
		waitpid(pids[i], &wstate, 0);
	}
	
	exit(0);
}

int main(int argc, char **argv) {
	if (argc != 2)
		app_error("Usage: %s [SIZE]", argv[0]);

	int size = atoi(argv[1]);

	if (size < 3 || size > 9)
		app_error("Give board size in range from 4 to 9!");

	int board[size];
	put_het(0, size, board);

	return 0;
}
