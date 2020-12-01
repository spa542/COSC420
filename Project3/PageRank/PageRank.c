#include"PageRank.h"
#include"MatrixJawn/matrix.h"
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

//Decompresses sparse matrix protocol view readME for more details
//2000, 2, 100
//Returns a col matrix
//Under assumption the file it is reading from is ints that holds the number of zeros
double* decompress(int* sparse, int size, int dim, MPI_Comm* world, int worldSize, int myRank){
    if(size == 0){
        printf("Why did you even decompress?");
        return NULL;
    }
  
    double* rtn = (double*)malloc(dim*sizeof(double));    

    int i, j;
    int current;
    int itter=0;
    for(i=0; i<size; i++){
        current = sparse[i];
      for(j=0; j<current; j++){
            rtn[itter] = 0;
            itter += 1;
        }
        rtn[itter]=1;
    }
    return rtn;
}


