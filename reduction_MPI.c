#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

/*
load mpi
module load mpi/openmpi-x86_64

compile
mpicc -g -Wall -std=c99 -o reduction_MPI reduction_MPI.c -lm

execute
time mpiexec -n 4 ./reduction_MPI 10000000
*/

void initialize_array(double *arr, int N) {
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

    
    double global_sum = 0.0;
    double *arr = NULL;

    int chunk_size = N / size;
    double *local_arr = malloc(chunk_size * sizeof(double));

    double start_time;

    if (my_rank == 0) {
        arr = malloc(N * sizeof(double));
        initialize_array(arr, N);
        start_time = MPI_Wtime();
        MPI_Scatter(arr, chunk_size, MPI_DOUBLE, local_arr, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        free(arr);
    }
    else {
        MPI_Scatter(arr, chunk_size, MPI_DOUBLE, local_arr, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    double local_sum = 0.0;
    for (int i = 0; i < chunk_size; i++) {
        local_sum += sin(local_arr[i]) + cos(local_arr[i]);
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    
    if (my_rank == 0) {
        printf("%f\n", end_time - start_time);
        // printf("Execution time with MPI: %f seconds\n", end_time - start_time);
        // printf("Sum: %f\n", global_sum);
    }

    
    MPI_Finalize();
    return 0;
}