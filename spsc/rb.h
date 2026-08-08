#pragma once

#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef PADDED
// #define PADDED  /* or compile with -DPADDED */
#endif

#ifdef PADDED
typedef struct {
  _Atomic size_t head;
  char pad1[128];
  _Atomic size_t tail;
  char pad2[128];
  size_t capacity;
  size_t *buffer;
} Buffer;
#else
typedef struct {
  _Atomic size_t head;
  _Atomic size_t tail;
  size_t capacity;
  size_t *buffer;
} Buffer;
#endif

extern Buffer *initBuffer(size_t size);
extern void freeBuffer(Buffer *buffer);
extern bool enqueue(Buffer *buffer, size_t val);
extern bool dequeue(Buffer *buffer, size_t *val);
static bool isEmptyBuffer(const Buffer *buffer);
static bool isFullBuffer(const Buffer *buffer);
