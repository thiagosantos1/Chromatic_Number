/*
 * This program prints the prime factors of a number provided to the program
 * via the command line.
 * Example input/output:
 * ./h10 9872349872
 * 9872349872: 2 2 2 2 7 7 11 347 3299
 */


  /* Make sure the numbers are stored as longs. */


  /**
   * If there isn't a number on the command line, print a usage statement and
   * exit.
   */





  /**
   * n will hold the number we want to print the prime factors of. Use atol()
   * convert the string to a long integer.
   */


  /**
   * If n is too small, there can't be any factors.  It has to be at least 2,
   * print a error message "No factors for %ld\n".
   */




  /* Print the number out so we know what it originally was: */

  
  /**
   * Find the square root of n, we only need to check factors up to the square
   * root of the number:
   */


  /**
   * Check if 2 is a prime factor, 2 is the only even prime so we check it
   * separately to make the code cleaner.  If 2 evenly divides n, we print a
   * 2 and divide n by 2 until 2 no longer evenly divides it.
   */




  /* Now we check all the odd numbers up to the square root of n: */


    /* So long as the number we're at evenly divides n, we print the number out
     * and divide n by the number.
     */




    /* Check the next odd number. */


  /* If n isn't 1 after the loop, then all that is left is a prime number,
   * so we print it.
   */

  /* Print a newline at the end. */



