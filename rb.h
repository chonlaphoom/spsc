#pragma once

#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t *buffer;
  _Atomic size_t head;
  _Atomic size_t tail;
  size_t capacity;
} Buffer;

extern Buffer *initBuffer(size_t size);
extern void freeBuffer(Buffer *buffer);
extern bool enqueue(Buffer *buffer, size_t val);
extern bool dequeue(Buffer *buffer, size_t *val);
static bool isEmptyBuffer(const Buffer *buffer);
static bool isFullBuffer(const Buffer *buffer);
