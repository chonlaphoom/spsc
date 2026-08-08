#pragma once

typedef struct {
  int *data;
  int size;
  int capacity;
} IntStack;

void stack_init(IntStack *stack);
void stack_free(IntStack *stack);
int stack_push(IntStack *stack, int value);
int stack_pop(IntStack *stack, int *out);
int stack_peek(const IntStack *stack, int *out);
int stack_is_empty(const IntStack *stack);
