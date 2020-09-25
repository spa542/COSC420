#include"stack.h"

// Push function
void push(stackPtr *top, unsigned long long int x) {
    stackPtr newNode;

    // allocating memory
    newNode = malloc(sizeof(Stack));

    // pushing value at the top of the stack if there is space
    if (newNode != NULL) {
        newNode->data = x;
        newNode->ptr = *top;
        *top = newNode;
    } else {
        printf("Overflow\n");
    }
}

// Pop function
unsigned long long int pop(stackPtr *top) {
    int popVal; // variable for value at the top
    stackPtr temp; // temp pointer

    temp = *top;
    popVal = (*top)->data;
    *top = (*top)->ptr;
    free(temp); // free temporary pointer value
    return popVal;
}

// Print function
void print(stackPtr *top) {
    stackPtr tmp = *top;
    while(tmp != NULL) {
        printf("%lld\n", tmp->data);
        tmp = tmp->ptr;
    }
}

// Count function
int count(stackPtr *top) {
    stackPtr tmp = *top;
    int acc = 0;
    while(tmp != NULL) {
        acc++;
        tmp = tmp->ptr;
    }
    return acc;
}
