## **Concept Summary: What Are Environment Management Routines in MPI?**

These are **MPI functions** that let each process:

* Join the MPI environment (`MPI_Init`)
* Know **how many** processes there are (`MPI_Comm_size`)
* Know **which process** it is (`MPI_Comm_rank`)
* Know **what machine** it’s running on (`MPI_Get_processor_name`)
* Stop MPI safely (`MPI_Finalize`)
* And a few extras for diagnostics and performance

---

## Step-by-Step MPI Program: Explained With Environment Routines

We'll break it down and explain **each line** in an MPI C program:

```c
#include "mpi.h"        // Include MPI library
#include <stdio.h>      // Standard I/O

int main(int argc, char *argv[]) {
    int numtasks, rank, len;          // Variables to store task info
    char hostname[MPI_MAX_PROCESSOR_NAME]; // To hold machine name

    MPI_Init(&argc, &argv); //  Step 1: Start MPI

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // Step 2: How many processes are running
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);     // Step 3: What is MY process rank (ID)

    MPI_Get_processor_name(hostname, &len);   // Step 4: On which machine is this process running

    // Step 5: Print info about this process
    printf("Number of tasks = %d, My rank = %d, Running on %s\n", 
           numtasks, rank, hostname);

    // Step 6: Stop MPI environment safely
    MPI_Finalize();

    return 0;
}
```

---

## Key MPI Functions Just Used


| Function                 | What It Does                                            |
| ------------------------ | ------------------------------------------------------- |
| `MPI_Init`               | Starts the MPI environment (must be first)              |
| `MPI_Comm_size`          | Gets total number of MPI processes                      |
| `MPI_Comm_rank`          | Gets the current process's rank (0 to N-1)              |
| `MPI_Get_processor_name` | Gets the name of the machine this process is running on |
| `MPI_Finalize`           | Cleans up and ends the MPI program                      |

---

## How to Run It?

1. Save it as `env_info.c`
2. Compile:

   ```bash
   mpicc env_info.c -o env_info
   ```
3. Run on 4 processes:

   ```bash
   mpirun -np 4 ./env_info
   ```

### Output (may vary by system):

```
Number of tasks = 4, My rank = 0, Running on node1
Number of tasks = 4, My rank = 1, Running on node2
Number of tasks = 4, My rank = 2, Running on node3
Number of tasks = 4, My rank = 3, Running on node4
```

---

## Summary: You Now Know

* How MPI programs start (`MPI_Init`) and end (`MPI_Finalize`)
* How each process knows **how many** there are and **who** it is
* How to print from each process
* How to get the machine name

---
