#include <stdlib.h>
#include <stdio.h>

/* 1 point */

/**
 * Make a recursive function to compute the nth Fibonacci number, call it fib:
 * It should take a integer argument specifying the nth Fibonacci number to
 * compute. The function should take an integer but return an unsigned long
 * integer.
 */

/*
  I dicide to change a lit bit on how to solve this question by using DP, just because
  I have been learning DP and I think this is a good time to use it. Save memory and process
  it's just another option, in case we decide for a optimze algorithm
*/
unsigned long int fiboDP(int fiboSeq, unsigned long int memorization[]) // get also an array to use memorization and reduce computation
{
  if(fiboSeq <=0)
    return 0;
  else if(fiboSeq ==1)
    return 1;
  else if( ! memorization[fiboSeq]) // if not calculated yet that fibo, then calculated
    memorization[fiboSeq] = fiboDP(fiboSeq -1, memorization) + fiboDP(fiboSeq -2, memorization);

  return memorization[fiboSeq]; // if it has already been calculated for that fibo
}

unsigned long int fibo(int fiboSeq)
{
  if(fiboSeq <=0)
    return 0;
  else if(fiboSeq ==1)
    return 1;
  
  return fibo(fiboSeq -1) + fibo(fiboSeq -2);
}

/**
 * Make a main function that takes a command line parameter and converts it
 * to an integer and passes that to the fib() function you created above to
 * print the nth Fibonacci number.
 * Example input/output:
 * ./h1 10
 * 55
 */

int main(int argc, char * argv[])
{
  if(argc<2){
    printf("Usage <fib num> %s\n", argv[0]);
    exit(1);
  }
  //unsigned long int memorization[500] = {-1}; // gonna use Dinamic Programing with memorization, cause I don't wanna to recompute the same fibonacci more than once
  
  //printf("%ld\n", fibo(atoi(argv[1]), memorization) ); // with DP
  printf("%ld\n", fibo(atoi(argv[1])) );
 
  return 0;
}