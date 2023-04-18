#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

/*
load mpi
module load mpi/openmpi-x86_64

compile
mpicc -g -Wall -std=c99 -o matrix_MPI matrix_multiplication_MPI.c -lm

execute
time mpiexec -n 4 ./matrix_MPI 1000
*/


void initialize_matrices(double *A, double *B, double *C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i * N + j] = i;
            B[i * N + j] = j;
            C[i * N + j] = 0.0;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: mpiexec -n <number_of_processes> ./matrix_MPI <matrix_dimension>\n");
        return 1;
    }
    int N = atoi(argv[1]);

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double *A = malloc(N * N * sizeof(double));
    if(!A) {
        printf("Error allocating array A\n");
        exit(1);
	}
    double *B = malloc(N * N * sizeof(double));
    if(!B) {
        printf("Error allocating array B\n");
        exit(1);
	}
    double *C = malloc(N * N * sizeof(double));
    if(!C) {
        printf("Error allocating array C\n");
        exit(1);
	}

    if (rank == 0) {
        initialize_matrices(A, B, C, N);
    }

    double start_time = MPI_Wtime();

    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, N * N / size, MPI_DOUBLE, A + (rank * N * N / size), N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < N / size; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
    
    MPI_Gather(C + (rank * N * N / size), N * N / size, MPI_DOUBLE, C, N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("%f\n", end_time - start_time);
        // printf("Matrix Multiplication Execution Time (MPI): %f seconds\n", end_time - start_time);
    }

    free(A);
    free(B);
    free(C);

    MPI_Finalize();
    return 0;
}
