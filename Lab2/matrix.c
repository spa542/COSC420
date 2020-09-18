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
    puts("");
}

// Adds two matrices together
double* addMatrices(Matrix *a, Matrix *b, MPI_Comm *world, int worldSize, int myRank) {
  
  //We need tpo utilize all the nodes given by adding the scatterv and gatherv so that 
  //we can make cetrian nodes get more stuff to do than other nodes
  //
  //ex. 6 elements and 5 nodes means one node needs to do 1 extra comutation.
  //If we used regular scatter and gather the last one extra would be ignored and not 
  //calculated. So we used scatterV and gatherV so we can give the extra to nodes
  //But these functions need an array of how many elements should go places  
  int Varray = [];
  int j=0
  for(j; j<())
  
  
  
  int matLen = (a->rows * a->cols) / worldSize;//TODO ScatterVarray[myRank]
  double* rtn = NULL;
  if(myRank == 0 ) //TODO This is gonna break we need to determine how we watnt hese functions to run
    rtn = (double*) malloc(matLen*worldSize*sizeof(double));
    

  double* holder = (double*) malloc(matLen*sizeof(double));
  double* local_matA = (double*) malloc(matLen*sizeof(double));
  double* local_matB = (double*) malloc(matLen*sizeof(double));
  MPI_Scatterv(a->data, , MPI_DOUBLE, local_matA, matLen, MPI_DOUBLE, 0, *world);
  MPI_Scatterv(b->data, , MPI_DOUBLE, local_matB, matLen, MPI_DOUBLE, 0, *world);
  //Each now has their needed a data and b data now to add them
  int i;
  //double* rtn = (double*) malloc(matLen*sizeof(double));
  for(i=0; i<matLen; i++){
    holder[i] = local_matA[i] + local_matB[i];
  }
  MPI_Gatherv(holder, matLen, MPI_DOUBLE, rtn, , MPI_DOUBLE, 0, *world);
  return rtn;
}

// Subtracts two matrices from each other
void subtractMatrices(Matrix *a, Matrix *b, MPI_Comm *world, int worldSize, int myRank) {

}

// Does matrix multiplication 
void multMatrices(Matrix *a, Matrix *b, MPI_Comm *world, int worldSize, int myRank) {

}

// Transposes the given matrix
void transpose(Matrix* a) {

}

// Calculates the inner product of two matrices
void innerProduct(Matrix *a, Matrix *b, MPI_Comm *world, int worldSize, int myRank) {

}
