#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
load mpi
module load mpi/openmpi-x86_64

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

    double start_time = MPI_Wtime();

    dummy_function();

    double end_time = MPI_Wtime();
    if (rank == 0) {
        printf("Execution time with MPI (creating %d processes): %lf seconds\n", NUM_PROCESSES, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
