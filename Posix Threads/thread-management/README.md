# POSIX Threads Example

This repository contains a simple example demonstrating the use of POSIX threads (pthreads) in C/C++.

## Overview

The program `pthread-create-terminate.cpp` shows how to create multiple threads, have them execute a function concurrently, and properly terminate them.

## Code Explanation

The example demonstrates:
- Creating multiple threads using `pthread_create()`
- Passing arguments to thread functions
- Proper thread termination with `pthread_exit()`

Each thread prints a message with its thread ID number, demonstrating concurrent execution.

## How to Compile

To compile the program, use gcc with the pthread library flag:

```bash
g++ -o pthread-example pthread-create-terminate.cpp -pthread
```

Or with gcc:

```bash
gcc -o pthread-example pthread-create-terminate.cpp -pthread
```

## How to Run

After compilation, run the executable:

```bash
./pthread-example
```

## Expected Output

The output will show the main thread creating 5 threads and each thread printing its ID. The order may vary between runs due to thread scheduling:

```
In main: creating thread 0
In main: creating thread 1
Hello World! It's me, thread #0!
In main: creating thread 2
Hello World! It's me, thread #1!
In main: creating thread 3
Hello World! It's me, thread #2!
In main: creating thread 4
Hello World! It's me, thread #3!
Hello World! It's me, thread #4!
```

## Note About POSIX Threads

POSIX threads (pthreads) are a standard for threads that allow a program to control multiple different flows of work concurrently. Benefits include:

- Shared memory space between threads
- Lightweight compared to processes
- Efficient for parallel computation

The pthread library is commonly used in Unix-like operating systems (Linux, macOS, etc.) for multi-threaded programming.
