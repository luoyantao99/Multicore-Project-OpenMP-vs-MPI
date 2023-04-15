#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 100000000

/*
load mpi
module load mpi/openmpi-x86_64

compile
mpicc -g -Wall -std=c99 -o reduction_MPI reduction_MPI.c -lm

execute
time mpiexec -n 4 ./reduction_MPI
*/

void initialize_array(double *arr) {
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 100;
    }
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double *arr = malloc(N * sizeof(double));
    double local_sum = 0.0, global_sum = 0.0;

    if (rank == 0) {
        initialize_array(arr);
    }

    MPI_Bcast(arr, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    int chunk_size = N / size;
    for (int i = rank * chunk_size; i < (rank + 1) * chunk_size; ++i) {
        local_sum += arr[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    
    if (rank == 0) {
        printf("Execution time with MPI: %lf seconds\n", end_time - start_time);
        printf("Sum: %lf\n", global_sum);
    }

    free(arr);
    MPI_Finalize();

    return 0;
}