/* Ring Buffer */

#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 5

typedef struct {
  size_t *queue;
  size_t head;
  size_t tail;
  size_t size;
  size_t capacity;
} Buffer;

static Buffer *initBuffer(size_t size);
static int enqueue(Buffer *buffer, size_t val);
static size_t dequeue(Buffer *buffer);
static void freeBuffer(Buffer *buffer) {
  if (buffer != NULL) {
    free(buffer->queue);
    free(buffer);
  }
}
static int isEmptyBuffer(const Buffer *buffer);
static int isFullBuffer(Buffer *buffer);

int main() {
  Buffer *buffer = initBuffer(MAX_CAPACITY);
  if (!buffer) {
    fprintf(stderr, "Failed to initialize buffer\n");
    return 1;
  }
  enqueue(buffer, 1);
  enqueue(buffer, 2);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  enqueue(buffer, 3);
  enqueue(buffer, 4);
  enqueue(buffer, 5);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  enqueue(buffer, 6);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  printf("Dequeue: %zu\n", dequeue(buffer));
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  enqueue(buffer, 6);
  printf("Head: %zu Tail: %zu size: %zu\n", buffer->head, buffer->tail,
         buffer->size);
  freeBuffer(buffer);
  return 0;
}

static Buffer *initBuffer(size_t size) {
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

static int enqueue(Buffer *buff, size_t val) {
  if (buff == NULL || buff->queue == NULL || isFullBuffer(buff)) {
    return 1;
  }

  buff->queue[buff->tail] = val;
  size_t cap = buff->capacity;
  buff->tail = (buff->tail + 1) % cap;
  buff->size++;

  return 0;
}

static size_t dequeue(Buffer *buff) {
  if (buff == NULL || buff->queue == NULL || isEmptyBuffer(buff)) {
    return 0;
  }

  size_t val = buff->queue[buff->head];
  size_t cap = buff->capacity;
  buff->head = (buff->head + 1) % cap;
  buff->size--;

  return val;
}

static int isEmptyBuffer(const Buffer *buffer) {
  return (buffer == NULL) ? 1 : (buffer->size == 0);
}
static int isFullBuffer(Buffer *buffer) {
  return (buffer == NULL) ? 0 : (buffer->size == buffer->capacity);
}
