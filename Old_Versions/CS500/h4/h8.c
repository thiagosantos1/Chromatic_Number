#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * This program should test if a number provided on the command line is prime
 * or not.  To make this program efficient, only test if the number is evenly
 * divisible by two and odds up to the square root of the number itself.
 * The program should print a usage message or warning if no number is provided
 * or the number is less than 2 and should be able to handle numbers greater
 * than 4 billion.
 * Example input/output:
 * ./h8 9872349901
 * 9872349901 is prime
 * ./h8 65
 * 65 is not prime
 */

int numberIsPrime( long int number){
  
  int endCheck = sqrt(number) +1;
  
  if( (number %2) ==0)
    return -1; // not a prime 
    
  for(int i=3; i<=endCheck; i+=2 ){
    if( (number %i) ==0)
      return -1; // not a prime
    
  }	
  
  return 0; // prime number
  
}

int main(int argc, char * argv[]){
  
  if(argc<2){
    printf("Please provide a number for the program %s\n", argv[0]);
    exit(1);
  }
  
  if(atol(argv[1]) <=2 ){
    printf("Please provide a number greater than 2\n");
    exit(1);
  }
  
  
  if( numberIsPrime(atol(argv[1])) >= 0)
    printf("%ld is prime\n", atol(argv[1]) );
  else
    printf("%ld is not prime\n", atol(argv[1]) );
  
  return 0;
  
  
}