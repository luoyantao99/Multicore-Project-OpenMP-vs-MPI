#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 100000

void dummy_function() {
    int x = 42;
}

int main() {
    double start_time = omp_get_wtime();

    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < NUM_THREADS; ++i) {
        dummy_function();
    }

    double end_time = omp_get_wtime();
    printf("Execution time with OpenMP (creating %d threads): %lf seconds\n", NUM_THREADS, end_time - start_time);

    return 0;
}