#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "read.h"

int main(int argc, char **argv) {
  int status, fd;
  int wait = 0;

  if(argc == 2) {
    wait = atoi(argv[1]);
  }

  if((fd = open(SAVEFILE, O_RDWR)) < 0) {
    perror("open");
    exit(1);
  }
  if(wait > 0) {
    sleep(wait);
  }
  status = read_exclusive(fd);
  printf("%ld %d\n", getpid(), status);
}
