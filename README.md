# Single Producer, Single Consumer Queue (FIFO)

Building a lock-free, single producer, single consumer queue from scratch in C.

## Build and Run

```
cc -std=c11 -pthread -g -fsanitize=thread -o bin/out main.c rb.c && ./bin/out
```
