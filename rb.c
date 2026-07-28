/* Ring Buffer */

#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

extern void freeBuffer(Buffer *buffer) {
  if (buffer != NULL) {
    free(buffer->queue);
    free(buffer);
  }
}

extern Buffer *initBuffer(size_t size) {
  size_t *queue = (size_t *)malloc(sizeof(size_t) * size);
  if (queue == NULL) {
    return NULL;
  }
  Buffer *buff = (Buffer *)malloc(sizeof(Buffer));
  if (buff == NULL) {
    free(queue);
    return NULL;
  }

  buff->queue = queue;
  buff->head = 0;
  buff->tail = 0;
  buff->size = 0;
  buff->capacity = size;
  return buff;
}

extern int enqueue(Buffer *buff, size_t val) {
  if (buff == NULL || buff->queue == NULL || isFullBuffer(buff)) {
    return 1;
  }

  buff->queue[buff->tail] = val;
  size_t cap = buff->capacity;
  buff->tail = (buff->tail + 1) % cap;
  buff->size++;

  return 0;
}

extern size_t dequeue(Buffer *buff) {
  if (buff == NULL || buff->queue == NULL || isEmptyBuffer(buff)) {
    return 0;
  }

  size_t val = buff->queue[buff->head];
  size_t cap = buff->capacity;
  buff->head = (buff->head + 1) % cap;
  buff->size--;

  return val;
}

extern int isEmptyBuffer(const Buffer *buffer) {
  return (buffer == NULL) ? 1 : (buffer->size == 0);
}

extern int isFullBuffer(Buffer *buffer) {
  return (buffer == NULL) ? 0 : (buffer->size == buffer->capacity);
}
