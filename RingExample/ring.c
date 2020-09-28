#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank;
    int token = 0; // gets passed between procs
    int counter = 0; // how many times this proc has pingponged
    int dest; // Modified destination send
    unsigned int from; // Modified from receive (get rid of the negative value)

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    while(token < 10) {
        if (myRank % worldSize == token % worldSize) {
            token++;
            counter++;
            dest = (myRank + 1) % worldSize;
            printf("Proc %d sent %d to %d\n", myRank, token, dest);
            MPI_Send(&token, 1, MPI_INT, dest, 0, world);    
            if (token + worldSize > 10) {
                break;
            }
        } else {
            if (myRank > 0) {
                from = (myRank - 1) % worldSize;
            } else {
                from = worldSize - 1;
            }
            printf("Proc %d wainting on %d\n", myRank, from);
            MPI_Recv(&token, 1, MPI_INT, from, 0, world, MPI_STATUS_IGNORE);
            printf("Proc %d received %d from %d\n", myRank, token, from);
        }
    }
    printf("Proc %d done\n", myRank);

    MPI_Finalize();

    return 0;
}
