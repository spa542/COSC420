#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // sleep
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool
#include<math.h> // Math functions
#include"stack.h" // Stack functions

#define reduce 1475789056

// Knuth Arrow function
unsigned long long knuthArrow(unsigned long long a, unsigned long long b) {
    //a %= reduce;
    //b %= reduce;

    unsigned long long n = a;
    unsigned long long limit = 0;
    while (limit < b - 1) {
        if (n > reduce) {
            n %= reduce;
        }
        n *= a;
        limit++;
    }
    n %= reduce;
    printf("Result of knuth arrow: %lld\n", n);
    return n;
}

unsigned long long knuthArrow2(unsigned long long a, unsigned long long b) {
    unsigned long long copies = knuthArrow(a,b);
    printf("Copies knuth arrow 2 = %lld\n", copies);
    unsigned long long limit = 0;
    unsigned long long n = a;
    while (limit < copies - 1) {
        if (n > reduce) {
            n %= reduce;
        }
        n *= a;
        limit++;
    }
    n %= reduce;
    printf("Result of knuth arrow 2: %lld\n", n);
    return n;
}

unsigned long long knuthArrow3(unsigned long long a, unsigned long long b) {
    unsigned long long copies = knuthArrow2(a,b); 
    printf("Copies knuth arrow 3 = %lld\n", copies);
    unsigned long long limit = 0;
    unsigned long long n = a;
    while (limit < copies - 1) {
        if (n > reduce) {
            n %= reduce;
        }
        n *= a;
        limit++;
    }
    n %= reduce;
    printf("Result of knuth arrow 3: %lld\n", n);
    return n;
}

unsigned long long knuthArrow4(unsigned long long a, unsigned long long b) {
    unsigned long long copies = knuthArrow3(a,b); 
    printf("Copies knuth arrow 4 = %lld\n", copies);
    unsigned long long limit = 0;
    unsigned long long n = a;
    while (limit < copies - 1) {
        if (n > reduce) {
            n %= reduce;
        }
        n *= a;
        limit++;
    }
    n %= reduce;
    printf("Result of knuth arrow 4: %lld\n", n);
    return n;
}

// Ackermann function using closed forms
unsigned long long ack(unsigned long long m, unsigned long long n) {
    if (m == 0) {
        n += 1;
        n %= reduce;
    } else if (m == 1) {
        n += 2;
        n %= reduce;
    } else if (m == 2) {
        n = 2 * n + 3;
        n %= reduce;
    } else if (m == 3) {
        n = pow(2, n + 3) - 3;
        n %= reduce;
    } else if (m == 4) {
        n = ((knuthArrow2(2, n + 3) % reduce) - (3 % reduce)) % reduce;
    } else if (m == 5) {
        n = ((knuthArrow3(2, n + 3) % reduce) - (3 % reduce)) % reduce;
    } else if (m == 6) {
        n = ((knuthArrow4(2, n + 3) % reduce) - (3 % reduce)) % reduce;
    }
    return n;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    //stackPtr newptr = NULL; // Declare a pointer that starts the top of the stack
   /* 
    printf("2up->4 = %lld\n", knuthArrow(2,4));
    printf("2up->up->4 = %lld\n", knuthArrow2(2,4));
    printf("2up->up->up->4 = %lld\n", knuthArrow3(2,4));
    printf("2up->up->up->up->4 = %lld\n", knuthArrow4(2,4));
    printf("A(1,0) = %lld\n", ack(1,0));

    printf("A(2,2) = %lld\n", ack(2,2));

    printf("A(3,3) = %lld\n", ack(3,3));

    printf("A(4,1) = %lld\n", ack(4,1));
    printf("A(4,2) = %lld\n", ack(4,2));
    printf("A(4,3) = %lld\n", ack(4,3));
    */
    printf("A(0,0) = %lld\n", ack(0,0));

    printf("A(1,1) = %lld\n", ack(1,1));

    printf("A(2,2) = %lld\n", ack(2,2));

    printf("A(3,3) = %lld\n", ack(3,3));

    printf("A(4,4) = %lld\n", ack(4,4));

    printf("A(5,5) = %lld\n", ack(5,5));

    printf("A(6,6) = %lld\n", ack(6,6));
    /*
    unsigned long long sum = 0;
    int i;
    for (i = 0; i <= 6; i++) {
        sum += (ack(i,i) % reduce);
    }
    sum %= reduce;
    printf("sum: %lld\n", sum);
    */

    MPI_Finalize();

    return 0;
}
