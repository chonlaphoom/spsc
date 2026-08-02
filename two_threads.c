#include "rb.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ITEMS 10000

typedef struct {
  Buffer *buffer;
  size_t count;
  size_t sum;
} ThreadArg;

static void *producer(void *arg) {
  ThreadArg *threadArg = (ThreadArg *)arg;
  for (size_t i = 0; i < threadArg->count; i++) {
    while (!enqueue(threadArg->buffer, i))
      ;
  }
  return NULL;
}

static void *consumer(void *arg) {
  ThreadArg *threadArg = (ThreadArg *)arg;
  for (size_t i = 0; i < threadArg->count; i++) {
    size_t val;
    while (!dequeue(threadArg->buffer, &val))
      ;
    threadArg->sum += val;
  }
  return NULL;
}

int main(void) {
  Buffer *buffer = initBuffer(1024);
  if (!buffer) {
    fprintf(stderr, "initBuffer failed\n");
    return 1;
  }
  ThreadArg prodArg = {buffer, NUM_ITEMS, 0};
  ThreadArg consArg = {buffer, NUM_ITEMS, 0};
  pthread_t prodThread, consThread;
  pthread_create(&prodThread, NULL, producer, &prodArg);
  pthread_create(&consThread, NULL, consumer, &consArg);
  pthread_join(prodThread, NULL);
  pthread_join(consThread, NULL);

  size_t expected = NUM_ITEMS * (NUM_ITEMS - 1) / 2;
  printf("Expected sum: %zu, Actual sum: %zu\n", expected, consArg.sum);
  printf("Test %s\n", expected == consArg.sum ? "PASSED" : "FAILED");

  freeBuffer(buffer);
  return 0;
}
