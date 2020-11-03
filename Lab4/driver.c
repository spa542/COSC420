#include<stdio.h> // I/O
#include<stdlib.h> // Standard library functions
#include<mpi.h> // MPI Library
#include<time.h> // Time functions
#include"matrix.h" // Matrix Library

// Script to write test matrices to a file
void writeTestFile(int dims, MPI_Comm* world, int worldSize, int myRank) {
    Matrix test = default_matrix;

    test.rows = test.cols = dims;
    int Varray[worldSize];
    int i;
    for (i = 0; i < worldSize; i++) {
        Varray[i] = (dims*dims) / worldSize;
    }
    for (i = 0; i < (dims*dims) % worldSize; i++) {
        Varray[i] += 1;
    }
    test.data = (double*)malloc(Varray[myRank]*sizeof(double));
    for (i = 0; i < Varray[myRank]; i++) {
        test.data[i] = 1 + rand() % 10;
    }
    MPI_File fh;
    MPI_File_open(*world, "scripttest", MPI_MODE_CREATE | MPI_MODE_WRONLY,
            MPI_INFO_NULL, &fh);
    MPI_Offset off = myRank*Varray[myRank]*sizeof(double);
    MPI_File_write_at(fh, off, test.data, Varray[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);
    MPI_File_close(&fh);
    free(test.data);
}

void deleteFileTest() {
    if (remove("scripttest") == 0) {
        puts("Deleted scripttest file successfully");
    } else {
        puts("Error in deleting scripttest file");
    }
}

int main(int argc, char** argv){
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);
    
    if(myRank == 0)
        printf("End of porgram! | World Size: %d\n", worldSize);    
    
    int testcases[13] = {100, 250, 500, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
    int w, ww, dimnum;
   
    dimnum = 13;

    double numofTrials = 10.0; 
        
    double startAdd, finishAdd;
    //double startSub, finishSub;
    //double startMul, finishMul;
    //double startInn, finishInn;
    
    int rowLength;
    int colLength;
        
    Matrix A=default_matrix;
    Matrix B=default_matrix;
        
    Matrix Result=default_matrix;

    int DIMENSION; // Change the test case matrix dimensions 
    
    for(w=0; w<dimnum; w++){
        DIMENSION = testcases[w]; // Change the test case matrix dimensions 
        
        //Testing addition
        
        rowLength = DIMENSION;
        colLength = DIMENSION;
        
        //start timing
        startAdd = MPI_Wtime();

        for(ww=0; ww<numofTrials; ww++){
            if(myRank == 0){
                initMatrix(&A, rowLength, colLength);
                initMatrix(&B, rowLength, colLength);
            }else{
                A.rows = A.cols = rowLength;
                B.rows = B.cols = rowLength;
            }
            Result.rows = rowLength;
            Result.cols = colLength;
        
            Result.data = addMatrices(&A, &B, &world, worldSize, myRank);
            if(myRank == 0){
                //puts("Done");   
                free(Result.data);
                Result = default_matrix;
            }
            if (myRank == 0) {
                free(A.data);
                free(B.data);
                A = default_matrix;
                B = default_matrix; 
            }
        }
    
        finishAdd = MPI_Wtime();
        if(myRank == 0)
            printf("ADD -- numofItems: %d | Time/Node: %f \n", testcases[w], finishAdd - startAdd);
        fflush(stdout);
    } 
    
    
    
        
    //Testing subtract
        
    for(w=0; w<dimnum; w++){
        
        DIMENSION = testcases[w]; // Change the test case matrix dimensions 
      
        rowLength = DIMENSION;
        colLength = DIMENSION;
        
        //start timing
        startAdd = MPI_Wtime();

        for(ww=0; ww<numofTrials; ww++){
            if(myRank == 0){
                initMatrix(&A, rowLength, colLength);
                initMatrix(&B, rowLength, colLength);
            }else{
                A.rows = A.cols = rowLength;
                B.rows = B.cols = rowLength;
            }
            Result.rows = rowLength;
            Result.cols = colLength;
        
            Result.data = subtractMatrices(&A, &B, &world, worldSize, myRank);
            if(myRank == 0){
                //puts("Done");   
                free(Result.data);
                Result = default_matrix;
            }
            if (myRank == 0) {
                free(A.data);
                free(B.data);
                A = default_matrix;
                B = default_matrix; 
            }
        }
    
        finishAdd = MPI_Wtime();
        if(myRank == 0)
            printf("SUBTRACT -- numofItems: %d | Time/Node: %f \n", testcases[w], finishAdd - startAdd);
        fflush(stdout);
    } 
    
    
   






    //Testing inner product
        
    for(w=0; w<dimnum; w++){
        
        DIMENSION = testcases[w]; // Change the test case matrix dimensions 
      
        rowLength = DIMENSION;
        colLength = 1;
        
        //start timing
        startAdd = MPI_Wtime();

        for(ww=0; ww<numofTrials; ww++){
            if(myRank == 0){
                initMatrix(&A, rowLength, colLength);
                initMatrix(&B, rowLength, colLength);
            }else{
                A.rows = B.rows = rowLength;
                A.cols = B.cols = colLength;
            }
            Result.rows = rowLength;
            Result.cols = colLength;
        
            double answer = innerProduct(&A, &B, &world, worldSize, myRank);
            if(myRank == 0){
                //puts("Done");   
                free(Result.data);
                Result = default_matrix;
            }
            if (myRank == 0) {
                free(A.data);
                free(B.data);
                A = default_matrix;
                B = default_matrix; 
            }
        }
    
        finishAdd = MPI_Wtime();
        if(myRank == 0)
            printf("INNERPROD -- numofItems: %d | Time/Node: %f \n", testcases[w], finishAdd - startAdd);
        fflush(stdout);
    }














    //Testing multiply
        
    for(w=0; w<dimnum; w++){
        
        DIMENSION = testcases[w]; // Change the test case matrix dimensions 
      
        rowLength = DIMENSION;
        colLength = DIMENSION;
        
        //start timing
        startAdd = MPI_Wtime();

        for(ww=0; ww<numofTrials; ww++){
            if(myRank == 0){
                initMatrix(&A, rowLength, colLength);
                initMatrix(&B, rowLength, colLength);
            }else{
                A.rows = A.cols = rowLength;
                B.rows = B.cols = rowLength;
            }
            Result.rows = rowLength;
            Result.cols = colLength;
        
            Result.data = multMatrices(&A, &B, &world, worldSize, myRank);
            if(myRank == 0){
                //puts("Done");   
                free(Result.data);
                Result = default_matrix;
            }
            if (myRank == 0) {
                free(A.data);
                free(B.data);
                A = default_matrix;
                B = default_matrix; 
            }
        }
    
        finishAdd = MPI_Wtime();
        if(myRank == 0)
            printf("MULTIPLY -- numofItems: %d | Time/Node: %f \n", testcases[w], finishAdd - startAdd);
        fflush(stdout);    
    }
    
    
    
    
    
    
    
    
    
    
    //Testing GuassJordan
        
    for(w=0; w<dimnum; w++){
        
        DIMENSION = testcases[w]; // Change the test case matrix dimensions 
      
        rowLength = DIMENSION;
        colLength = DIMENSION;
        
        //start timing
        startAdd = MPI_Wtime();

        for(ww=0; ww<numofTrials; ww++){
            if(myRank == 0){
                initMatrix(&A, rowLength, colLength);
                initMatrix(&B, rowLength, 1);
            }else{
                A.rows = A.cols = rowLength;
                B.rows = rowLength;
                B.cols = 1;
            }
            Result.rows = rowLength;
            Result.cols = 1;
        
            Result.data = GaussJordan(&A, &B, &world, worldSize, myRank);
            if(myRank == 0){
                //puts("Done");   
                free(Result.data);
                Result = default_matrix;
            }
            if (myRank == 0) {
                free(A.data);
                free(B.data);
                A = default_matrix;
                B = default_matrix; 
            }
        }
    
        finishAdd = MPI_Wtime();
        if(myRank == 0)
            printf("GAUSSJORDAN -- numofItems: %d | Time/Node: %f \n", testcases[w], finishAdd - startAdd);
        fflush(stdout);    
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    if(myRank == 0)
        printf("End of porgram! | World Size: %d\n", worldSize);    
    MPI_Finalize();
    return 0;
    
}
