# Parallel programming using POSIX Threads (Pthreads)

## Key Concepts :

### 1. **Shared Memory Multiprocessor Architectures**

* This refers to computer systems where **multiple CPUs share the same memory**.
* These CPUs (or **cores**) can run different parts of a program at the same time — this is called **parallelism**.

### 2. **Threads**

* A **thread** is a "lightweight" process.
* It is the smallest unit of execution in a program.
* In shared memory systems, threads **share the same memory space**.
* Threads are useful for **parallelizing tasks** to run faster.

### 3. **POSIX Threads (Pthreads)**

* POSIX = **Portable Operating System Interface**, a standard defined for Unix systems.
* Pthreads = A **standardized API** (Application Programming Interface) for thread programming in **C**.
* Before POSIX, thread implementations were different for each hardware vendor, making programs **non-portable**.
* POSIX made thread programming **portable and standard**.

## Pthreads API: The 3 Major Parts

1. **Thread Management**
   * Create, run, wait for, and manage threads.
   * E.g., `pthread_create()`, `pthread_join()`
2. **Mutex Variables**
   * **Mutual exclusion locks** to protect shared data from concurrent access.
   * Prevents **race conditions** (when two threads change the same data at the same time).
3. **Condition Variables**
   * Used for **synchronizing threads**.
   * Lets threads **wait** for some condition to become true before continuing.
