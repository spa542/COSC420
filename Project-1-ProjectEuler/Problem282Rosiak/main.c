#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // sleep
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool
#include<math.h> // Math functions
#include"stack.h" // Stack functions
#include"BigIntegerSingleFile.cpp" // Big Int library in c++

#define reducer 1475789056

// Log2 Exponent function (iterative)
BigInteger* powIter(BigInteger* x, BigInteger* n) {
    BigInteger* testZero = makeBigIntStr("0");
    if (c_eqeq(n, testZero)) {
        return testZero;
    }

    BigInteger* y = makeBigIntStr("1");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* two = makeBigIntStr("2");
    while (c_gt(n, one)) {
        BigInteger* tmp = NULL;
        tmp = c_mod(n, two);
        if (c_eqeq(tmp, testZero)) {
            BigInteger* tmp2 = c_mult(x, x);
            destroy(x);
            x = tmp2;

            tmp2 = c_div(n, two);
            destroy(n);
            n = tmp2;
        } else {
            BigInteger* tmp3 = c_mult(x, y);
            destroy(y);
            y = tmp3;

            tmp3 = c_mult(x, x);
            destroy(x);
            x = tmp3;

            tmp3 = c_sub(n, one);
            destroy(n);
            n = tmp3;
            tmp3 = c_div(n, two);
            destroy(n);
            n = tmp3;
        }
    }
    BigInteger* tmp4 = c_mult(x, y);
    destroy(y);
    destroy(one);
    destroy(testZero);
    destroy(two);
    return tmp4;
}

// Log2 Exponent function (iterative)
BigInteger* powIterMod(BigInteger* x, BigInteger* n) {
    BigInteger* testZero = makeBigIntStr("0");
    if (c_eqeq(n, testZero)) {
        return testZero;
    }

    BigInteger* y = makeBigIntStr("1");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* two = makeBigIntStr("2");
    BigInteger* reduce = makeBigIntStr("1475789056");
    BigInteger* tmp = NULL;
    while (c_gt(n, one)) {
        tmp = c_mod(n, two);
        if (c_eqeq(tmp, testZero)) {
            BigInteger* temper = c_mod(x, reduce); 
            BigInteger* tmp2 = c_mult(temper, temper);
            destroy(x);
            destroy(temper);
            x = tmp2;
            tmp2 = c_mod(x, reduce);
            destroy(x);
            x = tmp2;

            tmp2 = c_div(n, two);
            destroy(n);
            n = tmp2;
        } else {
            BigInteger* temper = c_mod(x, reduce);
            BigInteger* temper2 = c_mod(y, reduce);
            BigInteger* tmp3 = c_mult(temper, temper2);
            destroy(y);
            y = tmp3;
            tmp3 = c_mod(y, reduce);
            destroy(y);
            y = tmp3;

            tmp3 = c_mult(temper, temper);
            destroy(x);
            x = tmp3;
            tmp3 = c_mod(x, reduce);
            destroy(x);
            x = tmp3;

            destroy(temper);
            destroy(temper2);

            tmp3 = c_sub(n, one);
            destroy(n);
            n = tmp3;
            tmp3 = c_div(n, two);
            destroy(n);
            n = tmp3;
        }
        free(tmp);
    }
    BigInteger* temper = c_mod(x, reduce);
    BigInteger* temper2 = c_mod(y, reduce);
    BigInteger* tmp4 = c_mult(temper, temper2);
    BigInteger* rtn = c_mod(tmp4, reduce);
    destroy(y);
    destroy(one);
    destroy(testZero);
    destroy(two);
    destroy(tmp4);
    return rtn;
}

// Knuth Arrow function
BigInteger* knuthArrow(BigInteger* a, BigInteger* b) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* n = powIter(atmp, btmp);
    printf("Result of knuth arrow: %s\n", c_str(b));
    return n;
}

BigInteger* knuthArrow2(BigInteger* a, BigInteger* b) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* copies = knuthArrow(atmp,btmp);
    BigInteger* n = powIter(atmp, copies);
    printf("Result of knuth arrow 2: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow3(BigInteger* a, BigInteger* b) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* copies = knuthArrow2(atmp,btmp);
    BigInteger* n = powIter(atmp, copies);
    printf("Result of knuth arrow 3: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow4(BigInteger* a, BigInteger* b) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* copies = knuthArrow2(atmp,btmp);
    BigInteger* n = powIter(atmp, copies);
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
    BigInteger* second = makeBigIntStr("400");
    /*
    printf("%s\n", c_str(powIterMod(first, second)));
    */
    printf("2up->4 = %s\n", c_str(knuthArrow(first, second)));
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
