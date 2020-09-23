#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

// Defining the buffer length for processor name
#define pNameSize MPI_MAX_PROCESSOR_NAME





int factorial(int fact, MPI_Comm *world, int worldSize, int Rank){
    int start;
    int finish;
    int local_fact;
    int rtn;

    if(Rank == 0){
        start = 2;
    }
    start = (int) (((fact/worldSize) * Rank)+1);
    finish = (int) ((fact/worldSize) * (Rank + 1));
    
    int i;

    for(i=start; i<finish; i++){
        local_fact *= i;
        while(local_fact % 10 == 0){
            local_fact /= 10;
        }
        if(local_fact >= 100000)
          local_fact %= 100000;
    }
    MPI_Reduce(&local_fact, &rtn, 1, MPI_INT, MPI_PROD, 0, *world);
    return rtn;
}






int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); // Initializing MPI

    MPI_Comm world = MPI_COMM_WORLD; // Communicator

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize); // Gives amount of nodes running in parallel
    MPI_Comm_rank(world, &myRank); // Gives the rank (number) node
    //MPI_Get_processor_name(processorName, &processSize); 
    srand(time(0));                           // Gives the processor name of current node

    
    int fac = 10;

    printf(factorial(&fac, &world, worldSize, myRank));



    MPI_Finalize(); // Finalizing MPI

    return 0;
}
