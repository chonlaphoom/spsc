/*
 * start with ring buffer then add a lock free version using atomic operations
 */
#include "rb.h"
#include <stdatomic.h>
#include <stdlib.h>

extern void freeBuffer(Buffer *buffer) {
  if (buffer) {
    free(buffer->buffer);
    free(buffer);
  }
}

extern Buffer *initBuffer(size_t size) {
  size_t *buf = malloc(sizeof(size_t) * size);
  if (!buf)
    return NULL;
  Buffer *b = malloc(sizeof(Buffer));
  if (!b) {
    free(buf);
    return NULL;
  }
  b->buffer = buf;
  atomic_init(&b->head, 0);
  atomic_init(&b->tail, 0);
  b->capacity = size;
  return b;
}

extern bool enqueue(Buffer *b, size_t val) {
  if (!b)
    return false;
  if (isFullBuffer(b))
    return false;
  size_t tail = atomic_load_explicit(&b->tail, memory_order_relaxed);
  b->buffer[tail] = val;
  atomic_store_explicit(&b->tail, (tail + 1) % b->capacity,
                        memory_order_release);
  return true;
}

extern bool dequeue(Buffer *b, size_t *val) {
  if (!b || !val)
    return false;
  if (isEmptyBuffer(b))
    return false;
  size_t head = atomic_load_explicit(&b->head, memory_order_relaxed);
  *val = b->buffer[head];
  atomic_store_explicit(&b->head, (head + 1) % b->capacity,
                        memory_order_release);
  return true;
}

static bool isEmptyBuffer(const Buffer *b) {
  if (!b)
    return true;

  return atomic_load_explicit(&b->head, memory_order_relaxed) ==
         atomic_load_explicit(&b->tail, memory_order_acquire);
}

static bool isFullBuffer(const Buffer *b) {
  if (!b)
    return false;

  return atomic_load_explicit(&b->head, memory_order_acquire) ==
         (atomic_load_explicit(&b->tail, memory_order_relaxed) + 1) %
             b->capacity;
}
