#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<mpi.h> // MPI library
#include<time.h> // Time functions
#include"MatrixJawn/matrix.h" // File with matrix definitions and operations
#include"PageRank.h"








double* AdjMatrix(int size){
    double* rtn = (double*)malloc(size*size*sizeof(double));
    int i, j;
    for(i=0; i<size*size; i++){
        rtn[i] = rand() % 2;
    }
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(j == i)
              rtn[size*i + j] = 0;
        }
    }
    return rtn;
}
















int main(int argc, char** argv) {
    srand(time(NULL)); // Seed the random generator

    MPI_Init(&argc, &argv); // Initialize MPI

    MPI_Comm world = MPI_COMM_WORLD; // Get the world

    int worldSize, myRank;
    MPI_Comm_size(world, &worldSize); // Get the world size
    MPI_Comm_rank(world, &myRank); // Get the rank of the "current" node
    //printf("myRank %d\n", myRank);

    // Create the matrices
    Matrix a = default_matrix;
    Matrix Result = default_matrix;
   

    int i;
    int DIM = 10;
    a.cols = a.rows = DIM;
    Result.cols = DIM;
    Result.rows = 1;

    if(myRank == 0){
        a.data = (double*)malloc(a.cols*a.rows*sizeof(double));
        for(i=0; i<a.cols*a.rows; i++){
            a.data[i] = 0;
        }
        a.data[11] = a.data[7] = a.data[3] = a.data[1] = a.data[2] = 1;
        printMatrix(&a);
    }
    
    Result.data = HITS(&a, 0, &world, worldSize, myRank);
    if(myRank == 0){
        free(a.data);
        puts("After test");
        printMatrix(&Result);
        free(Result.data);
        a.data = AdjMatrix(DIM);
    }


    Result.data = HITS(&a, 0, &world, worldSize, myRank);

    if(myRank == 0){
        free(a.data);
        puts("After test 2");
        printMatrix(&Result);
        free(Result.data);
    }

    


    MPI_Finalize(); // Wrap everything up
    return 0;
}
