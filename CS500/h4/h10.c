#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*
 * This program prints the prime factors of a number provided to the program
 * via the command line.
 * Example input/output:
 * ./h10 9872349872
 * 9872349872: 2 2 2 2 7 7 11 347 3299
 */

int isPrimeFactor(long int num, int factor);
int main(int argc, char * argv[]){
  
    /* Make sure the numbers are stored as longs. */
  long int factNum, squareFactor;
  
    /**
   * If there isn't a number on the command line, print a usage statement and
   * exit.
   */
  if(argc<2){
    printf("Please provide a number for the program %s\n", argv[0]);
    exit(1);
  }
  
   /**
   * n will hold the number we want to print the prime factors of. Use atol()
   * convert the string to a long integer.
   */
  factNum = atol(argv[1]);
  
    /**
   * If n is too small, there can't be any factors.  It has to be at least 2,
   * print a error message "No factors for %ld\n".
   */
  if(factNum <2){
    printf("No factor for %ld\n", factNum);
    exit(1);
  }
  
   /* Print the number out so we know what it originally was: */
  printf("%ld: ", factNum);
  
   /**
   * Find the square root of n, we only need to check factors up to the square
   * root of the number:
   */
  squareFactor = sqrt(factNum);

  
  /**
   * Check if 2 is a prime factor, 2 is the only even prime so we check it
   * separately to make the code cleaner.  If 2 evenly divides n, we print a
   * 2 and divide n by 2 until 2 no longer evenly divides it.
   */
  
  while(isPrimeFactor(factNum,2) ){
   
    printf("%d ", 2);
    factNum /=2;
  }
  
  /* Now we check all the odd numbers up to the square root of n: */
    /* Check the next odd number. */
  for(int i=3; i<=squareFactor; i+=2){ 
    
     /* So long as the number we're at evenly divides n, we print the number out
     * and divide n by the number.
     */
    while(isPrimeFactor(factNum,i)){
   
      printf("%d ", i);
      factNum /=i;
    }
  }
  
  /* If n isn't 1 after the loop, then all that is left is a prime number,
   * so we print it.
   */
  if(factNum !=1)
    printf("%ld", factNum);

  /* Print a newline at the end. */
  
  printf("\n");
  
  return 0;
  
} 
  
int isPrimeFactor(long int num, int factor){
  
  if( (num %factor) ==0)
    return 1; // is a prime factor
  
  return 0; // is not a prime factor 
   
}
