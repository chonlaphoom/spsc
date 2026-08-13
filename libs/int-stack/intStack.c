#include "intStack.h"
#include <stdlib.h>

/*
 * LIFO stack implementation using dynamic array.
 */
extern void stack_init(IntStack *stack) {
  if (stack == NULL) {
    return;
  }
  stack->size = 0;
  stack->capacity = 0;
  stack->data = NULL;
}

extern void stack_free(IntStack *stack) {
  if (stack != NULL && stack->data != NULL) {
    free(stack->data);
  }
}

extern int stack_push(IntStack *stack, int value) {
  if (stack == NULL) {
    return -1;
  }
  if (stack->capacity == 0) {
    int *newData = (int *)malloc(sizeof(int) * 4);
    if (newData == NULL) {
      return -1;
    }
    stack->data = newData;
    stack->capacity = 4;
    stack->size = 1;
    stack->data[0] = value;
    return 0;
  }

  if (stack->size == stack->capacity) {
    // no space left
    int *newData =
        (int *)realloc(stack->data, sizeof(int) * stack->capacity * 2);
    if (newData == NULL) {
      return -1;
    }
    stack->data = newData;
    stack->data[stack->size] = value;
    stack->capacity = stack->capacity * 2;
    stack->size++;
    return 0;
  }

  stack->data[stack->size] = value;
  stack->size += 1;
  return 0;
}

extern int stack_pop(IntStack *stack, int *out) {
  if (stack == NULL || stack->size == 0) {
    return -1;
  }

  *out = stack->data[--stack->size];
  return 0;
}

extern int stack_peek(const IntStack *stack, int *out) {
  if (stack == NULL || stack->size == 0) {
    return -1;
  }

  *out = stack->data[stack->size - 1];
  return 0;
}

extern int stack_is_empty(const IntStack *stack) {
  if (stack->size == 0) {
    return 1;
  }
  return 0;
}
