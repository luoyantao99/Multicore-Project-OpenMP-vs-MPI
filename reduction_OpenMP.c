#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000

void initialize_array(double *arr) {
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 100;
    }
}

int main() {
    double *arr = malloc(N * sizeof(double));
    double sum = 0.0;

    initialize_array(arr);

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += arr[i];
    }

    double end_time = omp_get_wtime();
    printf("Execution time with OpenMP: %lf seconds\n", end_time - start_time);
    printf("Sum: %lf\n", sum);

    free(arr);
    
    return 0;
}