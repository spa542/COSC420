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

    // Create the matrices
    Matrix a;
    Matrix b;
    Matrix c;
    Matrix d;
    Matrix e;

    // The row and column length for matrix a, b, and c
    int rowLength =  2, colLength = 3;
    if (myRank == 0) {
        initMatrix(&a, rowLength, colLength); // Initialize it
        printMatrix(&a); // Print the array after initialization

        initMatrix(&b, rowLength, colLength);
        printMatrix(&b);
    
        initMatrix(&c, rowLength, colLength);
        initMatrix(&d, rowLength, colLength);
        initMatrix(&e, rowLength, colLength);
        puts("Matrix to be transposed");
        printMatrix(&e);
    } else {
        a.rows = b.rows = c.rows = rowLength;
        a.cols = b.cols = c.cols = colLength;
    }
   



    //Testing opperations
    
    //The root must pass the actual data while the workers do not care 
    //so they are seperated
    c.data = addMatrices(&a, &b, &world, worldSize, myRank);
    if(myRank == 0) {
        puts("Result Matrix: a + b"); 
        printMatrix(&c);
    }

    d.data = subtractMatrices(&a, &b, &world, worldSize, myRank);
    if(myRank == 0){
      puts("Result Matrix: a - b");
      printMatrix(&d);
    }

    if (myRank == 0) {
        puts("Transposed Matrix:");
        Matrix tmp;
        initMatrix(&tmp, colLength, rowLength);
        tmp.data = transpose(&e);
        printMatrix(&tmp);
    }

    MPI_Finalize(); // Wrap everything up
    // Free the arrays of each matrix
    if (myRank == 0) {
        free(a.data);
        free(b.data); 
    }
    free(c.data);
    free(d.data);

    return 0;
}
