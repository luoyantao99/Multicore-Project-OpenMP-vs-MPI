#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
load mpi
module load gcc-12.2
module load mpi/openmpi-4.1

compile
mpicc -g -Wall -std=c99 -o thread_creation_MPI thread_creation_MPI.c -lm

execute
mpiexec -n <number of processes to be created> ./thread_creation_MPI
*/

int dummy_function() {
    int x = 42;
    return 0;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int NUM_PROCESSES = atoi(argv[2]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();
    dummy_function();
    double end_time = MPI_Wtime();
    
    if (rank == 0) {
        printf("Execution time with MPI: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
