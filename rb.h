#pragma once

#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

typedef _Atomic size_t atomic_size_t;

#define MAX_CAPACITY 5

typedef struct {
  size_t *queue;
  atomic_size_t head;
  atomic_size_t tail;
  size_t capacity;
  size_t ready;
} Buffer;

extern Buffer *initBuffer(size_t size);
extern size_t enqueue(Buffer *buffer, size_t val);
extern size_t dequeue(Buffer *buffer);
extern void freeBuffer(Buffer *buffer);
extern bool isEmptyBuffer(const Buffer *buffer);
extern bool isFullBuffer(Buffer *buffer);

static Buffer *acquire(Buffer *buffer);
static void release(Buffer *buffer);
