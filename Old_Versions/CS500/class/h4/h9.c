/* Create a global integer array called 'primes' of at least 100000 integers in
 * size and another integer called 'nprimes' that is initialized to 0, use
 * nprimes as the index into the primes array when you add a new prime number
 * to the primes array.  After adding a prime, increase nprimes by one.
 */


/*
 * Create a function called isprime that takes a number (n) and test if it is
 * prime and if it is, returns true (non-zero), otherwise false (0).
 * The function should:
 *  - Test n against all the primes stored in the global 'primes' that are
 *    less than or equal in value to the square root of n.
 *  - If any of the primes evenly divides n, return false immediately.
 *  - return true if none of the above primes evenly divides n.
 */


/*
 * This program prints the Nth prime (N an integer provided from the command
 * line.)
 * Example input/output:
 * ./h9 100
 * 541
 * ./h9 10000
 * 104729
 */



  /* Check that a number has been provided on the command line: */
  /* It hasn't so print a usage message and exit the program. */




  /* Take the first argument (a string) and convert it to an number. */
  /* If it's <= 0 or > 100000, print an out of range message and quit. */






  /* Add 2 to the primes array and set the first number to be checked to 3. */



  /**
   * Decrement n by one and while n is not zero, loop and keep decreasing it
   * by one each time through the loop.
   */

    /**
     * Make an inner loop that loops while the number is not prime, adding
     * two to the number on each loop iteration.
     */

    /**
     * Past the inner loop while loop, the number to be checked must be prime,
     * so we've found another prime. Add it to the primes array, then add 2 to
     * the number to be checked:
     */




  /* Print the last prime added to the primes array, it should be the nth prime: */



