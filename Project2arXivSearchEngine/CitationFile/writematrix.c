#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct IndexNode {
    char id[18];
    long int index;
} inode;

#define num_papers 1628188

int main() {

    // Create the necessary file pointers
    FILE* readCitations = NULL;
    FILE* writeMat = NULL;
    FILE* writeMatIndex = NULL; 
    FILE* readIndex = NULL;

    // Open the file to read the citation files in
    readCitations = fopen("arxiv-citations.txt", "r");
    // Read the index file to work with the matrix array
    readIndex = fopen("matrixfileindex", "r");
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
        fgets(tmp, 18, readCitations);
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
    fwrite(writeIndex, sizeof(inode), num_papers, writeMatIndex);
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
    //bool shouldPrint = false;
    // Start the loop
    while (count < num_papers) {
        // We know the structure and the order already
        // Just skip the first two lines of each section (id of paper and - block)
        fgets(tmp, 18, readCitations); 
        fgets(tmp, 18, readCitations); 
        row = (double*)malloc(num_papers*sizeof(double));
        memset(row, 0, sizeof(double));
        // Initialize
        for (i = 0; i < num_papers; i++) {
            row[i] = 0;
        }
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
        shouldPrint = false;
        */
        count++;
        free(row);
    }
    printf("Count of papers read in %ld vs. known %ld\n", count, num_papers);
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
    for (i = 0; i < 40; i++) {
        readme = (double*)malloc(num_papers*sizeof(double));
        memset(readme, 0, num_papers*sizeof(double));
        fread(readme, sizeof(double), num_papers, yeet);
        for (j = 0; j < num_papers; j++) {
            if (readme[j] == 1) {
                printf("Paper %ld\n", i);
                puts("we have a winner!");
            }
        }
        free(readme);
    }
    fclose(yeet);
    */
    
    return 0;
}
