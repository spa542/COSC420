#include<stdio.h>
#include "BigIntegerSingleFile.cpp"

/*
 * 1. gcc -c the .c files
 * 2. g++ -c the .cpp files
 * 3. g++ the .o's together into one executable
 */

int main(){
  BigInteger* a = makeBigIntStr("999999999999999");
  BigInteger* b = makeBigIntStr("999999999999999");

  printf("a*b = %s\n", c_str(c_mult(a,b)));

  return 0;
}
