#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

int main(int argc, char** argv) {
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    // Begin real work here

    if (argc != 2) {
        printf("Usage: ./a.out N\n");
        MPI_Finalize();
        return 1;
    }

    // The number of numbers to generate
    int N = atoi(argv[1]);

    // Allocation in C does not use new
    int* numbers = (int*)malloc(N*sizeof(int));

    if (myRank > 0) {
        // Worker section
        printf("I am node %d and I will generate %d numbers!\n", myRank, N);

        int i;
        for (i = 0; i < N; i++) {
            numbers[i] = rand() % 10;
        }

        /* For seeing each node's array individually
        for (i = 0; i < N; i++) {
            printf("%d ", numbers[i]);
        }
        puts("");
        */

        // Prototype:
        // int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
        MPI_Reduce(numbers, NULL, N, MPI_INT, MPI_SUM, 0, world);

        // De-allocate
        free(numbers);
    } else {
        // Root section
        MPI_Reduce(NULL, numbers, N, MPI_INT, MPI_SUM, 0, world);
        int i;
        puts("Final array:");
        for (i = 0; i < N; i++) {
            printf("%d ", numbers[i]);
        }
        puts("");
    }

    MPI_Finalize();

    return 0;
}
