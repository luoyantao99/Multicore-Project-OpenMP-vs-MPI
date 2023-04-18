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
    int my_rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    size_t global_sum = 0;
    size_t *arr = NULL;

    int chunk_size = N / size;
    size_t *local_arr = malloc(chunk_size * sizeof(size_t));

    double start_time;

    if (my_rank == 0) {
        arr = malloc(N * sizeof(size_t));
        initialize_array(arr, N);
        start_time = MPI_Wtime();
        MPI_Scatter(arr, chunk_size, MPI_UNSIGNED_LONG_LONG, local_arr, chunk_size, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
        free(arr);
    }
    else {
        MPI_Scatter(arr, chunk_size, MPI_UNSIGNED_LONG_LONG, local_arr, chunk_size, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    }

    size_t local_sum = 0;
    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_arr[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    
    if (my_rank == 0) {
        printf("Execution time with MPI: %f seconds\n", end_time - start_time);
        printf("Sum: %.zu\n", global_sum);
    }

    
    MPI_Finalize();
    return 0;
}