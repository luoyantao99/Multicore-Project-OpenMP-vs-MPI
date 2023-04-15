#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

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

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double *A = malloc(N * N * sizeof(double));
    double *B = malloc(N * N * sizeof(double));
    double *C = malloc(N * N * sizeof(double));

    if (rank == 0) {
        initialize_matrices(A, B, C);
    }

    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, N * N / size, MPI_DOUBLE, A + (rank * N * N / size), N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    for (int i = 0; i < N / size; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    MPI_Gather(C + (rank * N * N / size), N * N /