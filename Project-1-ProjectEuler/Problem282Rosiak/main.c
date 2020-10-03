#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool
#include<math.h> // Math functions
#include"stack.h" // Stack functions

#define reduce 1475789056

// Knuth Arrow function
unsigned long long knuthArrow(unsigned long long a, unsigned long long b) {
    a %= reduce;
    b %= reduce;
    return ((unsigned long long)pow(a, b)) % reduce;
}

// Ackermann function using closed forms
unsigned long long ack(unsigned long long m, unsigned long long n) {
    m %= reduce; // reduce the number by mod 14^8
    n %= reduce; // reduce the number by mod 14^8
    /*
    push(top, m);
    while(count(top) != 0) {
        m = pop(top);
      skipStack:
        if (m == 0) {
            n = ((n % reduce) + (1 % reduce)) % reduce;
        } else if (m == 1) {
            n = ((n % reduce) + (2 % reduce)) % reduce;
        } else if (m == 2) {
            n = 2 * n + 3;
        } else if (m == 3) {
            n = pow(2, n + 3) - 3;
        } else if (m == 4) {
            n = knuthArrow(2, knuthArrow(2, n + 3)) - 3; 
        } else if (m == 5) {
            n = knuthArrow(2, knuthArrow(2, knuthArrow(2, n + 3))) - 3; 
        } else {
            n = knuthArrow(2, knuthArrow(2, knuthArrow(2, knuthArrow(2, n + 3)))) - 3; 
        }
        } else if (n == 0) {
            --m;
            n = 1;
            goto skipStack;
        } else {
            push(top, m - 1);
            --n;
            goto skipStack;
        }
    }
    */
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
        n = knuthArrow(2, knuthArrow(2, n + 3)) - 3; 
    } else if (m == 5) {
        n = knuthArrow(2, knuthArrow(2, knuthArrow(2, n + 3))) - 3; 
    } else {
        n = knuthArrow(2, knuthArrow(2, knuthArrow(2, knuthArrow(2, n + 3)))) - 3; 
    }
    return n;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    //stackPtr newptr = NULL; // Declare a pointer that starts the top of the stack
    
    printf("A(1,0) = %lld\n", ack(1,0));

    printf("A(2,2) = %lld\n", ack(2,2));

    printf("A(3,3) = %lld\n", ack(3,3));

    printf("A(4,1) = %lld\n", ack(4,1));
    printf("A(4,2) = %lld\n", ack(4,2));
    printf("A(4,3) = %lld\n", ack(4,3));

    printf("A(4,4) = %lld\n", ack(4,4));

    MPI_Finalize();

    return 0;
}
