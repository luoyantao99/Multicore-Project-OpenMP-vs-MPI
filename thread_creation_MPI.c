#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_PROCESSES 100000

void dummy_function() {
    int x = 42;
}

int main(int argc, char *argv[]) {
    int rank, size;

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