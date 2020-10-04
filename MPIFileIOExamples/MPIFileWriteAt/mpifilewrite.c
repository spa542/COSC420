#include<stdio.h> // printf
#include<mpi.h> // MPI Library
#include<stdlib.h> // Standar library
#include<string.h> // String functions
#include<time.h> // time function

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    if (argc != 2) {
        fprintf(stderr, "Can only be 2 arguments!\n");
        MPI_Finalize();
        return 0;
    }

    srand(time(0) + myRank);

    int N = atoi(argv[1]); // How many integers each node will print
    int nums[N], i; // Initialize the variables
    char buf[N * 3 + 1]; // Create a buffer, size of amount of integers for each processor, plus the endline char
    memset(buf, '\0', N * 3 + 1); // Set the buffer
    char tmp[4]; // Create a tmp buffer

    MPI_File fh; // File handle for MPI
    int offset = N*myRank*sizeof(int); // Create the separation based on myRank and the amount each will write
    
    for (i = 0; i < N; i++) {
        nums[i] = rand() % 100; // Set each element of the array
        sprintf(tmp, "%d ", nums[i]); // tmp will hold what numbers are input (to be printed!)
        strcat(buf, tmp); // concatenate the formatting to our large buffer
    }

    printf("Rank %d numbers:\n%s\n", myRank, buf); // Print out what each node has in its buffer

    MPI_File_open(world, "datafile", 
            MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh); // Open the file

    printf("Rank: %d, Offset: %d\n", myRank, offset); // Print the offset for each node

    // This is the command to see the contents of the datafile
    // hexdump -v -e '5/4 "%3d"' -e '"\n"' datafile
    MPI_File_write_at(fh, offset, nums, N, MPI_INT, MPI_STATUS_IGNORE); // Write to the file
     
    MPI_File_close(&fh); // Close the file after use

    MPI_Finalize();

    return 0;
}
