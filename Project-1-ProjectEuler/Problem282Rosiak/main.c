#include<stdio.h> // I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // sleep
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool
#include<math.h> // Math functions
#include"BigIntegerSingleFile.cpp" // Big Int library in c++

#define reducer 1475789056

// Log2 Exponent function (iterative)
BigInteger* powIter(BigInteger* xt, BigInteger* nt) {
    BigInteger* x = makeBigIntStr(c_str(xt));
    BigInteger* n = makeBigIntStr(c_str(nt));
    BigInteger* testZero = makeBigIntStr("0");
    if (c_eqeq(n, testZero)) {
        return testZero;
    }

    BigInteger* y = makeBigIntStr("1");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* two = makeBigIntStr("2");
    BigInteger* tmp = NULL;
    while (c_gt(n, one)) {
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
        destroy(tmp);
    }
    BigInteger* tmp4 = c_mult(x, y);
    destroy(y);
    destroy(one);
    destroy(testZero);
    destroy(two);
    return tmp4;
}

// Log2 Exponent function (iterative)
BigInteger* powIterMod(BigInteger* xt, BigInteger* nt) {
    BigInteger* x = makeBigIntStr(c_str(xt));
    BigInteger* n = makeBigIntStr(c_str(nt));
    puts("Break in function 1");
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
        destroy(tmp);
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
    //printf("Result of knuth arrow: %s\n", c_str(b));
    return n;
}

BigInteger* knuthArrow2(BigInteger* a, BigInteger* b) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* copies = knuthArrow(atmp,btmp);
    BigInteger* n = powIter(atmp, copies);
    //printf("Result of knuth arrow 2: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow3(BigInteger* a, BigInteger* b, MPI_Comm* world, int worldSize, int myRank) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* copies = knuthArrow2(atmp,btmp);



    BigInteger* n = powIter(atmp, copies);
    //printf("Result of knuth arrow 3: %s\n", c_str(n));
    return n;
}

BigInteger* knuthArrow4(BigInteger* a, BigInteger* b, MPI_Comm* world, int worldSize, int myRank) {
    BigInteger* atmp = makeBigIntStr(c_str(a));
    BigInteger* btmp = makeBigIntStr(c_str(b));
    BigInteger* copies = knuthArrow3(atmp,btmp, world, worldSize, myRank);



    BigInteger* n = powIterMod(atmp, copies);
    //printf("Result of knuth arrow 4: %s\n", c_str(n));
    return n;
}

// Ackermann function using closed forms
BigInteger* ack(BigInteger* mt, BigInteger* nt, MPI_Comm* world, int worldSize, int myRank) {
    BigInteger* m = makeBigIntStr(c_str(mt));
    BigInteger* n = makeBigIntStr(c_str(nt));
    BigInteger* zero = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* two = makeBigIntStr("2");
    BigInteger* three = makeBigIntStr("3");
    BigInteger* four = makeBigIntStr("4");
    BigInteger* five = makeBigIntStr("5");
    BigInteger* six = makeBigIntStr("6");
    BigInteger* nplus3 = c_add(n, three);
    BigInteger* reduce = makeBigIntStr("1475789056");
    BigInteger* temp = NULL;
    BigInteger* temp2 = NULL;

    if (c_eqeq(m, zero)) {
        temp = c_add(n, one);
    } else if (c_eqeq(m, one)) {
        temp = c_add(n, two);
    } else if (c_eqeq(m, two)) {
        temp2 = c_mult(two, n);
        temp = c_add(temp2, three);
    } else if (c_eqeq(m, three)) {
        temp2 = powIter(two, nplus3);
        temp = c_sub(temp2, three);
    } else if (c_eqeq(m, four)) {
        temp = knuthArrow2(two, nplus3);
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;

        temp2 = c_sub(temp, three);
        destroy(temp);
        temp = temp2;
        
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
    } else if (c_eqeq(m, five)) {
        temp = knuthArrow3(two, nplus3, world, worldSize, myRank);
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;

        temp2 = c_sub(temp, three);
        destroy(temp);
        temp = temp2;
        
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
    } else if (c_eqeq(m, six)) {
        temp = knuthArrow4(two, nplus3, world, worldSize, myRank);
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;

        temp2 = c_sub(temp, three);
        destroy(temp);
        temp = temp2;
        
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
    }
    destroy(m);
    destroy(n);
    destroy(zero);
    destroy(one);
    destroy(two);
    destroy(three);
    destroy(four);
    destroy(five);
    destroy(six);
    destroy(nplus3);
    destroy(reduce);
    return temp;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    MPI_Comm world = MPI_COMM_WORLD;

    int myRank, worldSize;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    /*
    BigInteger* a = makeBigIntStr("1000000000000000000000000");
    BigInteger* b = makeBigIntStr("2000");

    BigInteger* c = c_mult(a, b);

    printf("%s\n", c_str(c));

    destroy(a);
    destroy(b);
    destroy(c);
    */

    /*
    BigInteger* first = makeBigIntStr("2");
    BigInteger* second = makeBigIntStr("4");
    printf("%s\n", c_str(powIterMod(first, second)));
    printf("2up->4 = %s\n", c_str(knuthArrow(first, second)));
    printf("2up->up->4 = %s\n", c_str(knuthArrow2(first,second)));
    printf("2up->up->up->4 = %s\n", c_str(knuthArrow3(first,second)));
    printf("2up->up->up->up->4 = %s\n", c_str(knuthArrow4(first,second)));
    destroy(first);
    destroy(second);
    */
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
    */

    /*
    int i;
    for (i = 0; i <= 6; i++) {

        sum += (ack(i,i) % reduce);
    }
    sum %= reduce;
    printf("sum: %lld\n", sum);
    */
    BigInteger* sum = makeBigIntStr("0");
    BigInteger* temp = NULL;
    BigInteger* temp2 = NULL;
    BigInteger* reduce = makeBigIntStr("1475789056");

    BigInteger* zero = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* two = makeBigIntStr("2");
    BigInteger* three = makeBigIntStr("3");
    BigInteger* four = makeBigIntStr("4");
    BigInteger* five = makeBigIntStr("5");
    BigInteger* six = makeBigIntStr("6");

    if (myRank == 0) {
        temp = ack(zero, zero, &world, worldSize, myRank);
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));

        temp = ack(one, one, &world, worldSize, myRank);
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));

        temp = ack(two, two, &world, worldSize, myRank);
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));

        temp = ack(three, three, &world, worldSize, myRank);
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));

        temp = ack(four, four, &world, worldSize, myRank);
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));
    }

    temp = ack(five, five, &world, worldSize, myRank);
    if (myRank == 0) {
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));
    }

    temp = ack(six, six, &world, worldSize, myRank);
    if (myRank == 0) {
        printf("ack:%s\n", c_str(temp));
        temp2 = c_mod(temp, reduce);
        destroy(temp);
        temp = temp2;
        temp2 = c_add(sum, temp);
        destroy(sum);
        sum = temp2;
        printf("new sum:%s\n", c_str(sum));
    }

    if (myRank == 0) {
        printf("Final sum: %s\n", c_str(sum));
    }

    destroy(zero);
    destroy(one);
    destroy(two);
    destroy(three);
    destroy(four);
    destroy(five);
    destroy(six);
    destroy(reduce);
    if (myRank == 0) {
        destroy(temp);
        destroy(temp2);
    }
    destroy(sum);

    MPI_Finalize();

    return 0;
}
