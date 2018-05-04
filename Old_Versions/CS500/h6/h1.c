#include <stdio.h>
#include <stdlib.h>

/* 1 point */
/**
 * Create a program that takes a long integer from the command line and counts
 * the number of 1 bits in it and prints the count, make it also keep track of
 * the largest run of consecutive 1 bits and print that value as well.
 * 
 * Example input/output:
 * ./h1 -1
 * count = 64, largest run = 64
 * ./h1 345897345532
 * count = 17, largest run = 7
 */

void countSetBits(const long int num, int * count, int * largest)
{
  int  maxSeq =0;
  for(int i=0; i<64;i++){
    
    if(num & (1UL<< i)){
      maxSeq++;
      (*count)++;   
      if(maxSeq > *largest)
        (*largest) = maxSeq;
    }
    else{
  
      maxSeq =0;
    }
    
  }
}

int main(int argc, char * argv[]){
  
  long int num;
  int count=0, largest=0;
  
  if(argc <2){
    
    printf("Usege <Num> %s\n", argv[0]);
    exit(1);
  }
   
  num = atol(argv[1]);
  
  countSetBits(num, &count, &largest);
  
  printf("count = %d, largest run = %d\n", count, largest);
  
  return 0;
  
  
}




