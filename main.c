/* Ring Buffer */

#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Buffer *buffer = initBuffer(MAX_CAPACITY);
  if (!buffer) {
    fprintf(stderr, "Failed to initialize buffer\n");
    return 1;
  }
  enqueue(buffer, 1);
  enqueue(buffer, 2);
  printf("Head: %zu Tail: %zu\n", buffer->head, buffer->tail);
  enqueue(buffer, 3);
  enqueue(buffer, 4);
  printf("Head: %zu Tail: %zu isFull: %d\n", buffer->head, buffer->tail,
         isFullBuffer(buffer));
  enqueue(buffer, 5);
  printf("Head: %zu Tail: %zu isFull: %d\n", buffer->head, buffer->tail,
         isFullBuffer(buffer));
  enqueue(buffer, 6);
  printf("Head: %zu Tail: %zu\n", buffer->head, buffer->tail);
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Head: %zu Tail: %zu\n", buffer->head, buffer->tail);
  enqueue(buffer, 6);
  printf("Head: %zu Tail: %zu\n", buffer->head, buffer->tail);
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Head: %zu Tail: %zu isFull: %d\n", buffer->head, buffer->tail,
         isFullBuffer(buffer));
  freeBuffer(buffer);
  return 0;
}
