#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
    clock_t start, end;
    double cpu_time_used;
    const int N = 100;
    int A[N], B[N];
    long long sum = 0;
    int num_threads = 4; // Set the desired number of threads

    // Set the number of threads
    omp_set_num_threads(num_threads);
    printf("Using %d threads\n", num_threads);

    // Initialize arrays
    for (int i = 0; i < N; i++)
    {
        A[i] = i;
        B[i] = i;
    }

    start = clock();

// Parallel sum computation using OpenMP
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < N; i++)
    {
        sum += (A[i] + B[i]);
    }

    end = clock();

    printf("Total sum: %lld\n", sum);
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}