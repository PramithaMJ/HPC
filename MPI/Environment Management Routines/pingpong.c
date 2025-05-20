#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numtasks, rank, dest, source, rc, count, tag = 1;
    char inmsg, outmsg = 'x';
    MPI_Status Stat; // required variable for receive routines

    MPI_Init(&argc, &argv);                   // Start MPI
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // Total number of tasks
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);     // My rank

    // Ensure only 2 processes run this
    if (numtasks != 2)
    {
        if (rank == 0)
        {
            printf("Please run with exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        dest = 1;
        source = 1;
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
    }
    else if (rank == 1)
    {
        dest = 0;
        source = 0;
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }

    // Inspect received message
    MPI_Get_count(&Stat, MPI_CHAR, &count);
    printf("Task %d: Received %d char(s) from task %d with tag %d\n",
           rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

    MPI_Finalize(); // Close MPI
    return 0;
}
