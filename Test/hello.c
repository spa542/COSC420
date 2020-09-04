#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv); // pass through cli args

    MPI_Comm world = MPI_COMM_WORLD; // This constant gets set by the MPI lib

    // worldSize will be the total number of nodes in the communicator
    // myRank will be the node's id within that communicator
    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    // This will only execute on the "master" node
    if (myRank == 0) {
        printf("Hello from the master node!\n");
        printf("There are %d total nodes.\n", worldSize);
    } else {
        // Executed in worker nodes
        printf("Hello, from the worker node %d!\n", myRank);
    }

    MPI_Finalize();

    return 0;
}
