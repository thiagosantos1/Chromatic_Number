#include <stdio.h>
#include <stdlib.h>

/* 1 point */
/**
 * Create a program that takes an long integer from the command line and sums
 * the value of each of its digits. i.e. the number 316 should sum to 3+1+6 or
 * 10.  Print the number with its "sum".
 *
 * Example input/output:
 * ./h2 316
 * num = 316, sum = 10
 * ./h2 -98374534984535
 * num = -98374534984535, sum = 77
 */


void sumEachBit(long int num, int * sum)
{

  while(num >= 10){

    (*sum) += num%10;
    num /=10;
  }

  if(num !=0){
    (*sum) += num;
  }
 
}

int main(int argc, char * argv[]){
  
  long int num;
  int sum=0;
  
  if(argc <2){
    
    printf("Usege <Num> %s\n", argv[0]);
    exit(1);
  }
  
  num = atol(argv[1]);
  
  sumEachBit(labs(num), &sum);
  
  printf("num = %ld, sum = %d\n", num, sum);
  
  return 0;
  
  
}




