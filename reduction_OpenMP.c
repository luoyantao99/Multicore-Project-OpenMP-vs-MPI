#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

/*
compile
gcc -fopenmp -Wall -std=c99 -o reduction_OpenMP reduction_OpenMP.c

execute
time ./reduction_OpenMP N
*/

void initialize_array(double *arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }
}

int main() {
    if (argc != 2) {
        printf("Usage: ./reduction_OpenMP <array_length>\n");
        return 1;
    }
    int N = atoi(argv[1]);

    double *arr = malloc(N * sizeof(double));
    double sum = 0.0;

    initialize_array(arr, N);

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