#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

/*
load mpi
module load mpi/openmpi-x86_64

compile
mpicc -g -Wall -std=c99 -o reduction_MPI reduction_MPI.c -lm

execute
time mpiexec -n 4 ./reduction_MPI 10000000
*/

void initialize_array(size_t *arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: mpiexec -n <number_of_processes> ./reduction_MPI <array_length>\n");
        return 1;
    }
    int N = atoi(argv[1]);
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    size_t *arr = malloc(N * sizeof(size_t));
    size_t local_sum = 0, global_sum = 0;

    if (rank == 0) {
        initialize_array(arr, N);
    }

    MPI_Bcast(arr, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // double start_time = MPI_Wtime();

    int chunk_size = N / size;
    for (int i = rank * chunk_size; i < (rank + 1) * chunk_size; ++i) {
        local_sum += arr[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // double end_time = MPI_Wtime();
    
    // if (rank == 0) {
    //     printf("Execution time with MPI: %f seconds\n", end_time - start_time);
    //     printf("Sum: %zu\n", global_sum);
    // }

    free(arr);
    MPI_Finalize();

    return 0;
}