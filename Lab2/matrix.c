#include"matrix.h"

// Initializes a "Matrix" struct with random values
// MUST have rows and columns initialized or will seg fault
// USE ON ONE NODE
void initMatrix(Matrix *a, int rows, int cols) {
    int i, j;
    a->rows = rows;
    a->cols = cols;
    a->data = (double*)malloc(a->rows*a->cols*sizeof(double));
    for (i = 0; i < a->rows; i++) {
        for (j = 0; j < a->cols; j++) {
            ACCESS(a,i,j) = rand() % 10 + 1;
        }
    }
}

// Prints the Matrix that is passed to it
// USE ON ONE NODE OR THERE WILL BE OVERLAP
void printMatrix(Matrix *a) {
    int i, j;
    for (i = 0; i < a->rows; i++) {
        for (j = 0; j < a->cols; j++) {
            printf("%0.2f ", ACCESS(a,i,j));
        }
        puts("");
    }
}

// Adds two matrices together
void addMatrices(Matrix *a, Matrix *b, MPI_Comm world, int worldSize, int myRank) {

}

// Subtracts two matrices from each other
void subtractMatrices(Matrix *a, Matrix *b, MPI_Comm world, int worldSize, int myRank) {

}

// Does matrix multiplication 
void multMatrices(Matrix *a, Matrix *b, MPI_Comm world, int worldSize, int myRank) {

}

// Transposes the given matrix
void transpose(Matrix* a) {

}

// Calculates the inner product of two matrices
void innerProduct(Matrix *a, Matrix *b, MPI_Comm world, int worldSize, int myRank) {

}
