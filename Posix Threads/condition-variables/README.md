# Condition Variables Overview

### What are Condition Variables?

* They allow threads to **wait for a specific condition** (based on data values) without constantly polling.
* Always used **together with a mutex** to protect shared data and avoid race conditions.
* Help **synchronize threads efficiently** by blocking and waking threads only when the condition is met.

### Typical Usage Flow

**Main Thread:**

* Initialize shared data, mutex, and condition variable.
* Create threads A and B.

**Thread A (Waiter):**

1. Lock the mutex.
2. Check the condition on shared data.
3. If condition is **not met**, call `pthread_cond_wait()`:
   * This atomically **unlocks** the mutex and blocks the thread.
4. When signaled, `pthread_cond_wait()` returns and **re-locks** the mutex.
5. Unlock the mutex and continue.

**Thread B (Signaler):**

1. Lock the mutex.
2. Change the shared data to satisfy the condition.
3. Signal the condition variable with `pthread_cond_signal()` (or broadcast if multiple threads).
4. Unlock the mutex.

### Why Use Condition Variables?

* **Avoid busy waiting (polling):** threads sleep instead of constantly checking a variable.
* **Ensure correct ordering and synchronization** based on actual data states.

## Creating and Destroying Condition Variables

* **Declaration:**
  Condition variables use the type `pthread_cond_t`.
* **Initialization:**
  Two ways to initialize:

  1. **Static initialization:**

     ```c
     pthread_cond_t myconvar = PTHREAD_COND_INITIALIZER;
     ```
  2. **Dynamic initialization:**

     ```c
     pthread_cond_t myconvar;
     pthread_cond_init(&myconvar, NULL);
     ```

     The second argument can be used to specify attributes, typically `NULL` for defaults.
* **Attributes (`pthread_condattr_t`):**
  Only one attribute currently defined:

  * `process-shared` — allows the condition variable to be shared across processes (not just threads).

  You can initialize/destroy the attribute object using:

  ```c
  pthread_condattr_t attr;
  pthread_condattr_init(&attr);
  // Set attributes if needed
  pthread_condattr_destroy(&attr);
  ```
* **Destroying:**
  Once you’re done with a condition variable:

  ```c
  pthread_cond_destroy(&myconvar);
  ```

  This frees resources associated with it.


# Waiting and Signaling on Condition Variables

### Key Routines

* **`pthread_cond_wait(condition, mutex)`**
  * Called with `mutex` locked.
  * Atomically unlocks the mutex and blocks the thread until the condition is signaled.
  * When awakened, it re-locks the mutex before returning.
  * The caller must unlock the mutex after `pthread_cond_wait()` returns.
* **`pthread_cond_signal(condition)`**
  * Wakes **one** thread waiting on the condition variable.
  * Should be called **with the mutex locked**.
  * Unlock the mutex afterward to allow the awakened thread to proceed.
* **`pthread_cond_broadcast(condition)`**
  * Wakes **all** threads waiting on the condition variable.
  * Used if multiple threads may be waiting for the same condition.

### Important Usage Notes

* Always lock the mutex **before** calling `pthread_cond_wait()` or `pthread_cond_signal()`.
* `pthread_cond_wait()` should be inside a **`while` loop** checking the condition, *not* an `if` statement. This handles spurious wake-ups and rechecks the condition properly.
* Calling `pthread_cond_signal()`**before** any thread is waiting (before `pthread_cond_wait()`) is a logical error; the signal will be lost, and threads will block indefinitely.
* Proper unlocking of the mutex after signaling is crucial, or waiting threads can remain blocked.

### Why use a **while** loop?

```c
pthread_mutex_lock(&mutex);
while (condition_is_false) {
    pthread_cond_wait(&condition, &mutex);
}
// Proceed knowing condition is true
pthread_mutex_unlock(&mutex);
```

* Handles spurious wakeups where `pthread_cond_wait()` returns even though no signal was sent.
* Ensures condition is still true after waking, especially when multiple threads wait on the same condition.
