#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool
#include"stack.h" // Stack functions

int ackermann(unsigned long long int n, unsigned long long int m) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else if ((m > 0) && (n > 0)) {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

unsigned long long int ack(stackPtr *top, unsigned long long int n, unsigned long long int m) {
    push(top, m);
    while(count(top) != 0) {
        m = pop(top);
      skipStack:
        if (m == 0) {
            n += 1;
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
    return n;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    stackPtr newptr = NULL; // Declare a pointer that starts the top of the stack
    
    printf("A(1,0) = %lld\n", ack(&newptr,1,0));
    //printf("A(1,0) = %d\n", ackermann(1,0));

    //printf("A(2,2) = %d\n", ackermann(2,2));
    printf("A(2,2) = %lld\n", ack(&newptr,2,2));

    //printf("A(3,4) = %d\n", ackermann(3,4));
    printf("A(3,3) = %lld\n", ack(&newptr,3,3));

    printf("A(4,4) = %lld\n", ack(&newptr,4,4));

    MPI_Finalize();

    return 0;
}


