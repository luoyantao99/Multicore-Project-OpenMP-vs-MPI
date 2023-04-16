#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
load mpi
module load mpi/openmpi-4.1

compile
mpicc -g -Wall -std=c99 -o thread_creation_MPI thread_creation_MPI.c -lm

execute
mpiexec -n <number of processes to be created> ./reduction_MPI
*/

int dummy_function() {
    int x = 42;
    return x;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int NUM_PROCESSES = atoi(argv[2]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != NUM_PROCESSES) {
        if (rank == 0) {
            printf("Error: Run the MPI program with %d processes using 'mpirun -np %d <executable>'\n", NUM_PROCESSES, NUM_PROCESSES);
        }
        MPI_Finalize();
        return 1;
    }

    dummy_function();

    MPI_Finalize();
    return 0;
}
