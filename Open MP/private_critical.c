#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
    clock_t start, end;
    double cpu_time_used;
    const int N = 1000000;
    int A[N], B[N];
    long long sum = 0;

    for (int i = 0; i < N; i++)
    {
        A[i] = i;
        B[i] = i;
    }

    start = clock();

    #pragma omp parallel
    {
        long long local_sum = 0;

        #pragma omp for
        for (int i = 0; i < N; i++){
            local_sum += (A[i] + B[i]);
        }

        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    end = clock();
    printf("Total sum: %lld\n", sum);
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f sec\n", cpu_time_used);

    return 0;
}