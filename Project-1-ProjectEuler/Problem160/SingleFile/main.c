#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<math.h>
#include<limits.h> //MAX_INT
#include "BigIntegerSingleFile.cpp"

//16576

// Defining the buffer length for processor name
#define pNameSize MPI_MAX_PROCESSOR_NAME

typedef BigInteger* boi;



//watch -n1 squeue
//sbatch P160.sh

boi factorial(unsigned long long fact, MPI_Comm *world, int worldSize, int Rank){
    boi* collector = NULL;
    if(Rank == 0)
      collector = ;//TODO This is broken

    //printf("worldSize:%d Rank:%d\n", worldSize, Rank);

    boi ten = makeBigIntStr("10");
    boi one = makeBigIntStr("1");

    unsigned long long srt;
    unsigned long long fin;
    boi start;
    boi finish;
    boi local_fact = makeBigIntStr("1");
    boi rtn;
    char str[256];

    if(Rank == 0){
        start = makeBigIntStr("2");
        
        fin = (unsigned long long) (fact/worldSize);
        sprintf(str, "%llu", fin);   
        finish = makeBigIntStr(str);
    }else if(Rank == worldSize-1){
        srt = (unsigned long long) (((fact/worldSize) * Rank)+1);
        sprintf(str, "%llu", srt);   
        start = makeBigIntStr(str);

        fin = fact;
        sprintf(str, "%llu", fin);
        finish = makeBigIntStr(str); 
    }else{
        srt = (unsigned long long) (((fact/worldSize) * Rank)+1);
        sprintf(str, "%llu", srt);   
        start = makeBigIntStr(str);
        
        fin = (unsigned long long) (start + (fact/worldSize)-1);
        sprintf(str, "%llu", fin);   
        finish = makeBigIntStr(str);
    }

       
    boi i;
    //printf("Rank: %d | Start: %llu | Finish: %llu\n", Rank, start, finish);
    for(i=start; 1 == c_leeq(i,finish); i=c_pp(i)){
        local_fact = c_mult(local_fact, i);
        while((c_eqeq(c_mod(local_fact, ten), zero)) == 1)
            local_fact = c_div(local_fact, ten);
    }
    //printf("local_fact: %llu\n", local_fact);
    MPI_Gather(&local_fact, 1, MPI_UNSIGNED_LONG_LONG, collector, 1, MPI_UNSIGNED_LONG_LONG, 0, *world);//TODO
    

    if(Rank == 0){
        int w, q;
        for(w=2; w<(2*worldSize); w*=2){
            for(q=0; q<worldSize - w/2; q+=w){
               
                collector[q] = c_mult(collector[q], collector[q+w/2]);
                while((c_eqeq(c_mod(collector[q], ten), zero)) == 1)
                    collector[q] = c_div(collector[q], ten);
                
            }
        }
        rtn = collector[0]; 

        if(rtn >= 100000)
          rtn %= 100000;
        free(collector);
        return rtn;
    }
    return -1;
}














int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); // Initializing MPI

    MPI_Comm world = MPI_COMM_WORLD; // Communicator

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize); // Gives amount of nodes running in parallel

    
    MPI_Comm_rank(world, &myRank); // Gives the rank (number) node
    srand(time(0));                           // Gives the processor name of current node

    puts("Testing");

    boi result;
    boi fac; 
    fac = 50000; 
    
    boi one = 5000000000;//ULLONG_MAX;
    boi two = one-1;//ULLONG_MAX;
    
    boi jawn = overflow(one, two, 100000, true);
   
    printf("Jawn: %llu\n", jawn); 
    
    //result = factorial(fac, &world, worldSize, myRank);
    /*if(myRank == 0){
        //printf("Ree %zu \n",results);
        printf("eeR %llu\n", result);
        printf("WORLD SIZE: %d\n", worldSize);
    }
    //M
    //puts("Done factorial!!");
    if(myRank == 0){
        if(result == 16576){
            puts("NUT");
        }else{
            puts("REE");
        }
    }*/
    MPI_Finalize(); // Finalizing MPI

    return 0;
}
