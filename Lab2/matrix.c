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
  //We need to utilize all the nodes given by adding the scatterv and gatherv so that 
  //we can make certainn nodes get more stuff to do than other nodes
  //
  //ex. 6 elements and 5 nodes means one node needs to do 1 extra comutation.
  //If we used regular scatter and gather the last one extra would be ignored and not 
  //calculated. So we used scatterV and gatherV so we can give the extra to nodes
  //But these functions need an array of how many elements should go places  
  int length = a->rows * a->cols;
  int Varray[worldSize];
  int displacement[worldSize];
  int j;
  // Initialize Varray sizes
  for(j=0; j<(worldSize); j++){
    Varray[j] = length / worldSize;
  }
  // Pick up any stragglers
  for(j=0; j<(length % worldSize); j++){
    Varray[j] += 1;
  }
  // Initialize displacement array using Varray values
  int nextLength = 0;
  for (j = 0; j < worldSize; j++) {
    if (j == 0){
        displacement[j] = 0;
        nextLength = Varray[j];
        continue;
    }
    displacement[j] = displacement[j - 1] + nextLength;
    nextLength = Varray[j];
  }

  /*for(j=0; j<worldSize; j++){
    printf("%d ", Varray[j]);
  }
  puts("");*/
  
  int matLen = Varray[myRank]; // Each nodes divied up array sizes
  double* rtn = NULL; // For the root node to initialize
  if(myRank == 0 ) // Root node will initialize the return array
    rtn = (double*) malloc(length*sizeof(double));
    
  // Each local node solution
  double* local_solution = (double*) malloc(matLen*sizeof(double));
  // Local matrix for A
  double* local_matA = (double*) malloc(matLen*sizeof(double));
  // Local matrix for B
  double* local_matB = (double*) malloc(matLen*sizeof(double));
  MPI_Scatterv(a->data, Varray, displacement, MPI_DOUBLE, local_matA, matLen, MPI_DOUBLE, 0, *world);
  MPI_Scatterv(b->data, Varray, displacement, MPI_DOUBLE, local_matB, matLen, MPI_DOUBLE, 0, *world);
  // Each now has their needed a data and b data now to add them
  int i;
  for(i=0; i<matLen; i++){
    local_solution[i] = local_matA[i] + local_matB[i];
  }
  // Gather all of the solutions back
  MPI_Gatherv(local_solution, matLen, MPI_DOUBLE, rtn, Varray, displacement, MPI_DOUBLE, 0, *world);

  free(local_solution);
  free(local_matA);
  free(local_matB);
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
