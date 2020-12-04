#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

// Defining the buffer length for processor name
#define pNameSize MPI_MAX_PROCESSOR_NAME

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); // Initializing MPI

    MPI_Comm world = MPI_COMM_WORLD; // Communicator

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize); // Gives amount of nodes running in parallel
    MPI_Comm_rank(world, &myRank); // Gives the rank (number) node
    srand(time(0));      

    printf("Hi\n");    

    int size = 5;

    int* arr = (int*)malloc(size*sizeof(int));  
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 0;
    arr[3] = -1;
    arr[4] = 50;
    
    double* test = decompress(arr, size, 8, &world, worldSize, myRank);  

    int i;
    for(i=0; i<8; i++){
        printf("%f \n", test[i]);
    }



    MPI_Finalize(); // Finalizing MPI

    return 0;
}
