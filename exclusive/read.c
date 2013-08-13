#include <sys/file.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "read.h"

int read_exclusive(int fd) {
  struct stat fileinfo;
  char readchar;

  if(flock(fd, LOCK_EX) != 0) {
    perror("flock");
    return -1;
  }
  if(unlink(SAVEFILE) != 0) {
    perror("unlink");
    return -1;
  }
  if(fstat(fd, &fileinfo) != 0) {
    perror("fstat");
    return -1;
  }
  if(fileinfo.st_nlink != 0) {
    fprintf(stderr, "st_nlink == %d != 0\n", fileinfo.st_nlink);
    return -1;
  }
  if(fileinfo.st_size == 0) {
    fprintf(stderr, "st_size == %d\n", fileinfo.st_size);
    return -1;
  }
  if(read(fd, &readchar, 1) != 1) {
    perror("read");
    return -1;
  }
  if(ftruncate(fd, 0) != 0) {
    perror("ftruncate");
    return -1;
  }

  if(readchar == '1') {
    return 1;
  }
  return 0;
}
