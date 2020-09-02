#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv); // pass through cli args

    MPI_Comm world = MPI_COMM_WORLD; // This constant gets set by the MPI lib

    puts("Hello World!");

    MPI_Finalize();

    return 0;
}
