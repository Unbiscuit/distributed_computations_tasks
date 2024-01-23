#include <cstdio>
#include <mpi.h>
#include <cstdlib>

void dialog_sync(int argc, char **argv){
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 100;
    char* send_buf = (char*)malloc(n);
    char* recv_buf = (char*)malloc(n);
    double start_time, end_time;

    for (int i = 0; i < n; ++i) {
        send_buf[i] = (char)('A' + rank);
    }

    if (rank == 0){
        start_time = MPI_Wtime();
    }

    for (int iter = 0; iter < 5; ++iter) {
        MPI_Sendrecv(send_buf, n, MPI_CHAR, (rank + 1) % size, 0,
                     recv_buf, n, MPI_CHAR, (rank - 1 + size) % size, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        /*printf("Процесс %d получил сообщение: %.*s\n", rank, n, recv_buf);*/

        char* temp = send_buf;
        send_buf = recv_buf;
        recv_buf = temp;
    }

    if (rank == 0) {
        end_time = MPI_Wtime();

        printf("%f\n", end_time - start_time);
    }

    free(send_buf);
    free(recv_buf);
}

void dialog(int argc, char **argv){
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 100;
    char* send_buf = (char*)malloc(n);
    char* recv_buf = (char*)malloc(n);
    double start_time, end_time;

    for (int i = 0; i < n; ++i) {
        send_buf[i] = (char)('A' + rank);
    }

    if (rank == 0){
        start_time = MPI_Wtime();
    }

    for (int iter = 0; iter < 5; ++iter) {

        if (rank == 0){
            printf("%d: sending %s to %d\n", rank, send_buf, 1);
            MPI_Send(send_buf, n, MPI_CHAR, 1, 1, MPI_COMM_WORLD);

            printf("%d: receiving from %d\n", rank, 1);
            MPI_Recv(recv_buf, n, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }else{
            printf("%d: receiving from %d\n", rank, 0);
            MPI_Recv(recv_buf, n, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("%d: sending %s to %d\n", rank, send_buf, 0);
            MPI_Send(send_buf, n, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        }

        // printf("Процесс %d получил сообщение: %.*s\n", rank, n, recv_buf);

        char* temp = send_buf;
        send_buf = recv_buf;
        recv_buf = temp;
    }

    if (rank == 0) {
        end_time = MPI_Wtime();

        // Calculate and print the elapsed time
        printf("%f\n", end_time - start_time);
    }

    free(send_buf);
    free(recv_buf);
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);
    dialog(argc, argv);
    MPI_Finalize();

    return 0;
}