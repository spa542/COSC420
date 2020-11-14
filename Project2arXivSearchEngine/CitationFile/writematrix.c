#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct IndexNode {
    char id[18];
    long int index;
} inode;

#define num_papers 1628188
#define file_length 10913892

int main() {

    // Create the necessary file pointers
    FILE* readCitations = NULL;
    FILE* writeMat = NULL;
    FILE* writeMatIndex = NULL; 
    FILE* readIndex = NULL;

    // Open the file to read the citation files in
    readCitations = fopen("arxiv-citations.txt", "r");
    // Read the index file to work with the matrix array
    readIndex = fopen("indexfile", "r");
    // Open the file to write the matrix into
    writeMat = fopen("matrixfile", "w");
    // Open the file to write the indices of the matrix
    //writeMatIndex = fopen("matrixfileindex", "w");

    if (!readCitations || !writeMat || !readIndex) { // If changed back, then fix this TODO
        puts("One of the three files broke :(");
        return 0;
    }

    /*
    // THIS IS FOR CREATING THE INDEX FILE BASED OFF OF THE CITATION DOCUMENT
    // Index for the indexnode struct and array counter
    long int index = 0;
    // Count the amount of papers to make sure it matches
    long int count = 0;
    // tmp array for strings
    char tmp[18];
    // Array for index nodes
    inode* writeIndex = (inode*)malloc(num_papers*sizeof(inode));
    memset(writeIndex, 0, num_papers*sizeof(inode));
    // Must create the new index first
    while (index < num_papers) {
        // TESTING
        if (!fgets(tmp, 18, readCitations)) {
            break;
        }
        inode newNode;
        // Copy the id into the index node
        strcpy(newNode.id, tmp);
        newNode.index = index;
        // Replace the \n
        newNode.id[strlen(newNode.id) - 1] = '\0';
        // Add to the array of structs
        writeIndex[index] = newNode;
        // Test print
        printf("ID: %s\n", writeIndex[index].id);
        printf("Index: %ld\n", writeIndex[index].index);
        // Skip intermediate lines (for now)
        while (fgets(tmp, 18, readCitations)) {
            if (tmp[0] == '+' && tmp[1] == '+') {
                break;       
            }
        }
        // Increment extra stuff
        index++;
        count++;
    }
    // Write the array to the specified file
    //fwrite(writeIndex, sizeof(inode), num_papers, writeMatIndex);
    printf("Count of papers read in %ld vs. known %ld\n", count, num_papers);
    free(writeIndex);
    fclose(writeMatIndex);

    // TESTING writeMatIndex file
    FILE* readTest = NULL;
    readTest = fopen("matrixfileindex", "r");
    inode* testarr = (inode*)malloc(100*sizeof(inode));
    memset(testarr, 0, 100*sizeof(inode));
    fread(testarr, sizeof(inode), 100, readTest);
    int i;
    puts("TESTING THE FILE THAT WAS WRITTEN TO...");
    for (i = 0; i < 100; i++) {
        printf("Struct %d\n" , i + 1);
        printf("id: %s\n", testarr[i].id);
        printf("index: %ld\n", testarr[i].index);
    }
    fclose(readTest);
    free(testarr);
    */

    /*
    FILE* readit = NULL;
    readit = fopen("matrixfileindex", "r");
    inode* check = (inode*)malloc(num_papers*sizeof(inode));
    memset(check, 0, num_papers*sizeof(inode));
    fread(check, sizeof(inode), num_papers, readit);
    int i;
    for (i = 0; i < num_papers; i++) {
        printf("id = %s\n", check[i].id);
    }
    free(check);
    fclose(readit);
    */


    // Timing
    time_t first, second;
    // Create the pointer to hold each row of the matrix
    double* row = NULL;
    // Create the index array to keep track of each index and read it in
    inode* indices = (inode*)malloc(num_papers*sizeof(inode));
    memset(indices, 0, num_papers*sizeof(inode));
    fread(indices, sizeof(inode), num_papers, readIndex);
    fclose(readIndex);
    // Done reading the index structs in
    // Count the amount of papers to make sure it matches
    long int count = 0;
    // tmp array for strings
    char tmp[18];
    // Counter
    long int i;
    // Test bool
    bool allZeros = false;
    bool shouldPrint = false;
    // Benchmark number
    long int benchmark = 200;
    // Start the loop
    first = time(NULL);
    while (count < num_papers) {
        // Need to iterate over the amount of papers in the indexfile
        // and find the right paper id that matches in the arxiv file
        while (fgets(tmp, 18, readCitations)) {
            // Kill the endline so somparisons work
            tmp[strlen(tmp) - 1] = '\0';
            if (strcmp(indices[count].id, tmp) == 0) {
                /*
                puts("Found it!!!!!");
                printf("struct id: %s\nfound id: %s\n", indices[count].id, tmp);
                */
                break;
            }
            // Skip all of the other elements until we get to the "next" paper for 
            // citation checking
            while(fgets(tmp, 18, readCitations)) {
                if (tmp[0] == '+' && tmp[1] == '+') {
                    break;
                }
            }
            // If we reach the end of the file, the loops will hit NULL and skip!!!!
        }
        // We know the structure and the order already
        // Will be a minus row next... skip it!!!!
        fgets(tmp, 18, readCitations); 
        row = (double*)malloc(num_papers*sizeof(double));
        memset(row, 0, sizeof(double));
        // Initialize the row
        for (i = 0; i < num_papers; i++) {
            row[i] = 0;
        }
        // If we couldnt find the string, just put an all zero row in its place
        // Read all of the citations in and fill the row vector until we read the
        // dividing line
        while(fgets(tmp, 18, readCitations)) {
            if (tmp[0] == '+' && tmp[1] == '+') {
                break;
            }
            tmp[strlen(tmp) - 1] = '\0';
            for (i = 0; i < num_papers; i++) {
                if (strcmp(tmp, indices[i].id) == 0) {
                    row[i] = 1; 
                }
            }
            // Print it out
            //shouldPrint = true; 
        }
        // Write the row to the file after the matrix row has been filled
        fwrite(row, sizeof(double), num_papers, writeMat);
        /*
        // Test Print
        if (shouldPrint) {
            // Test
            printf("Paper %ld\n", count);
            for (i = 0; i < num_papers; i++) {
                if (row[i] == 1) {
                    puts("we have a winner!");
                }
            }
        }
        */
        // Reset the pointer to the beginning of the file
        fseek(readCitations, 0, SEEK_SET);
        shouldPrint = false;
        count++;
        free(row);
        if (count % benchmark == 0) {
            printf("Benchmark %ld\n", count / benchmark);
        }
    }
    second = time(NULL);
    printf("Count of papers read in %ld vs. known %ld\n", count, num_papers);
    printf("Time in seconds to complete: %ld\n", second - first);
    free(indices);

    // Close the files
    fclose(readCitations);
    fclose(writeMat);

    /*
    // TEST matrix write file
    puts("STARTING TEST OF WRITE FILE");
    FILE* yeet = NULL;
    yeet = fopen("matrixfile", "r");
    double* readme = NULL;
    long int j;
    int sumcheck = 0;
    for (i = 0; i < 200; i++) {
        readme = (double*)malloc(num_papers*sizeof(double));
        memset(readme, 0, num_papers*sizeof(double));
        fread(readme, sizeof(double), num_papers, yeet);
        for (j = 0; j < num_papers; j++) {
            sumcheck += readme[j];
            if (readme[j] == 1) {
                printf("Paper %ld\n", i);
                puts("we have a winner!");
            }
        }
        if (sumcheck == 0) {
            printf("Paper %ld\n", i);
            puts("all zeros row");
        }
        sumcheck = 0;
        free(readme);
    }
    fclose(yeet);
    */
    
    return 0;
}
