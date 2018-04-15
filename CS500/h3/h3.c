
/**
 * Prints the powers of two from 0 to 63:
 * Example output:
 * ./h3
 * 2^0  = 1
 * 2^1  = 2
 * 2^2  = 4
 * 2^3  = 8
 * ...
 * 2^62 = 4611686018427387904
 * 2^63 = 9223372036854775808
 */
/* Author: Thiago
 * Date: 09/08/17
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// for some how the function pow is not working, it's not compiling
// then I just did a function to my own pow function
double toThePower(int base, int exp)
{
    double result = 1; // everything to the power of 0 is equal 1
    while(exp >0) 
    {   
        result = result * base; 
        exp--; 
    }
    return result;
    
}


int main()
{
  
  for(int i=0; i<=9; i++)
    printf("2^%d  = %.0f\n", i, toThePower(2,i));  // pow(2,i) not working
    
  for(int i=10; i<=63; i++)
    printf("2^%d = %.0f\n", i, toThePower(2,i));  // pow(2,i) not working
    
  
  
}