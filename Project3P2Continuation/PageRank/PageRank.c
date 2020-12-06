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
    if(myRank==0){
        p->data = (double*)malloc(p->cols * p->rows * sizeof(double));
	for(i=0; i<p->rows*p->cols; i++)
            p->data[i] = 1;
    }
	
    Matrix PreviousP = default_matrix;
    Matrix* oldP = &PreviousP;
    oldP->rows = dim;
    oldP->cols = 1;
    if(myRank==0){
        oldP->data = (double*)malloc(oldP->cols * oldP->rows * sizeof(double));
        for(i=0; i<oldP->rows*oldP->cols; i++)
            oldP->data[i] = 1;
    }
    
    Matrix locPs = default_matrix;
    Matrix* section_p = &locPs;
    section_p->rows = myRowsCount[myRank];
    section_p->cols = 1;
    section_p->data = (double*)malloc(section_p->rows * section_p->cols * sizeof(double));
    for(i=0; i<section_p->rows * section_p->cols; i++){
        section_p->data[i] = 1;
    }
	    
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
	if(myRank == 0){
	    free(oldP->data);
	    oldP->data = p->data;
	}
	
	for(masterI=0; masterI<myRowsCount[myRank]; masterI+=grabbed){
	    if(myRank == 0){//Root gets the P matrix for calculations           
                for(i=0; i<p->rows*p->cols; i++){
                    local_p->data[i] = p->data[i]; 
                }
            }
            //Every node gets the P vectors for calculations
            MPI_Bcast(local_p, p->rows*p->cols, MPI_DOUBLE, 0, *world);
	    
	    
	    //This holds the Sparse version of the adjecncy rows
	    int* sparseInFile = (int*)malloc(5064*grabbed*sizeof(int));//written to only work for grabbed = 1 TODO
	    
	    //This matrix will be the expanded version of the sparse Matrix
	    Matrix inFile = default_matrix;
            Matrix* fileData = &inFile;
            fileData->cols = dim;
            fileData->rows = grabbed;
	    
	    MPI_File_open(*world, "scripttest", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	    MPI_File_read_at(fh, (masterI + myRowsDisp[myRank])*sizeof(int)*5064 , sparseInFile, grabbed*5064, MPI_DOUBLE, MPI_STATUS_IGNORE);
	    MPI_File_close(&fh);
	    //5064 - This could be better but we this is from the file that
            //has the adjecency sparse matrix in it. This is the buffer size
 
	    //Now that we have the sparse matrix in we can decode and save
	    fileData->data = decompressSerial(sparseInFile, 5064, dim, world, worldSize, myRank);

	    //Normallize each row that was grabbed
	    for(i=0; i<fileData->rows*fileData->cols; i+=fileData->cols){     
                sum = 0;
                for(j=0; j<fileData->cols; j++)
                    sum += fileData->data[i+j];
                if(sum == 0)
                    sum = 1;
                for(j=0; j<fileData->cols; j++)
                    fileData->data[i+j] /= sum;
            }
            
            //All data needed to do PageRank formula is ready!
            //This below is the actual algorithm
            
            
	    Mp.data = multMatricesSerial(fileData, local_p);
	    tmp = multMatrixConstSerial(&Mp, alpha);
	    free(Mp.data);
	    Mp.data = tmp;
	  
	    tmp = addMatricesSerial(&Mp, ones);
	    free(Mp.data);
	    Mp.data = tmp;
	    
	    for(i=0; i<grabbed; i++){
		section_p->data[masterI+i] = Mp.data[i];
	    }
	    free(tmp);
	    free(fileData->data);
	    
	}
	length = 0;
        for(i=0; i<section_p->rows*section_p->cols; i++){
            length += section_p->data[i];
        }
        for(i=0; i<section_p->rows*section_p->cols; i++){
             section_p->data[i] /= length;
        }
	for(i=0; i<section_p->rows*section_p->cols; i+=section_p->cols){     
            sum = 0;
            for(j=0; j<section_p->cols; j++)
                sum += section_p->data[i+j];
            if(sum == 0)
                sum = 1;
            for(j=0; j<section_p->cols; j++)
                section_p->data[i+j] /= sum;
        }
        
        if(myRank == 0){
            p->data = (double*)malloc(p->rows*p->cols*sizeof(double));
        }  
        MPI_Gatherv(local_ps->data, myRowsCount[myRank], MPI_DOUBLE, p->data, myRowsCount, myRowsDisp, MPI_DOUBLE, 0, *world);
	
      
      
      
    }
    
    
}








//Decompresses sparse matrix protocol view readME for more details
//0,3,1,0
//1,0,0,0,1,0,1
//There will be a 1 between each number
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
	if(i+1 < size){
	  rtn[itter]=1;
	  itter++;
	}
    }
    return rtn;
}


