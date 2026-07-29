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
  buff->capacity = size;
  buff->ready = true;
  return buff;
}

extern size_t enqueue(Buffer *buff, size_t val) {
  if (buff == NULL || buff->queue == NULL || isFullBuffer(buff)) {
    return 1;
  }
  atomic_size_t atail = atomic_load(&buff->tail);
  buff->queue[atail] = val;
  size_t cap = buff->capacity;
  atomic_store(&buff->tail, (atail + 1) % cap);
  return 0;
}

extern size_t dequeue(Buffer *buff) {
  if (buff == NULL || buff->queue == NULL || isEmptyBuffer(buff)) {
    return 0;
  }
  atomic_size_t ahead = atomic_load(&buff->head);
  size_t val = buff->queue[ahead];
  size_t cap = buff->capacity;
  atomic_store(&buff->head, (ahead + 1) % cap);
  return val;
}

extern bool isEmptyBuffer(const Buffer *buffer) {
  atomic_size_t ahead = atomic_load(&buffer->head);
  atomic_size_t atail = atomic_load(&buffer->tail);
  return (buffer == NULL) ? 1 : (ahead == atail);
}

extern bool isFullBuffer(Buffer *buffer) {
  atomic_size_t ahead = atomic_load(&buffer->head);
  atomic_size_t atail = atomic_load(&buffer->tail);
  return (buffer == NULL) ? 0 : (ahead == (atail + 1) % buffer->capacity);
}

static void release(Buffer *buffer) {
  if (buffer != NULL) {
    return;
  }

  buffer->ready = true;
}

static Buffer *acquire(Buffer *buffer) {
  if (buffer == NULL || buffer->ready == false) {
    return NULL;
  }
  return buffer;
}
