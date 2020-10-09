#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // sleep
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool
#include<math.h> // Math functions
#include"stack.h" // Stack functions
#include"BigIntegerSingleFile.cpp" // Big Int library in c++

#define reduce 1475789056

// Knuth Arrow function
BigInteger* knuthArrow(BigInteger* a, BigInteger* b) {
    //a %= reduce;
    //b %= reduce;

    /*
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
    */
    BigInteger* tmp = NULL;
    BigInteger* tmp2 = NULL;
    BigInteger* n = makeBigIntStr("1");
    BigInteger* limit = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    while (c_lt(limit,b)) { 
        tmp = c_mult(n,a); 
        destroy(n);
        n = tmp;

        tmp2 = c_add(limit,one);
        destroy(limit);
        limit = tmp2;
    }
    tmp = tmp2 = NULL;

    printf("Result of knuth arrow: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow2(BigInteger* a, BigInteger* b) {
    /*
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
    */
    BigInteger* copies = knuthArrow(a,b);
    BigInteger* tmp = NULL;
    BigInteger* tmp2 = NULL;
    BigInteger* n = makeBigIntStr("1");
    BigInteger* limit = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    while (c_lt(limit,copies)) { 
        tmp = c_mult(n,a); 
        destroy(n);
        n = tmp;

        tmp2 = c_add(limit,one);
        destroy(limit);
        limit = tmp2;
    }
    tmp = tmp2 = NULL;

    printf("Result of knuth arrow 2: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow3(BigInteger* a, BigInteger* b) {
    /*
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
    */
    BigInteger* copies = knuthArrow2(a,b);
    BigInteger* tmp = NULL;
    BigInteger* tmp2 = NULL;
    BigInteger* n = makeBigIntStr("1");
    BigInteger* limit = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    while (c_lt(limit,copies)) { 
        tmp = c_mult(n,a); 
        destroy(n);
        n = tmp;

        tmp2 = c_add(limit,one);
        destroy(limit);
        limit = tmp2;
    }
    tmp = tmp2 = NULL;

    printf("Result of knuth arrow 3: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow4(BigInteger* a, BigInteger* b) {
    /*
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
    */
    BigInteger* copies = knuthArrow3(a,b);
    BigInteger* tmp = NULL;
    BigInteger* tmp2 = NULL;
    BigInteger* n = makeBigIntStr("1");
    BigInteger* limit = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* mod = makeBigIntStr("1475789056");
    while (c_lt(limit,copies)) { 
        tmp = c_mult(n,a); 
        destroy(n);
        n = tmp;

        tmp = c_mod(n,mod);
        destroy(n);
        n = tmp;

        tmp2 = c_add(limit,one);
        destroy(limit);
        limit = tmp2;
    }
    tmp = tmp2 = NULL;
    destroy(mod);

    printf("Result of knuth arrow 4: %s\n", c_str(n));
    return n;
}

// Ackermann function using closed forms
unsigned long long ack(unsigned long long m, unsigned long long n) {
    if (m == 0) {
        n += 1;
    } else if (m == 1) {
        n += 2;
    } else if (m == 2) {
        n = 2 * n + 3;
    } else if (m == 3) {
        n = pow(2, n + 3) - 3;
    } else if (m == 4) {
        //n = ((knuthArrow2(2, n + 3) % reduce) - (3 % reduce)) % reduce;
    } else if (m == 5) {
        //n = ((knuthArrow3(2, n + 3) % reduce) - (3 % reduce)) % reduce;
    } else if (m == 6) {
        //n = ((knuthArrow4(2, n + 3) % reduce) - (3 % reduce)) % reduce;
    }
    return n;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    /*
    BigInteger* a = makeBigIntStr("1000000000000000000000000");
    BigInteger* b = makeBigIntStr("2000");

    BigInteger* c = c_mult(a, b);

    printf("%s\n", c_str(c));

    destroy(a);
    destroy(b);
    destroy(c);
    //stackPtr newptr = NULL; // Declare a pointer that starts the top of the stack
    */

    BigInteger* first = makeBigIntStr("2");
    BigInteger* second = makeBigIntStr("4");
    printf("2up->4 = %s\n", c_str(knuthArrow(first,second)));
    printf("2up->up->4 = %s\n", c_str(knuthArrow2(first,second)));
    printf("2up->up->up->4 = %s\n", c_str(knuthArrow3(first,second)));
    printf("2up->up->up->up->4 = %s\n", c_str(knuthArrow4(first,second)));
    destroy(first);
    destroy(second);
    /*
    printf("A(1,0) = %lld\n", ack(1,0));

    printf("A(2,2) = %lld\n", ack(2,2));

    printf("A(3,3) = %lld\n", ack(3,3));

    printf("A(4,1) = %lld\n", ack(4,1));
    printf("A(4,2) = %lld\n", ack(4,2));
    printf("A(4,3) = %lld\n", ack(4,3));
    printf("A(0,0) = %lld\n", ack(0,0));

    printf("A(1,1) = %lld\n", ack(1,1));

    printf("A(2,2) = %lld\n", ack(2,2));

    printf("A(3,3) = %lld\n", ack(3,3));

    printf("A(4,4) = %lld\n", ack(4,4));

    printf("A(5,5) = %lld\n", ack(5,5));

    printf("A(6,6) = %lld\n", ack(6,6));

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
