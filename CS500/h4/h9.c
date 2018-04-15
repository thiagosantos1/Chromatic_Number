

/*
 * This program prints the Nth prime (N an integer provided from the command
 * line.)
 * Example input/output:
 * ./h9 100
 * 541
 * ./h9 10000
 * 104729
 */
   
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Create a global integer array called 'primes' of at least 100000 integers in
 * size and another integer called 'nprimes' that is initialized to 0, use
 * nprimes as the index into the primes array when you add a new prime number
 * to the primes array.  After adding a prime, increase nprimes by one.
 */
int primes[100000], nprimes=0;

int isPrime(int number);

int main(int argc, char * argv[]){
  
  int number, numToCheck;
  
   /* Check that a number has been provided on the command line: */
  /* It hasn't so print a usage message and exit the program. */
  if(argc<2){
    printf("Please provide a number for the program %s\n", argv[0]);
    exit(1);
   }
  
  /* Take the first argument (a string) and convert it to an number. */
  /* If it's <= 0 or > 100000, print an out of range message and quit. */
  if( (atoi(argv[1])  <=0 ) || (atoi(argv[1]) >100000) ){
    printf("Number is Out of range\n");
    exit(1);
  }
  
  number=atoi(argv[1]);
  
   /* Add 2 to the primes array and set the first number to be checked to 3. */
  primes[nprimes++] = 2;
  numToCheck = 3;
  
    /**
   * Decrement n by one and while n is not zero, loop and keep decreasing it
   * by one each time through the loop.
   */
  while(--number >0){
    
    
    /**
     * Make an inner loop that loops while the number is not prime, adding
     * two to the number on each loop iteration.
     */
    while(!isPrime(numToCheck)){
      
      numToCheck +=2;
      
    }
    
    /**
     * Past the inner loop while loop, the number to be checked must be prime,
     * so we've found another prime. Add it to the primes array, then add 2 to
     * the number to be checked:
     */
    primes[nprimes++] = numToCheck;
    numToCheck +=2;
    
  }
  
  
  

  /* Print the last prime added to the primes array, it should be the nth prime: */
  
  printf("%d\n", primes[nprimes -1]);
  
  return 0;
  
  
}          

/*
 * Create a function called isprime that takes a number (n) and test if it is
 * prime and if it is, returns true (non-zero), otherwise false (0).
 * The function should:
 *  - Test n against all the primes stored in the global 'primes' that are
 *    less than or equal in value to the square root of n.
 *  - If any of the primes evenly divides n, return false immediately.
 *  - return true if none of the above primes evenly divides n.
 */
int isPrime(int number){
  
  if( (number %2) ==0)
    return 0; // not prime
  
  for(int i=0; i<nprimes; i++){
    
    if(primes[i] <= sqrt(number)){ // test just until the square root of n
      if( (number %primes[i]) ==0)
	return 0; // not prime
    }else{
      return 1; // is prime
    }
    
  }
   
    
  return 1; // it's prime
}












