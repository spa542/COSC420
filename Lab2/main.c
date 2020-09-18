#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<mpi.h> // MPI library
#include<time.h> // Time functions
#include"matrix.h" // File with matrix definitions and operations

int main(int argc, char** argv) {
    srand(time(NULL)); // Seed the random generator

    MPI_Init(&argc, &argv); // Initialize MPI

    MPI_Comm world = MPI_COMM_WORLD; // Get the world

    int worldSize, myRank;
    MPI_Comm_size(world, &worldSize); // Get the world size
    MPI_Comm_rank(world, &myRank); // Get the rank of the "current" node

    // Testing linking and basic functions
    
    int arows = 2, acols = 3;
    int brows = 2, bcols = 3;


    Matrix a; // Create the matrix
    Matrix b;
    Matrix c;
    if(myRank == 0){
      initMatrix(&a, 2, 3); // Initialize it
      printMatrix(&a); // Print the array after initialization

      initMatrix(&b, 2, 3);
      printMatrix(&b);
    
      initMatrix(&c, 2, 3);
    }else{
      a.rows = arows;
      a.cols = acols;
      b.rows = brows;
      b.cols = bcols;
    }
   



    //Testing opperations
    
    //The root must pass the actual data while the workers do not care 
    //so they are seperated
    c.data = addMatrices(&a, &b, &world, worldSize, myRank);
    if(myRank == 0)
      printMatrix(&c);



    MPI_Finalize(); // Wrap everything up
    free(a.data); // Free the array
    
    return 0;
}
