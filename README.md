# Comparing Parallel Programming Languages: OpenMP vs MPI

Parallel computing has become an essential technique to achieve high-performance computing for large-scale scientific and engineering applications. Two popular parallel models are OpenMP, which stands for Open Multi-Processing, and MPI, which stands for Message Passing Interface. These models can help programmers divide a task into smaller pieces and utilize multi processors for better performance. Both models are widely used in modern high performance computing. 

From former research we know that OpenMP is more programmable and less overhead when creating and destroying workers. However, what is the scale of the difference? It is known that OpenMP is easier to program, but can we have a more clear view on how much easier it is? What about the scalability differences between those two parallel programming models? In this project, we will measure the differences and provide a deeper insight in OpenMP and MPI performance. We will discuss the advantages and disadvantages of each parallel model and provide insights into which model is better suited for specific types of applications. This will help choose the appropriate parallel model for specific applications and achieve better performance and scalability. 


## Running Benchmarks

In order to run the benchmarks we must first compile the corresponding OpenMP and MPI programs. Then we can run a benchmark with the specified number of threads/processes and problem size:

### Reduction Benchmark: 
```
gcc -fopenmp -Wall -std=c99 -o reduction_OpenMP reduction_OpenMP.c -lm
mpicc -g -Wall -std=c99 -o reduction_MPI reduction_MPI.c -lm
```
```
./reduction_OpenMP <number_of_threads> <array_length>
mpiexec -n <number_of_processes> ./reduction_MPI <array_length>
```

### Matrix Multiplication Benchmark: 
```
gcc -fopenmp -Wall -std=c99 -o matrix_OpenMP matrix_multiplication_OpenMP.c
mpicc -g -Wall -std=c99 -o matrix_MPI matrix_multiplication_MPI.c -lm
```
```
./matrix_OpenMP <number_of_threads> <matrix_dimension>
mpiexec -n <number_of_processes> ./matrix_MPI <matrix_dimension>
```

### Overhead Benchmark: 
```
gcc -fopenmp -Wall -std=c99 -o thread_creation_OpenMP thread_creation_OpenMP.c
mpicc -g -Wall -std=c99 -o thread_creation_MPI thread_creation_MPI.c -lm
```
```
./thread_creation_OpenMP <number of thread creation calls>
mpiexec -n <number of processes to be created> ./thread_creation_MPI
```

## Results

Below we include some of the results of the experiments:

![Alt text](https://github.com/luoyantao99/Multicore-Project-OpenMP-vs-MPI/blob/main/img/Reduction%20Benchmark%204.png)
