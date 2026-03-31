Multithreaded Systems Programming — POSIX Threads (C++)

Four concurrent systems programs written in C++ using the POSIX threads API. Built for an Operating Systems course at TCU. Demonstrates low-level thread coordination, shared memory management, and parallel algorithm design — without high-level concurrency abstractions.

---

## Projects

### Sudoku Validator
Validates a 9×9 Sudoku board using **27 concurrent threads** — one per row, column, and 3×3 subgrid. Each thread independently checks its region for duplicate values using an unordered set. Uses `std::atomic<int>` for race-free signaling across threads.

**Key skills:** thread decomposition, atomic operations, 2D array indexing, file I/O

---

### Multithreaded Merge Sort
Sorts an integer array by splitting it across **two sorting threads**, then merging results with a **third merge thread**. Threads are sequenced with explicit `pthread_join` barriers — sort threads must complete before the merge thread launches.

**Key skills:** parallel sorting, thread sequencing, dynamic memory allocation, merge algorithm

---

### Monte Carlo Pi Estimator
Estimates π using random dart-throw simulation across **4 parallel threads**, each running independent trials with thread-local seeds via `rand_r()`. Aggregates hit counts atomically and computes the final estimate from the combined result.

**Key skills:** Monte Carlo methods, thread-safe RNG, atomic aggregation, floating-point computation

---

### Integer Identifier
Classifies command-line integers across **4 concurrent threads** (negative, zero, prime, not prime) while preserving input order in output — without mutexes or semaphores. Uses a global `turn` counter with `sched_yield()` for cooperative thread coordination.

**Key skills:** lock-free synchronization, cooperative scheduling, primality testing (O(√n)), ordered concurrent output

---

## Technical Highlights

- Written in **C++** with POSIX threads (`pthread.h`)
- Lock-free coordination using `std::atomic` and `sched_yield()`
- Thread-safe RNG with per-thread seeds (`rand_r`)
- Handles 64-bit integer overflow edge cases (`long long`, `atoll`)
- Compiled and tested on **Ubuntu Server 24.04 LTS** (babbage.cs.tcu.edu)

---

## Build & Run

Each subdirectory contains a `Makefile`:

```bash
cd SudokuValidator && make && ./pthsv tests/input.txt
cd ThreadSorter    && make && ./pthsort tests/input.txt
cd MonteCarloPi   && make && ./pthpi
cd IntegerIdentifier && make && ./pthii 4 -5 3 -1 2 0 1
```

---

## Author

**Griffin Kuchar** — CS + Math + Economics, TCU (Class of 2027)  

[github.com/gkuchar](https://github.com/gkuchar) 

[linkedin.com/griffin-kuchar](https://www.linkedin.com/in/griffin-kuchar/)