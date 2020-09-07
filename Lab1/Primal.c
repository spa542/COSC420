#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        puts("Invalid Arguments, ./Primal ( num )");
        return 1;
    }

    MPI_Init(&argc, &argv);

    MPI_Comm world = MPI_COMM_WORLD;

    unsigned long int endValue = atoi(argv[1]); // # of values to be checked
    int worldSize, myRank, maxJobs, stuffToDo, startingNum;

    MPI_Comm_size(world, &worldSize); // Amount of nodes being used
    MPI_Comm_rank(world, &myRank); // Rank of each node

    maxJobs = sqrt(endValue); // Amount of numbers that need to be checked

    if (worldSize >= maxJobs) { // Only need as many nodes as there are jobs for efficiency
        printf("Amount of nodes exceeds the amount for the job. # of nodes needed is sqrt(%d)", maxJobs);
        MPI_Abort(world, 1);
        return 1;
    }

    stuffToDo = maxJobs / worldSize; // Numbers that each node has to check

    if (myRank == 0) {
        startingNum = 2;
    } else {
        startingNum = myRank * stuffToDo + 1; // Where each node will start
    }

    int i;
    for (i = startingNum; i <= startingNum + stuffToDo; i++) {
        if (endValue % i == 0) {
            printf("%d is composite, divisible by %d\n", endValue, i);
        }
    }

    MPI_Finalize();

    return 0;
}
