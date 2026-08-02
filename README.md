# Single Producer, Single Consumer Queue (FIFO)

Building a lock-free, single producer, single consumer queue.
To learn how it works and delve dive into race-condition problem.

## Scripts

track race condition with `-fsanitize`

```bash
cc -std=c11 -g -pthread -fsanitize=thread -o bin/out two_threads.c rb.c && ./bin/out
```

main

```bash
cc -std=c11 -g -pedantic -Wall main.c rb.c -o ./bin/main && ./bin/main
```

benchmark before and after add padding

```bash
cc -std=c11 -O2 -pthread bench.c rb.c -o ./bin/bench && ./bin/bench
cc -std=c11 -O2 -pthread -DPADDED bench.c rb.c -o ./bin/bench && ./bin/bench
```

Padding is toggled with `-DPADDED` (or uncomment `#define PADDED` in `rb.h`).
It separates `head` and `tail` onto different cache lines to avoid false sharing.

Results on this Mac (10M items, best of 5 rounds, 128-byte cache lines):

| Variant  | head/tail offsets | best   | throughput |
| -------- | ----------------- | ------ | ---------- |
| unpadded | 0 / 8             | 0.456s | ~44 Mops/s |
| padded   | 0 / 136           | 0.325s | ~62 Mops/s |

Memory ordering: acquire/release vs relaxed

Compile-time switch in `rb.c` (or `-DRELAXED`): `#ifdef RELAXED` maps all acquire/release to `memory_order_relaxed`, removing the happens-before edges that make the queue correct.

Generate and diff the assembly:

```bash
cc -std=c11 -O2 -S rb.c -o rb_ar.s
cc -std=c11 -O2 -DRELAXED -S rb.c -o rb_relaxed.s
```
