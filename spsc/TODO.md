# SPSC Lock-Free Queue — Learning Challenges

## Completed

- [x] Ring buffer basics (enqueue, dequeue, isFull, isEmpty)
- [x] C11 atomic operations (head, tail as `_Atomic size_t`)
- [x] Correct acquire/release memory ordering
- [x] Producer/consumer threads with pthreads
- [x] Sum validation test (passes ThreadSanitizer)

## Challenges

### 1. Cache line padding (false sharing)

`head` (written by consumer) and `tail` (written by producer) currently live on the same cache line. This causes cache bouncing between cores.

- Separate `head` and `tail` with padding (typically 64 bytes)
- Benchmark before and after to see the difference

### 2. Power-of-2 capacity with masking

Modulo (`% cap`) is slow. Lock-free queues often require power-of-2 capacity and use `& (cap - 1)` instead.

- Assert/require capacity is a power of 2
- Replace `(tail + 1) % capacity` with `(tail + 1) & (capacity - 1)`
- Compare performance

### 3. Mutex-based queue for comparison

Build the same queue protected by `pthread_mutex_t` and benchmark both.

- How much faster is the lock-free version?
- Does it scale with more items?

### 4. Batch operations

Single-item enqueue/dequeue has high synchronization overhead per item.

- Add `size_t enqueue_n(Buffer *b, const size_t *vals, size_t n)`
- Add `size_t dequeue_n(Buffer *b, size_t *vals, size_t n)`
- Move multiple items per acquire/release pair
- Measure throughput improvement

### 5. Backoff strategy

Busy-waiting (`while (!enqueue(...)) ;`) hammers the CPU.

- Add `_mm_pause()` (x86) / `__builtin_arm_yield()` (ARM) in the spin loop
- Or use `sched_yield()` after a spin threshold
- Compare power consumption / CPU usage

### 6. Hazard pointers / Epoch-based reclamation (advanced)

If the queue held dynamically allocated pointers instead of integers, the consumer must know when it's safe to free.

- Research hazard pointers or RCU
- Implement a simple pointer-based SPSC with safe memory reclamation

## Bonus

- [ ] Write a benchmark that measures ops/sec for each version
- [ ] Compare generated assembly (`-S`) with and without padding
- [ ] Experiment with different cache line sizes
