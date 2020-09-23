#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

// Defining the buffer length for processor name
#define pNameSize MPI_MAX_PROCESSOR_NAME





size_t factorial(size_t fact, MPI_Comm *world, int worldSize, int Rank){
    size_t start;
    size_t finish;
    size_t local_fact=1;
    size_t rtn;

    if(Rank == 0){
        start = (size_t)2;
        finish = (size_t) (fact/worldSize);
    }else{
        start = (size_t) (((fact/worldSize) * Rank)+1);
        finish = (size_t) start + (fact/worldSize) -1;
    }

       
    size_t i;
    puts("BEfor for loop");
    printf("Rank: %d | Start: %zu | Finish: %zu\n", Rank, start, finish);
    for(i=start; i<=finish; i++){
        local_fact *= i;
        //printf("local_fact *= %zu: %zu\n",i,local_fact);
        while(local_fact % 10 == 0){
            local_fact /= 10;
        //    puts("oh no");
        }
        if(local_fact >= 100000){
            local_fact %= 100000;
        //    puts("local_fact >= 100000");
        }
        if(i%200000 == 0){
            printf("%zu\n", i);
        }
    }
    puts("ENd for loop");
    

    
    
    while(local_fact % 10 == 0){
        local_fact /= 10;
        puts("oh no");
    }
    
    
    
    printf("local_fact: %zu\n", local_fact);
    MPI_Reduce(&local_fact, &rtn, 1, MPI_UNSIGNED_LONG_LONG, MPI_PROD, 0, *world);
    puts("Reduced");
    
    

    if(Rank == 0)
        return rtn%100000;
    return -1;
}















int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); // Initializing MPI

    MPI_Comm world = MPI_COMM_WORLD; // Communicator

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize); // Gives amount of nodes running in parallel
    MPI_Comm_rank(world, &myRank); // Gives the rank (number) node
    //MPI_Get_processor_name(processorName, &processSize); 
    srand(time(0));                           // Gives the processor name of current node

    
    //size_t fac = 1000000000000;
    //size_t fac = 20; 
    size_t fac = 1000000; 
    puts("Start factorial!!");
    size_t result = factorial(fac, &world, worldSize, myRank);
    //size_t results = factorialTest(fac, &world, worldSize, myRank);
    if(myRank == 0){
        //printf("Ree %zu \n",results);
        printf("eeR %zu\n", result);
    }
    puts("Done factorial!!");


    MPI_Finalize(); // Finalizing MPI

    return 0;
}
