# Single Producer, Single Consumer Queue (FIFO)

Building a lock-free, single producer, single consumer queue.
To learn how it works and delve dive into race-condition problem.

## Scripts

two threads

```bash
cc -std=c11 -g -pthread -fsanitize=thread -o bin/out two_threads.c rb.c && ./bin/out
```

main

```bash
cc -std=c11 -g -pedantic -Wall main.c rb.c -o ./bin/main && ./bin/main
```

benchmark before and after add padding

```bash
cc -std=c11 -O2 -pthread bench.c rb.c -o ./bin/bench && ./bin/bench           # unpadded
cc -std=c11 -O2 -pthread -DPADDED bench.c rb.c -o ./bin/bench && ./bin/bench  # padded
```

Padding is toggled with `-DPADDED` (or uncomment `#define PADDED` in `rb.h`).
It separates `head` and `tail` onto different cache lines to avoid false sharing.

Results on this Mac (10M items, best of 5 rounds, 128-byte cache lines):

| Variant  | head/tail offsets | best   | throughput |
| -------- | ----------------- | ------ | ---------- |
| unpadded | 0 / 8             | 0.456s | ~44 Mops/s |
| padded   | 0 / 136           | 0.325s | ~62 Mops/s |
