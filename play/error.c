#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  printf("uid = %d, gid = %d\n", getuid(), getgid());
  fprintf(stderr, "EACCES: %s\n", strerror(EACCES));

  errno = ENOENT;
  perror(argv[0]); // ./a.out: No such file or directory
  exit(0);
}
