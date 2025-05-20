## What is Non-blocking Communication in MPI?

In **blocking communication** (`MPI_Send`, `MPI_Recv`), a process **waits** until the operation is **finished**.

In **non-blocking communication**, you **start** the send/receive, and then **immediately continue** doing other work while the communication happens **in the background**.

Imagine:

* You're cooking dinner (`non-blocking`) while the laundry is running.
* With `blocking`, you would wait at the washing machine until it finishes.

## Why Use Non-blocking?

* To **overlap computation and communication**.
* To **avoid deadlocks** that might happen in tightly coupled send/receive calls.
* To make communication **more efficient** in large, distributed systems.

## The Key Non-blocking MPI Functions


| Function      | What it does                                         |
| ------------- | ---------------------------------------------------- |
| `MPI_Isend`   | Start sending data, don't wait for it to finish      |
| `MPI_Irecv`   | Start receiving data, don’t wait for it to arrive   |
| `MPI_Wait`    | Wait until a specific non-blocking operation is done |
| `MPI_Waitall` | Wait until**all**non-blocking operations are done    |
| `MPI_Test`    | Check if an operation is done without waiting        |
| `MPI_Iprobe`  | Peek: check if a message is available to receive     |

Each send/recv needs a **request object** (`MPI_Request`) so MPI can keep track of its progress.

## Visual Example: Ring Topology

Each process in a ring talks to its left and right neighbor.

### Step-by-step (in the C code you posted):

```c
int numtasks, rank, next, prev, buf[2], tag1=1, tag2=2;
MPI_Request reqs[4];
MPI_Status stats[4];
```

* `rank`: Who am I?
* `next`, `prev`: Who are my neighbors?
* `buf[2]`: Where I store what I receive.
* `reqs[4]`: MPI needs these to manage the 4 non-blocking operations.
  * 2 receives (from left and right)
  * 2 sends (to left and right)

### What the program does:

1. **Initialize MPI**, get your `rank`, total `numtasks`.
2. **Figure out neighbors** in the ring:

   * If you're `rank 0`, your left neighbor is the **last** one.
   * If you're the last, your right neighbor is `rank 0`.
3. **Post non-blocking receives:**

   * I want to get a message from `prev` and `next`, but I don't wait.

   ```c
   MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
   MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);
   ```
4. **Post non-blocking sends:**

   * Send my `rank` to neighbors.

   ```c
   MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
   MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);
   ```
5. **Do other work while messages fly.**
6. **Wait for all 4 operations to finish**:

   ```c
   MPI_Waitall(4, reqs, stats);
   ```
7. Now, it's safe to use `buf[0]` and `buf[1]`.

## Best Practices with Non-blocking

* Always call `MPI_Wait` or `MPI_Test` to ensure operations are done.
* Never touch the send/recv buffer until you're sure it’s complete.
* Can improve performance in compute-heavy applications.

## Simple Analogy


| Real World                    | MPI Non-blocking Equivalent           |
| ----------------------------- | ------------------------------------- |
| Put clothes in washer         | `MPI_Isend`/`MPI_Irecv`starts the job |
| Do other things (cook, study) | Your app continues computation        |
| Check if wash is done         | `MPI_Test`or`MPI_Wait`                |
| Fold dry clothes              | Use the data after it's ready         |

## Summary

* Non-blocking = Start and go.
* Use it when you can do useful work while communication is ongoing.
* Always finish with `MPI_Wait` or `MPI_Test`.
* Ideal for overlapping computation and communication.
