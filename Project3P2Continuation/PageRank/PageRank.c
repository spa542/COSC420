#include"PageRank.h"
#include"MatrixJawn/matrix.h"
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>




double* pageRank(int dim, MPI_Comm* world, int worldSize, int myRank){
    double alpha = .88;
    int i, masterI, j;
    int grabbed = 1;

    //Divides up the rows of the M matrix so each processor gets a chunk
    int mRowsCount[worldSize];
    int mRowsDisp[worldSize];

    for(i=0; i<worldSize; i++){
        mRowsCount[i] = dim/worldSize;        
    }
    for(i=0; i<(dim%worldSize); i++){
        mRowsCount[i] += 1;
    }

    int sum=0;
    for(i=0; i<worldSize; i++){
        mRowsDisp[i] = sum;
        sum += mRowsCount[i];   
    }

    //Init needs matricies for PageRank
    Matrix locP = default_matrix;
    Matrix* local_p = &locP;
    local_p->rows = dim;
    local_p->cols = 1;
    local_p->data = (double*)malloc(local_p->rows * local_p->cols * sizeof(double));
    for(i=0; i<local_p->rows * local_p->cols; i++){
        local_p->data[i] = 1;
    }

    Matrix pt = default_matrix;
    Matrix* p = &pt;
    p->rows = dim;
    p->cols = 1;
    if(myRank==0)
        p->data = (double*)malloc(p->cols * p->rows * sizeof(double));
       
    Matrix PreviousP = default_matrix;
    Matrix* oldP = &PreviousP;
    oldP->rows = dim;
    oldP->cols = 1;
    if(myRank==0)
        oldP->data = (double*)malloc(oldP->cols * oldP->rows * sizeof(double));
  
    Matrix tOnes = default_matrix;
    Matrix* ones = &tOnes;
    ones->rows = grabbed;
    ones->cols = 1;
    ones->data = (double*)malloc(ones->cols * ones->rows * sizeof(double));
    for(i=0; i<ones->rows*ones->cols; i++){
        ones->data[i] = (1-alpha);
    }
    
    
    double errorTolerance = .0000000000000001;
    double* difference;
    int counter = 0;
    int done = 1;
    
    
    double length;
    
    Matrix Mp = default_matrix;
    Mp.cols = grabbed;
    Mp.rows = 1;

    double* tmp=NULL;
    
    
    
    while(done>=1 && counter<2500){
	free(oldP->data);
	oldP->data = p->data;
	
	for(masterI=0; masterI<myRowsCount[myRank]; masterI+=grabbed){
	    if(myRank == 0){           
                for(i=0; i<p->rows*p->cols; i++){
                    local_p->data[i] = p->data[i]; 
                }
            }
            MPI_Bcast(local_p, p->rows*p->cols, MPI_DOUBLE, 0, *world);
	    
	    Matrix inA = default_matrix;
            Matrix* a = &inA;
            a->cols = dim;
            a->rows = grabbed;
            a->data = (double*)malloc(a->cols*a->rows*sizeof(double));
	    
	    MPI_File_open(*world, "scripttest", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	    MPI_File_read_at(fh, (masterI + myRowsDisp[myRank])*sizeof(double)*dim , a->data, grabbed*dim, MPI_DOUBLE, MPI_STATUS_IGNORE);
	    MPI_File_close(&fh);
	    
	    for(i=0; i<a->rows*a->cols; i+=a->cols){     
                sum = 0;
                for(j=0; j<a->cols; j++){
                    sum += a->data[i+j];
                }
                if(sum == 0)
                    sum = 1;
                for(j=0; j<a->cols; j++){
                    a->data[i+j] /= sum;
                }
            } 
	  
	    
	    
	    
	}
      
      
      
    }
    
    
}








//Decompresses sparse matrix protocol view readME for more details
//2000, 2, 100
//Returns a col matrix
//Under assumption the file it is reading from is ints that holds the number of zeros
double* decompressSerial(int* sparse, int size, int dim, MPI_Comm* world, int worldSize, int myRank){
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
        if(current == -1)
            break;
      for(j=0; j<current; j++){
            rtn[itter] = 0;
            itter += 1;
        }
        rtn[itter]=1;
        itter++;
    }
    return rtn;
}


