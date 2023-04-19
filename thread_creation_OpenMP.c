#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
compile
gcc -fopenmp -Wall -std=c99 -o thread_creation_OpenMP thread_creation_OpenMP.c

execute
time ./thread_creation_OpenMP <number of thread creation calls>
*/

int dummy_function() {
    int x = 42;
    return x;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./thread_creation_OpenMP <number of thread creation calls>\n");
        return 1;
    }

    double start_time = omp_get_wtime();
    int NUM_THREADS = atoi(argv[1]);

    for (int i = 0; i < NUM_THREADS; ++i) {
        #pragma omp parallel num_threads(2)
        dummy_function();
    }

    double end_time = omp_get_wtime();
    printf("Execution time with OpenMP (creating %d threads): %lf seconds\n", NUM_THREADS, end_time - start_time);

    return 0;
}
