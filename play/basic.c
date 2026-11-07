#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1024 * 4

int 
main(void) {
  long n;
  char buffer[BUFFER_SIZE];

  while ((n = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
    if (write(STDOUT_FILENO, buffer, n) != n) {
      perror("write error");
      return 1;
    }

  if (n < 0) {
    perror("write error");
    return 1;
  }

  exit(0);
}
