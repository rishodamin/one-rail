# OneRail

OneRail is a high-concurrency railway ticket booking engine inspired by the Indian Railways Tatkal reservation system. The project focuses on building a thread-safe booking engine capable of processing thousands of simultaneous booking requests while maintaining data consistency and minimizing lock contention.

The objective is to explore systems programming concepts such as multithreading, synchronization, atomic operations, bit manipulation, and performance optimization using modern C++.

## Features

* Multi-threaded booking engine
* Configurable worker thread pool
* Fine-grained coach-level locking
* Bitmask-based seat representation
* Greedy seat allocation
* Atomic waitlist generation
* Booking cancellation with automatic waitlist promotion
* Concurrent load simulator and benchmarks

## Seat Allocation

Each passenger can book up to three seats.

Seats are grouped into triplets.

```text
(1,2,3)
(4,5,6)
(7,8,9)
...
```

Allocation follows the following rules:

* For one seat, allocate any available seat.
* For two seats, attempt to allocate two consecutive seats within the same triplet. If unavailable, allocate any two available seats.
* For three seats, attempt to allocate an entire triplet. If unavailable, allocate any three available seats.
* If no seats are available, assign the next waiting list number.

## Design

Instead of locking the entire train, every coach owns its own mutex. Multiple threads can therefore process bookings in different coaches simultaneously, reducing contention under heavy load.

Seat occupancy inside a coach is represented using bitmasks. This enables fast allocation, deallocation, and availability checks using bitwise operations while keeping memory usage low.

A fixed-size thread pool processes booking requests concurrently. Waiting list numbers are generated using atomic operations to avoid unnecessary locking.

## Project Structure

```text
OneRail/
├── include/
├── src/
├── tests/
├── benchmarks/
├── docs/
├── CMakeLists.txt
└── README.md
```

## Building

```bash
mkdir build
cd build

cmake ..
make

./onerail_sim
```

## Future Work

* Lock-free task queue
* Multiple train support
* Reservation priorities
* Performance benchmarking
* REST API
* Distributed booking engine

## License

MIT License
