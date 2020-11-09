#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct MetaDataNode {
    char id[18];
    char title[384];
    char author[36664];
    char abstract[6093];
} mdnode;

#define FILE_LINES 8140940

int main() {

    // Metadata has been calculated, now need to create the structs, fix the strings, 
    // and then write them to a file to be used later
    FILE* fh = NULL;

    fh = fopen("arxiv-metadata.txt", "r");

    if (fh == NULL) {
        fprintf(stderr, "Error opening file");
        return 0;
    }

    long int is = 0;
    int i;
    int count = 1;
    long int cap = FILE_LINES / 5;
    printf("# of papers: %ld\n", cap);
    puts("BEFORE mnode");
    printf("%ld\n", cap/16);
    mdnode *arr = (mdnode*)malloc((cap/16)*sizeof(mdnode));
    if (!arr) {
        puts("Broken");
    }
    //mdnode arr[20];
    puts("After mnode");
    memset(arr, 0, (cap/16)*sizeof(mdnode));
    char tmp[10];
    puts("BEFORE LOOP");
    while (is < 1) {
        mdnode newNode;
        fgets(newNode.id, 18, fh);
        fgets(newNode.title, 384, fh);
        fgets(newNode.author, 36664, fh);
        fgets(newNode.abstract, 6093, fh);
        fgets(tmp, 10, fh);
        /*
        for (i = 0; i < 1; i++) {
            printf("ID: %s\n", newNode.id);
            printf("Title: %s\n", newNode.title);
            printf("Author(s): %s\n", newNode.author);
            printf("Abstract: %s\n", newNode.abstract);
        }
        */
        puts("Breaks?");
        strcpy(arr[is].id, newNode.id);
        puts("huh?");
        strcpy(arr[is].title, newNode.title);
        puts("what?");
        strcpy(arr[is].author, newNode.author);
        puts("why");
        strcpy(arr[is].abstract, newNode.abstract);
        puts("problem?");
        is++;
    }
    puts("AFTER LOOP");
    for (i = 0; i < 1; i++) {
        printf("ID: %s\n", arr[i].id);
        printf("Title: %s\n", arr[i].title);
        printf("Author(s): %s\n", arr[i].author);
        printf("Abstract: %s\n", arr[i].abstract);
    }

    free(arr);
    fclose(fh);

    return 0;
}
