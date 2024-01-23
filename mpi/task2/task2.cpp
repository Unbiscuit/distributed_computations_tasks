#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include "vector"

int vec_mul(int argc, char **argv){
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 10000000;
    std::vector<int> vec_a(n);
    std::vector<int> vec_b(n);
    double start_time, end_time;

    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            vec_a[i] = rand() % 10;
            vec_b[i] = rand() % 10;
        }
        start_time = MPI_Wtime();
    }

    int part_size = n / size;
    std::vector<int> part_a(part_size);
    std::vector<int> part_b(part_size);
    MPI_Scatter(vec_a.data(), part_size, MPI_INT, part_a.data(), part_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vec_b.data(), part_size, MPI_INT, part_b.data(), part_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_dot_product = 0;
    for (int i = 0; i < part_size; ++i) {
        local_dot_product += part_a[i] * part_b[i];
    }

    int global_dot_product;
    MPI_Reduce(&local_dot_product, &global_dot_product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        end_time = MPI_Wtime();

        // Calculate and print the elapsed time
        printf("%f\n", end_time - start_time);
    }
    return global_dot_product;
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);
    vec_mul(argc, argv);
    MPI_Finalize();

    return 0;
}