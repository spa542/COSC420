#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include"PageRank.h"

// Defining the buffer length for processor name
#define pNameSize MPI_MAX_PROCESSOR_NAME

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); // Initializing MPI

    MPI_Comm world = MPI_COMM_WORLD; // Communicator

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize); // Gives amount of nodes running in parallel
    MPI_Comm_rank(world, &myRank); // Gives the rank (number) node
    srand(time(0));      

    printf("Hi\n");    
    int i;

    if(myRank == 0){
      int arr[] = {
      2,0,0,0,
      4,0,-1,-1,
      4,0,-1,-1,
      4,0,-1,-1,
      5,-1,-1,-1
      };
      int* tmp = (int*)malloc(5*4*sizeof(int));
      for(i=0; i<5*4; i++){
      tmp[i] = arr[i];
      }
      printf("REE | Rank: %d\n", myRank);

      printf("open | Rank: %d\n", myRank);
      FILE* fh = fopen("scripttest", "w");
      printf("write | Rank: %d\n", myRank);
      fwrite(tmp, sizeof(int),20, fh);
      printf("close | Rank: %d\n", myRank);
      fclose(fh);
      free(tmp);
    }
    
    
    
/*   
    int* tes = (int*)malloc(20*sizeof(int));

    MPI_File fh; 
  
    MPI_File_open(world, "scripttest", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
   
    MPI_File_read(fh, tes, 20, MPI_INT, MPI_STATUS_IGNORE);
    
    MPI_File_close(&fh);

    int w;
    for(w=1; w<21; w++){
      printf("%d ", tes[w-1]);  
      if(w%4==0){
    puts("");
      }
    }
    free(tes);
 */  
    
    
    
    
    
    
    
    printf("BF PageRank | Rank: %d\n", myRank);
    double* rtn = pageRank(5, 4, &world, worldSize, myRank);
    
/*    
    if(myRank == 0){
      for(i=0; i<5; i++){
    printf("%f ", rtn[i]);    
      }
      puts("");
    }
*/
    free(rtn);
    MPI_Finalize(); // Finalizing MPI

    return 0;
}
