#include "rb.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Buffer *buffer = initBuffer(1024);
  if (!buffer) {
    fprintf(stderr, "initBuffer failed\n");
    return 1;
  }

  printf("Buffer capacity: %zu\n", sizeof(Buffer));
  freeBuffer(buffer);
  return 0;
}
