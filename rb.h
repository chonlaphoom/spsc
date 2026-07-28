#pragma once

#include <stdlib.h>

#define MAX_CAPACITY 5

typedef struct {
  size_t *queue;
  size_t head;
  size_t tail;
  size_t size;
  size_t capacity;
} Buffer;

extern Buffer *initBuffer(size_t size);
extern int enqueue(Buffer *buffer, size_t val);
extern size_t dequeue(Buffer *buffer);
extern void freeBuffer(Buffer *buffer);
extern int isEmptyBuffer(const Buffer *buffer);
extern int isFullBuffer(Buffer *buffer);
