#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buff1[1024] = "abcdefghij";
char buff2[] = "1234567890";

int main(void) {
  int fd;

  if ((fd = creat("testfile", FILESEC_MODE)) < 0) {
    perror("create");
    exit(1);
  }

  printf("fd created: %d\n", fd);

  if ((write(fd, buff1, sizeof(buff1))) != sizeof(buff1)) {
    perror("buff1 write error");
    exit(1);
  }

  off_t current_offset;
  if ((current_offset = lseek(fd, 16384, SEEK_SET) == -1))
    perror("lseek error");
  // offset now = 16384

  if (write(fd, buff2, sizeof(buff2)) != sizeof(buff2))
    perror("buff2 write error");
  // offset now = 16394

  exit(0);
}
