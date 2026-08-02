/*
 * Measure operations per second of the ring buffer implementation.
 *
 * Build for benchmarking:
 *   cc -std=c11 -O2 -pthread bench.c rb.c -o bin/bench # no padding
 *   cc -std=c11 -O2 -pthread -DPADDED bench.c rb.c -o bin/bench # with padding
 */
#include "rb.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <time.h>
#include <unistd.h>

struct ThreadArg {
  Buffer *buffer;
  size_t count;
};
static void *producer(void *arg);
static void *consumer(void *arg);
static double runBenchmark(size_t count);

#define NUM_ITEMS 10000000
#define NUM_ROUNDS 5

int main(void) {
#ifdef PADDED
  printf("Variant: PADDED\n");
#else
  printf("Variant: UNPADDED\n");
#endif
  printf("offsetof(Buffer, head) = %zu\n", offsetof(Buffer, head));
  printf("offsetof(Buffer, tail) = %zu\n", offsetof(Buffer, tail));
  size_t linesize = 0;
  size_t len = sizeof(linesize);
  if (sysctlbyname("hw.cachelinesize", &linesize, &len, NULL, 0) == 0) {
    printf("cache line size        = %zu\n", linesize);
  } else {
    printf("cache line size        = unknown\n");
  }

  runBenchmark(NUM_ITEMS / 10); /* warmup to avoid cold start effects */

  double results[NUM_ROUNDS];
  for (int i = 0; i < NUM_ROUNDS; i++) {
    results[i] = runBenchmark(NUM_ITEMS);
  }

  double best = results[0];
  for (int i = 1; i < NUM_ROUNDS; i++) {
    if (results[i] < best)
      best = results[i];
  }
  printf("rounds:");
  for (int i = 0; i < NUM_ROUNDS; i++) {
    printf(" %.3f", results[i]);
  }
  printf("\n");
  printf("best elapsed: %.3f s  ->  %.1f Mops/s\n", best,
         (2.0 * NUM_ITEMS) / best / 1e6);
  /* 2.0 * NUM_ITEMS because each item is enqueued and dequeued then round to
   * Mops */
  return 0;
}

static double runBenchmark(size_t count) {
  Buffer *buffer = initBuffer(1024);
  if (!buffer) {
    fprintf(stderr, "initBuffer failed\n");
    exit(1);
  }

  struct ThreadArg prodArg = {buffer, count};
  struct ThreadArg consArg = {buffer, count};
  pthread_t prodThread, consThread;

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  pthread_create(&prodThread, NULL, producer, &prodArg);
  pthread_create(&consThread, NULL, consumer, &consArg);
  pthread_join(prodThread, NULL);
  pthread_join(consThread, NULL);
  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed = (end.tv_sec - start.tv_sec) +
                   (end.tv_nsec - start.tv_nsec) / 1000000000.0;

  freeBuffer(buffer);
  return elapsed;
}

static void *producer(void *arg) {
  struct ThreadArg *threadArg = (struct ThreadArg *)arg;
  size_t count = 0;
  while (count < threadArg->count) {
    if (enqueue(threadArg->buffer, count)) {
      count++;
    }
  }
  return NULL;
}
static void *consumer(void *arg) {
  struct ThreadArg *threadArg = (struct ThreadArg *)arg;
  size_t count = 0;
  while (count < threadArg->count) {
    size_t val;
    if (dequeue(threadArg->buffer, &val)) {
      count++;
    }
  }
  return NULL;
}
