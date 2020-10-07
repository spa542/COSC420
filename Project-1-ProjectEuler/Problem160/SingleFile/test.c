#include<stdio.h>
#include "BigIntegerSingleFile.cpp"

/*
 * 1. gcc -c the .c files
 * 2. g++ -c the .cpp files
 * 3. g++ the .o's together into one executable
 */

int main(){
    BigInteger* zero = makeBigIntStr("0");
    BigInteger* one = makeBigIntStr("1");
    BigInteger* ten = makeBigIntStr("10");
    BigInteger* a = makeBigIntStr("999999999999999");
    BigInteger* b = makeBigIntStr("999999999999999");

    printf("a*b = %s\n", c_str(c_mult(a,b)));
    a = c_mult(a,b);
    printf("a*b = %s\n", c_str(a));



    puts("Sub");
    printf("a-1 = %s\n", c_str(c_sub(a,one)));
    a = c_sub(a,one);

    printf("a = %s\n", c_str(a));


    puts("mod jawn");
    
    printf("a = %s\n", c_str(a));
    printf("a%10 =%s\n", c_str(c_mod(a,ten)));
    
    while((c_eqeq(c_mod(a,ten), zero)) == 1){
        puts("ree");
        a = c_div(a,ten);
    }
    
    puts("Print");
    printf("a = %s\n", c_str(a));

    a = c_pp(a);

    printf("a = %s\n", c_str(a));

    char str[256];
    unsigned long long x = 989;
    sprintf(str, "%llu",x);

    printf("String: %s", str);
  return 0;
}














//
