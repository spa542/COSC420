#include"PageRank.h"


double* pageRank(Matrix* ai, MPI_Comm* world, int worldSize, int myRank){
    int dim = ai->rows;
    if(dim == 1)
        dim = ai->cols;
    int i;

    //Copping ai to a so we don;t destory the ai matrix
    Matrix inA = default_matrix;
    Matrix* a = inA;
    a->cols = dim;
    if(myRank == 0)
        a->data = (double*)malloc(a->cols*a->rows*sizeof(double));

    //Init needed varriables for algorithm
    Matrix pt = default_matrix;
    Matrix* p = &pt;
    p->rows = dim;
    if(myRank==0)
        p->data = (double*)malloc(p->cols * p->rows * sizeof(double));
    
    Matrix PreviousP = default_matrix;
    Matrix* oldP = PreviousP;
    oldP->rows = dim;
    if(myRank==0)
        oldP->data = (double*)malloc(oldP->cols * oldP->rows * sizeof(double));
    
    
    Matrix tOnes = default_matrix;
    Matrix* ones = &tOnes;
    ones->rows = dim;
    if(myRank==0)
        ones->data = (double*)malloc(ones->cols * ones->rows * sizeof(double));
    
    if(myRank==0){
        for(i=0; i<dim; i++){
            p->data[i] = 1;
            oldP->data[i] = 1;
            ones->data[i] = 1;
        }
    }

    double alpha = .875;//Chance of teleporting between .85 and .9

    //Keep doing the same operation until P converges
    double errorTolerance = .0000000000000001;
    double* difference;
    int counter = 0;
    int done = 1;

    int sendCount[worldSize];
    int disp[worldSize];
    double length;

    while(done>=1 && counter<10000){
        free(oldP->data);
        oldP->data = p->data;
        //TODO DO PAGE RANK JAWN
         



        length = L2Norm(a, world, worldSize, myRank);
        MPI_Bcast(&length, 1, MPI_DOUBLE, 0, *world);

        for(i=0; i<worldSize; i++){
            sendCount[i] = (p->rows * p->cols)/worldSize;
        }
        for(i=0; i<(p->cols*p->rows)%worldSize; i++){
            sendCount[i] += 1;
        }
        sum = 0;
        for(i=0; i<worldSize; i++){
            disp[i] = sum;
            sum += sendCount[i];
        }

        //Scatterv
        double buffer[sendCount[myRank]];
        MPI_Scatterv(p->data, sendCount, disp, MPI_DOUBLE, buffer, sendCount[myRank], MPI_DOUBLE, 0, *world);
        
        for(i=0; i<sendCount[myRank]; i++){
            buffer[i] /= length;
        } 

        //Gatherv
        MPI_Gatherv(buffer, sendCount[myRank], MPI_DOUBLE, p->data, sendCount, disp, MPI_DOUBLE, 0, *world);

        difference = subtractMatrices(p, oldP, world, worldSize, myRank);


        //splits up job for error Tolerance
        for(i=0; i<worldSize; i++){
            sendCount[i] = (p->rows*p->cols)/worldSize;
        }
        for(i=0; i<(p->rows*p->cols)%worldSize; i++){
            sendCount[i] += 1;
        }
        int sum = 0;
        for(i=0; i<worldSize; i++){
            disp[i] = sum;
            sum += sendCount[i];
        }
        double buffer2[sendCount[myRank]];

        MPI_Scatterv(difference, sendCount, disp, MPI_DOUBLE, buffer2, sendCount[myRank], MPI_DOUBLE, 0, *world);
        done = 0;
        for(i=o; i<sendCount[i]; i++){
            if(buffer2[i]>0 ? buffer2[i] : buffer2[i]*-1 > errorTolerance){
                done = 1;
                break;
            }
        }
        
        MPI_Reduce(&done, &done, 1, MPI_DOUBLE, MPI_SUM, 0, *world);
        free(difference);
        counter++;
    }
    if(myRank == 0){
        free(oldP->data);
        free(ones->data);
        free(a->data);
        return p->data;
    }
    return NULL;
    


}


