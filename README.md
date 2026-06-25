# OneRail

OneRail is a high-concurrency railway ticket booking engine (Phase 1).
This part implements a correct single-threaded booking engine with a clean architecture.

## Features
- Bitmask-based seat allocation
- Multi-coach train model
- Waitlist generation and automatic promotion
- Ticket cancellation
- Configurable seat allocation logic favoring consecutive seats and whole triplets.

## Build

```bash
mkdir build
cd build
cmake ..
make
```

## Run
```bash
./onerail_demo
```
