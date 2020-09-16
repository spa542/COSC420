#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Note: the A here needs to be a struct, not a pointer
#define INDEX(A,i,j) A->cols*i + j
// Now we can do A.data(INDEX(A,i,j)

// Use the above to shortcut accessing the array
#define ACCESS(A,i,j) A->data[INDEX(A,i,j)]

// C needs the "typedef"
typedef struct {
    int rows, cols; // dimensions
    double* data; // pointer to the data, a flat array
} matrix;

void initArray(matrix *A) {
    int i, j;
    A->data = (double*)malloc(A->rows*A->cols*sizeof(double));
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            ACCESS(A,i,j) = rand() / RAND_MAX; 
        }
    }
}

void printArray(matrix *A) {
    int i, j;
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            printf("%0.2f ", ACCESS(A,i,j));
        }
        puts("");
    }
}

int main() {
    srand(time(NULL))
    matrix A;
    A->rows = 3;
    A->cols = 4;
    // TODO: allocate, then initialize the matrix
    // To get A[i,j], we need data[cols*i + j]
    // We would need to say A.data[A.cols*i + j]
    // This is ugly :(
    initMatrix(&A);
    printMatrix(&A);

    return 0;
}
