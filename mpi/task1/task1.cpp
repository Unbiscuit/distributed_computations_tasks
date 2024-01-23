#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include "vector"

int find_min(int argc, char **argv){
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 1000000;
    std::vector<int> vec(N);
    double start_time, end_time;

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            vec[i] = rand() % 100;
        }
        start_time = MPI_Wtime();
    }

    int part_size = N / size;
    std::vector<int> part(part_size);
    MPI_Scatter(vec.data(), part_size, MPI_INT, part.data(), part_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_min = part[0];
    for (int i = 1; i < part_size; ++i) {
        if (part[i] < local_min) {
            local_min = part[i];
        }
    }

    int global_min;
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end_time = MPI_Wtime();

        // Calculate and print the elapsed time
        printf("Elapsed time: %f seconds\n", end_time - start_time);
    }

    return local_min;
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);
    find_min(argc, argv);
    MPI_Finalize();

    return 0;
}