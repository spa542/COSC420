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
    Matrix a; // Create the matrix
    initMatrix(&a, 2, 3); // Initialize it
    printMatrix(&a); // Print the array after initialization

    MPI_Finalize(); // Wrap everything up
    free(a.data); // Free the array
    
    return 0;
}
