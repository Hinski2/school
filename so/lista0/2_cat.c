#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc, char* argv[]) {
  int fd = STDIN_FILENO;
  int n;
  char buf[BUFFSIZE];

  if (argc > 1) {
    if((fd = open(argv[1], O_RDONLY)) < 0) 
      err_sys("open %s error", argv[1]);
  }

  while ((n = read(fd, buf, BUFFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  if (fd != STDIN_FILENO) 
    close(fd);

  exit(0);
}
