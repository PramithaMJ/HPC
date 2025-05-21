# What is an OpenMP Directive in C/C++?

In OpenMP, **directives** are **special instructions to the compiler** that tell it how to run parts of your code in parallel using multiple threads.

In C/C++, these are written using the `#pragma` keyword.

## Basic Format of a Directive

```c
#pragma omp <directive-name> [clause, ...]
{
    // Structured block of code
}
```

* `#pragma omp` — Always starts with this.
* `<directive-name>` — What kind of OpenMP behavior you're specifying (e.g., `parallel`, `for`, `sections`).
* `[clause, ...]` — Optional modifiers that control *how* the parallelism works (e.g., `private(x)`, `shared(y)`).
* `{ ... }` — A structured block of code (i.e., code that follows good block structure with a single entry and exit point).

## Example

```c
#pragma omp parallel default(shared) private(beta, pi)
{
    // Code inside here runs in parallel
}
```

### Explanation:

* `parallel`: Create multiple threads.
* `default(shared)`: By default, all variables are shared.
* `private(beta, pi)`: These two variables are private to each thread.

## General Rules

1. **Case-sensitive**
   `#pragma omp parallel` ≠ `#pragma OMP Parallel`
2. Only one directive-name per line
   Invalid: `#pragma omp parallel for sections`
   Valid: `#pragma omp parallel for`
3. **Applies to only one structured block**
   That means a single loop, statement, or `{ ... }` block.
4. **Line continuation supported**
   If a directive is long, you can split it like this:
   ```c
   #pragma omp parallel \
       default(shared) private(i,j)
   ```

## Structured Block (What Is It?)

A **structured block** is any block of code with:

* A clear beginning and end (like a loop or `{ ... }` block)
* No `goto`, `return`, `break` that jumps out

Example of a structured block:

```c
{
    sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
}
```

## Summary (Quick Facts)


| Rule              | Description                            |
| ----------------- | -------------------------------------- |
| Starts with       | `#pragma omp`                          |
| Case              | **Case-sensitive**                     |
| One directive     | per line only                          |
| Block required    | Must be a structured block             |
| Clauses           | Optional, can be repeated or reordered |
| Line continuation | Use`\`to continue on next line         |


## What Is "Directive Scoping" in OpenMP?

Scoping helps determine:

* Where a directive is valid.
* Which code sections are affected by a directive.
* Whether other directives are "linked" to it or not.

There are **three types** of scope (or *extent*) in OpenMP:

### **Static (Lexical) Extent**

Definition:
This is the part of the code that is **textually enclosed** by a directive.

 Example:

```fortran
!$OMP PARALLEL
   ! All this is inside the static extent of PARALLEL
   CALL SUB1
!$OMP END PARALLEL
```

 Characteristics:

* Starts right after the directive.
* Ends at its matching `END` directive.
* **Does NOT span across functions, subroutines, or files.**

### **Orphaned Directives**

Definition:
A directive that is **not within the static extent** of any other directive — usually because it's in a different subroutine or file — is called **orphaned**.

Example:

```fortran
SUBROUTINE SUB1
   !$OMP CRITICAL
       ! Critical region
   !$OMP END CRITICAL
END
```

This `CRITICAL` section in `SUB1` is **orphaned** — it's **not textually inside** the `PARALLEL` region from the calling code.

### **Dynamic Extent**

Definition:
Dynamic extent includes:

* The **static extent**
* **Plus** any **orphaned directives** that are **executed within that parallel region** at runtime.

Real  fortran Example:

```fortran
PROGRAM TEST
   !$OMP PARALLEL
       CALL SUB1     ! This runs inside the dynamic extent of PARALLEL
   !$OMP END PARALLEL

SUBROUTINE SUB1
   !$OMP CRITICAL
      ! Protected region
   !$OMP END CRITICAL
END
```

The `CRITICAL` directive in `SUB1` is not inside the static extent of `PARALLEL`,
**but because it runs inside the `PARALLEL` region at runtime, it is in the dynamic extent.**

## Why Does This Matter?

* OpenMP has **rules** about **which directives can be inside others**.
* If you misuse nesting or scoping:
  * You could get **unexpected behavior**, or
  * The code might be **invalid** (won’t compile or run properly).

Following scope rules ensures your parallel logic is **valid**, **efficient**, and **thread-safe**.

## Summary Table


| Scope Type         | Description                                                                  |
| ------------------ | ---------------------------------------------------------------------------- |
| Static Extent      | Textually inside a directive block. Doesn’t cross function/file boundaries. |
| Orphaned Directive | Outside the static extent but used inside a parallel execution context.      |
| Dynamic Extent     | Runtime execution context – includes static + orphaned executed directives. |


# What is a Parallel Region in OpenMP?

A **parallel region** is a block of code that runs **simultaneously by multiple threads**.
It's the **core feature** of OpenMP and enables **multithreading**.

## Syntax

### C/C++:

```c
#pragma omp parallel [clauses]
{
    // Parallel code block
}
```

### Fortran:

```fortran
!$OMP PARALLEL [clauses]
   ! Parallel code block
!$OMP END PARALLEL
```

## Clauses


| Clause               | Purpose                                                               |
| -------------------- | --------------------------------------------------------------------- |
| `private(list)`      | Each thread gets its own copy of listed variables.                    |
| `shared(list)`       | Variables shared across all threads.                                  |
| default(shared)      |                                                                       |
| `firstprivate(list)` | Variables initialized from master thread, but private to each thread. |
| `reduction(op:list)` | Reduces a variable using an operator (e.g., sum) across all threads.  |
| `copyin(list)`       | Copies values of master’s threadprivate variables to all threads.    |
| `num_threads(n)`     | Requests`n`threads for this region.                                   |
| `if(condition)`      | If false, the region runs serially by the master thread.              |

## How It Works

1. **Master thread** hits the `parallel` directive.
2. **Team of threads** is created.
3. All threads **run the same code block** concurrently.
4. After the block ends, there's an **implicit barrier** — all threads sync up.
5. Execution continues **only with the master** thread after the barrier.

## How Many Threads Will Be Created?

OpenMP checks for the number of threads in this order:

1. `if()` clause result (false = serial execution).
2. `num_threads(n)` clause.
3. Call to `omp_set_num_threads(n)`.
4. Environment variable `OMP_NUM_THREADS`.
5. **Implementation default** (usually # of CPUs).

**Thread IDs** range from `0` (master) to `N-1`.

## Dynamic Threads

If supported:

* Use `omp_set_dynamic()` or set `OMP_DYNAMIC=TRUE` to allow OpenMP to adjust thread count at runtime.
* Use `omp_get_dynamic()` to query if it's enabled.

## Restrictions

* Must be a **structured block**: cannot `goto` in/out.
* Cannot span multiple functions or files.
* Only **one**`if` clause and **one**`num_threads` clause allowed.
* Clause order doesn’t matter.

## Example

```c
#include <omp.h>
#include <stdio.h>

int main() {
    int tid, nthreads;

    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("Hello from thread = %d\n", tid);

        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Total threads = %d\n", nthreads);
        }
    }
    return 0;
}
```

## Summary

* A **parallel region** is the basic building block of OpenMP parallelism.
* It’s simple to use: just wrap your code with `#pragma omp parallel`.
* Use **clauses** to fine-tune data sharing and thread behavior.
* Understand **scoping, barriers, and thread limits** to write safe and efficient code.
