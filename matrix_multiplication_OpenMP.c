#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1024

void initialize_matrices(double *A, double *B, double *C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i * N + j] = rand() % 100;
            B[i * N + j] = rand() % 100;
            C[i * N + j] = 0.0;
        }
    }
}

int main() {
    double *A = malloc(N * N * sizeof(double));
    double *B = malloc(N * N * sizeof(double));
    double *C = malloc(N * N * sizeof(double));

    initialize_matrices(A, B, C);

    double start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Execution time with OpenMP: %lf seconds\n", end_time - start_time);

    free(A);
    free(B);
    free(C);
    
    return 0;
}