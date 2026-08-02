/*
 * start with ring buffer then add a lock free version using atomic operations
 */
#include "rb.h"
#include <stdatomic.h>
#include <stdlib.h>

#ifndef RELAXED
// #define RELAXED  /* or compile with -DRELAXED: no ordering guarantees */
#endif

#ifdef RELAXED
#define MO_ACQ memory_order_relaxed
#define MO_REL memory_order_relaxed
#else
#define MO_ACQ memory_order_acquire
#define MO_REL memory_order_release
#endif

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
  atomic_store_explicit(&b->tail, (tail + 1) % b->capacity, MO_REL);
  return true;
}

extern bool dequeue(Buffer *b, size_t *val) {
  if (!b || !val)
    return false;
  if (isEmptyBuffer(b))
    return false;
  size_t head = atomic_load_explicit(&b->head, memory_order_relaxed);
  *val = b->buffer[head];
  atomic_store_explicit(&b->head, (head + 1) % b->capacity, MO_REL);
  return true;
}

static bool isEmptyBuffer(const Buffer *b) {
  if (!b)
    return true;

  return atomic_load_explicit(&b->head, memory_order_relaxed) ==
         atomic_load_explicit(&b->tail, MO_ACQ);
}

static bool isFullBuffer(const Buffer *b) {
  if (!b)
    return false;

  return atomic_load_explicit(&b->head, MO_ACQ) ==
         (atomic_load_explicit(&b->tail, memory_order_relaxed) + 1) %
             b->capacity;
}
