#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<string.h>

int main(int argc, char** argv) {

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

    srand(time(NULL) + myRank); // Offset by the node's rank so that each node will have different data

    // The number of numbers to generate
    int N = atoi(argv[1]);

    // Allocation in C does not use new
    int* numbers = (int*)malloc(N*sizeof(int));
    int i;

    /*
     * Purely to allow printing the whole array
     * in a thread-safe way
     *
     * If we just printf one-by-one, the numbers will
     * get mixed up between the nodes all competing for
     * stdout
     */
    // Only safe for N < 80 and 2-digit randoms
    char buf[256];
    char tmp[3];
    // Basically does buf.join(" ");
    for (i = 0; i < N; i++) {
        numbers[i] = rand() % 10;
        sprintf(tmp, "%d ", numbers[i]);
        // sad panda ;(
        strcat(buf, tmp);
    }

    printf("I am node %d and my numbers are %s\n", myRank, buf);

    /* int MPI_Reduce(const void* sendbuf,
     *  void* recvbuf,
     *  int count,
     *  MPI_Datatype datatype,
     *  MPI_Op op,
     *  int root,
     *  MPI_Comm comm);
     */

    int* result = NULL;

    if (myRank == 0) {
        result = (int*)malloc(N*sizeof(int));
    }

    // Everybody (including root) participates/calls this.
    // The recvbuf only matters for the root
    // computes the element-wise sum of each vector of N numbers

    // Stores reusult on the root's result array
    MPI_Reduce(numbers, result, N, MPI_INT, MPI_SUM, 0, world);

    if (myRank == 0) {
        // ROOT SECTION
        for (i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        puts("");
    }

    // de-allocate space
    free(numbers);
    free(result);

    // End real work
    MPI_Finalize();

    return 0;
}
