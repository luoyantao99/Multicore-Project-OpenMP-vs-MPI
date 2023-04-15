#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>




/*
compile
gcc -fopenmp -Wall -std=c99 -o matrix_OpenMP matrix_multiplication_OpenMP.c

execute
time ./matrix_OpenMP <number_of_threads> <matrix_dimension>
*/


void initialize_matrices(double *A, double *B, double *C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i * N + j] = rand() % 100;
            B[i * N + j] = rand() % 100;
            C[i * N + j] = 0.0;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./matrix_OpenMP <number_of_threads> <matrix_dimension>\n");
        return 1;
    }
    int N = atoi(argv[2]);

    double *A = malloc(N * N * sizeof(double));
    double *B = malloc(N * N * sizeof(double));
    double *C = malloc(N * N * sizeof(double));

    initialize_matrices(A, B, C, N);

    double start_time = omp_get_wtime();
    
    omp_set_num_threads(atoi(argv[1]));
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Matrix Multiplication Execution Time (OpenMP): %.3f seconds\n", end_time - start_time);

    free(A);
    free(B);
    free(C);
    
    return 0;
}