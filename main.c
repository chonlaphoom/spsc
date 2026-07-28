/* Ring Buffer */

#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Buffer *buffer = initBuffer(MAX_CAPACITY);
  if (!buffer) {
    fprintf(stderr, "Failed to initialize buffer\n");
    return 1;
  }
  enqueue(buffer, 1);
  enqueue(buffer, 2);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  enqueue(buffer, 3);
  enqueue(buffer, 4);
  enqueue(buffer, 5);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  enqueue(buffer, 6);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  enqueue(buffer, 6);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  freeBuffer(buffer);
  return 0;
}
