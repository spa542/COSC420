#ifndef _STACK_C_
#define _STACK_C_
#include<stdio.h> // I/O
#include<stdlib.h> // Standard library functions
#include<mpi.h> // MPI Library
#include<stdbool.h> // bool

struct stack {
    unsigned long long int data;
    struct stack *ptr;
};

typedef struct stack Stack;
typedef Stack *stackPtr;

// Stack functions for BIG ackermann integers

// Push for the stack
void push(stackPtr*, unsigned long long int);
// Pop for the stack
unsigned long long int pop(stackPtr*);
// Print the values of the stack
void print(stackPtr*);
// Returns the size of the stack
int count(stackPtr*);

#endif // _STACK_C
