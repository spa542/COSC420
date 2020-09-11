#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>
#include<time.h>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank, i;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    if (argc != 2) {
        printf("Usage: ./scatter N\n");
        MPI_Finalize();
        return 1;
    }

    srand(time(NULL) + myRank);

    int N = atoi(argv[1]);

    // Making sure we can divide evenly
    if (N % worldSize > 0) {
        printf("Choose N divisible by %d\n", worldSize);
        MPI_Finalize();
        return 1;
    }

    double* arr = NULL;
    if (myRank == 0) {
        // Realistically, the world will read in an array 
        // from a large datafile
        arr = (double*)malloc(N*sizeof(double));

        for (i = 0; i < N; i++) {
            arr[i] = (double)rand() / (double)RAND_MAX; // Between 0 and 1
            printf("%0.2f ", arr[i]);
        }
        puts("");
    }

    // The chunk of the array that will be scattered to me
    int local_len = N / worldSize;
    double* local_arr = (double*)malloc(local_len*sizeof(double));

    MPI_Scatter(arr, local_len, MPI_DOUBLE, // Send info
            local_arr, local_len, MPI_DOUBLE, // Recv info
            0, world); // misc info book keeping

    char* buf = (char*)malloc(5*local_len + 1);
    memset(buf, 0, 5*local_len + 1);
    /* Long way of filling the buffer
    for (i = 0; i < 5*local_len + 1; i++) {
        buf[i] = 0;
    }
    */
    char tmp[6];
    for (i = 0; i < local_len; i++) {
        sprintf(tmp, "%0.2f ", local_arr[i]);
        strcat(buf, tmp);
    }

    printf("I am node %d and my numbers are %s\n", myRank, buf);

    MPI_Finalize();
    free(local_arr);
    free(buf);
    if (myRank == 0) {
        free(arr);
    }

    return 0;
}
