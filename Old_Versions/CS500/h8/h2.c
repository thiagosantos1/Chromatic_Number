#include <stdlib.h>
#include <stdio.h>

/* 1 point */

/**
 * Like h1.c, make a function called fib to compute the nth Fibonacci number
 * however make it using a loop, rather than recursive.  The function should
 * take an integer, but return a unsigned long integer.
 */

unsigned long int fibo(int fiboSeq) 
{
  unsigned long int last_fibos[2] = {0,1}; // save previous 2 fibo - start with 0 and 1
  unsigned long int fib;
  
  if(fiboSeq <0){
    printf("Please, enter a positive value\n");
    exit(1);
  }
  fib = fiboSeq < 1 ? last_fibos[0]: last_fibos[1]; // in case fiboSeq is 0 or 1 - we already have it
  
  for(int i=2; i<=fiboSeq; i++){
    
    fib = last_fibos[0] + last_fibos[1];
    last_fibos[0] = last_fibos[1];
    last_fibos[1] = fib;
  }
  
  return fib;
}

/**
 * Make a main function that takes a command line parameter and converts it
 * to an integer and passes that to the fib() function you created above to
 * print the nth Fibonacci number.
 * Example input/output:
 * ./h2 1200
 * 8665637060948656192
 */


int main(int argc, char * argv[])
{
  if(argc<2){
    printf("Usage <fib num> %s\n", argv[0]);
    exit(1);
  }
  
  printf("%ld\n", fibo(atoi(argv[1])) );
  return 0;
}