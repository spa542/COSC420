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
    //printf("myRank %d\n", myRank);

    // Create the matrices
    Matrix a = default_matrix;
    Matrix b = default_matrix;
    // For addition result
    Matrix c = default_matrix;
    // For subtraction result
    Matrix d = default_matrix;
    // For transpose
    Matrix e = default_matrix;
    // For inner product
    Matrix f = default_matrix;
    Matrix g = default_matrix;
    // For matrix multiplication
    Matrix h = default_matrix;
    Matrix i = default_matrix;
    // Result for matrix multiplication
    Matrix j = default_matrix;
    // Matrix test for Gauss Jordan function
    Matrix gj = default_matrix;
    // Matrix b for Gauss Jordan function
    Matrix gjb = default_matrix;
    // Result matrix for Gauss Jordan function
    Matrix gjresult = default_matrix;
    //Matrix to check if jkresult is correct
    Matrix GJtest = default_matrix;


    // The row and column length for matrix a, b, and c
    int rowLength =  2, colLength = 3;
    if (myRank == 0) {
        puts("Matrix a for addition and subtraction");
        initMatrix(&a, rowLength, colLength); // Initialize it
        printMatrix(&a); // Print the array after initialization

        puts("Matrix b for addition and subtraction");
        initMatrix(&b, rowLength, colLength);
        printMatrix(&b);
    
        initMatrix(&c, rowLength, colLength);
        free(c.data); // We change the result of c
        initMatrix(&d, rowLength, colLength);
        free(d.data); // We change the result of d
        initMatrix(&e, rowLength, colLength);
        puts("Matrix to be transposed");
        printMatrix(&e);

        initMatrix(&f, 3, 1);
        initMatrix(&g, 3, 1);
        puts("f matrix for inner product:");
        printMatrix(&f);
        puts("g matrix for inner product:");
        printMatrix(&g);

        initMatrix(&h, 4, 4);
        initMatrix(&i, 4, 4);
        puts("h matrix for matrix multiplication:");
        printMatrix(&h);
        puts("i matrix for matrix multiplication:");
        printMatrix(&i);
        initMatrix(&j, 4, 4);
        free(j.data); // We change the result of j

        initMatrix(&gj, 3, 3);
        puts("Matrix a for gauss jordan function");
        printMatrix(&gj);
        initMatrix(&gjb, 3, 1);
        puts("Matrix b for gauss jordan function");
        printMatrix(&gjb);
        initMatrix(&gjresult, 3, 1);
        free(gjresult.data); // We change the result of gjresult
        initMatrix(&GJtest, 3, 1);
        free(GJtest.data);
    
    } else {
        // So other nodes know the dimensions
        a.rows = b.rows = c.rows = rowLength;
        a.cols = b.cols = c.cols = colLength;
        f.rows = g.rows = 3;
        f.cols = g.cols = 1;
        h.rows = i.rows = j.rows = 4;
        h.cols = i.cols = j.cols = 4;
        gj.rows = gjb.rows = gjresult.rows = GJtest.rows = gj.cols = 3;
        gjresult.cols = gjb.cols = GJtest.cols = 1;
    }

    // Test file operations

    MPI_File fh;

    MPI_File_open(world, "outfile", MPI_MODE_CREATE | MPI_MODE_WRONLY,
            MPI_INFO_NULL, &fh);


   
    //Testing opperations
    
    //The root must pass the actual data while the workers do not care 
    //so they are seperated
    c.data = addMatrices(&a, &b, &world, worldSize, myRank);
    // For writing to file
    if (myRank != 0) {
        c.data = (double*)malloc(c.rows*c.cols*sizeof(double));
    }
    int Varray[worldSize];
    int disp[worldSize];
    int z;
    for (z = 0; z < worldSize; z++) {
        Varray[z] = (c.rows*c.cols) / worldSize;
    }
    for (z = 0; z < (c.rows*c.cols) % worldSize; z++) {
        Varray[z] += 1;
    }
    int nextLength = 0;
    for (z = 0; z < worldSize; z++) {
        disp[z] = nextLength;
        nextLength += Varray[myRank];
    }
    double local_mat[Varray[myRank]];
    MPI_Scatterv(c.data, Varray, disp, MPI_DOUBLE, local_mat, Varray[myRank], MPI_DOUBLE, 0, world);

    MPI_Offset offset = Varray[myRank] * myRank * sizeof(double);

    MPI_File_write_at(fh, offset, local_mat, Varray[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);
    // End writing to file for addition result
    if(myRank == 0) {
        puts("Result Matrix: a + b"); 
        printMatrix(&c);
    }

    d.data = subtractMatrices(&a, &b, &world, worldSize, myRank);
    if (myRank != 0) {
        d.data = (double*)malloc(d.rows*d.cols*sizeof(double));
    }
    // For writing to file
    if (myRank != 0) {
        d.data = (double*)malloc(d.rows*d.cols*sizeof(double));
    }
    for (z = 0; z < worldSize; z++) {
        Varray[z] = (d.rows*d.cols) / worldSize;
    }
    for (z = 0; z < (d.rows*d.cols) % worldSize; z++) {
        Varray[z] += 1;
    }
    nextLength = 0;
    for (z = 0; z < worldSize; z++) {
        disp[z] = nextLength;
        nextLength += Varray[myRank];
    }
    if (myRank == 0) {
        for (z = 0; z < worldSize; z++) {
            printf("%d ", Varray[z]);
        }
    }
    double local_mat1[Varray[myRank]];
    MPI_Scatterv(d.data, Varray, disp, MPI_DOUBLE, local_mat1, Varray[myRank], MPI_DOUBLE, 0, world);

    offset = Varray[myRank] * myRank * sizeof(double);

    MPI_File_write_at(fh, offset, local_mat1, Varray[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);
    // End writing to file for subtraction result
    if(myRank == 0){
      puts("Result Matrix: a - b");
      printMatrix(&d);
    }

    if (myRank == 0) {
        puts("Transposed Matrix:");
        Matrix tmp=default_matrix;
        initMatrix(&tmp, colLength, rowLength);
        free(tmp.data);
        tmp.data = transpose(&e);
        printMatrix(&tmp);
        free(tmp.data);
        free(e.data);
    }

    double innerProdResult = innerProduct(&f, &g, &world, worldSize, myRank);
    if (myRank == 0) {
        printf("The inner product result is %f\n", innerProdResult);
    }

    j.data = multMatrices(&h, &i, &world, worldSize, myRank);
    if (myRank == 0) {
        puts("Matrix Mult Answer:");
        printMatrix(&j);
    }

    gjresult.data = GaussJordan(&gj, &gjb, &world, worldSize, myRank);
    if (myRank == 0) {
        puts("Result of Gauss Jordan Reduction, linear system answer");
        printMatrix(&gjresult);
    }
        GJtest.data = multMatrices(&gj, &gjresult, &world, worldSize, myRank);
   if(myRank == 0){
       printMatrix(&GJtest);
   } 


   //puts("REEEEEEEEEEEEEEEEEEEEEEE NEW JAWN");

 
   Matrix aa = default_matrix;
   Matrix bb = default_matrix;
   Matrix rr = default_matrix;
   Matrix rrtest = default_matrix;
   if(myRank == 0){
       initMatrix(&aa, 4, 4);
       initMatrixIdentity(&bb, 4, 4); 
       initMatrix(&rr, 4, 4);
       initMatrix(&rrtest, 4, 4);
       free(rr.data);
       free(rrtest.data);

   }else{
       rr.rows = rr.cols = aa.rows = aa.cols = bb.rows = bb.cols = 4;          
   }
   if(myRank == 0){
       puts("aa: ");
       printMatrix(&aa);
       puts("bb: ");
       printMatrix(&bb);
   }

   rr.data = GaussJordan(&aa, &bb, &world, worldSize, myRank);
   
   if(myRank == 0){
      puts("Result: ");
      printMatrix(&rr);
   }
   rrtest.data = multMatrices(&aa, &rr, &world, worldSize, myRank);
   
   if(myRank == 0){
      puts("test result: ");
      printMatrix(&rrtest);
    }

    MPI_File_close(&fh);
    MPI_Finalize(); // Wrap everything up
    // Free the arrays of each matrix
    if (myRank == 0) {
        free(a.data);
        free(b.data); 
        free(gj.data);
        free(gjb.data); // gjresult will point to gjb when pointer returned, watch for double free!!!!
        free(GJtest.data);
        free(aa.data);
        free(bb.data);
        free(rr.data);
        free(rrtest.data);
    }
    free(gjresult.data);
    free(c.data);
    free(d.data);
    free(f.data);
    free(g.data);
    free(h.data);
    free(i.data);
    free(j.data); 
    return 0;
}
