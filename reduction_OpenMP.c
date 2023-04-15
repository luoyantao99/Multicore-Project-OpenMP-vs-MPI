#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

/*
compile
gcc -fopenmp -Wall -std=c99 -o reduction_OpenMP reduction_OpenMP.c

execute
time ./reduction_OpenMP <number_of_threads> <array_length>
*/

void initialize_array(size_t *arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./reduction_OpenMP <number_of_threads> <array_length>\n");
        return 1;
    }
    int N = atoi(argv[2]);

    size_t *arr = malloc(N * sizeof(size_t));
    size_t sum = 0;

    initialize_array(arr, N);

    double start_time = omp_get_wtime();

    omp_set_num_threads(atoi(argv[1]));
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += arr[i];
    }

    double end_time = omp_get_wtime();
    printf("Execution time with OpenMP: %f seconds\n", end_time - start_time);
    printf("Sum: %zu\n", sum);

    free(arr);
    
    return 0;
}