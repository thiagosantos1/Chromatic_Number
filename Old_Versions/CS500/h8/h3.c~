/* 2 points  */
#include <stdio.h>
#include <stdlib.h>

/* Source Used
 * 
 * https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm
 * 
*/

/** (1pt)
 * Create a function called add that takes two unsigned integers and adds them
 * together w/o using the addition operator at all.  You may use only the
 * binary operators &, |, ^, << and >>. Given bits in a and b to be added
 * together, the bit in result, and the carry flag is the result of adding the
 * bit in a, with the bit in b and the carry from the previous bit.  Use the
 * following truth table to determine the formula for calculating the result and
 * carry:
 * 
 * a b carry	result	new carry
 * 0 0 0	0	0
 * 0 0 1	1	0
 * 0 1 0	1	0
 * 0 1 1	0	1
 * 1 0 0	1	0
 * 1 0 1	0	1
 * 1 1 0	0	1
 * 1 1 1	1	1
 *
 * Hint, for the result, consider the xor operation.  For the carry it is one
 * when at least two of the bits are 1.  Also you can stop when all the a and b
 * bits left are zeros, but remember to "carry" the last carry.
 */
unsigned int add(unsigned int num1, unsigned int num2)
{
  unsigned int carry;
  while(num2 != 0){ // no carry left
    
    carry = num1 & num2; // if both are 1, then the carry becomes 1; otherwise, it is 0
    
    num1 = num1 ^ num2; // sum of bits of both numbers. if at least of of them is 1, it becomes 1
    
    num2 = carry <<1; // carry goes shifted one to the left
  }
  
  return num1;
  
}


/** (1pt)
 * Make a function called mult, that takes two unsigned integer parameters and
 * multiplies them together w/o using the multiplication or addition operators
 * or any other external function.  You may use the above add function as well
 * as Boolean and binary operations including &, |, ^, << and >>.  You should
 * use the grade-school method of multiplication but for binary numbers.  The
 * return type should be a normal signed integer.
 * 
 * a=    10011	shift a right by one after each addition
 * b=  *   101	shift b left by one after each addition
 *       -----
 *       10011	if bit 1 in b is 1, add a to result
 *      00000	if bit 1 in b is 0, add nothing to result
 *   + 10011	Note the spaces here are actually zero's in a (a is being <<)
 *     -------
 *     1011111	Stop when b is 0, return result.
 * 
 * This is probably easier than adding above, so use + or += to get this working
 * first, then switch to using add() above once you've got it.
 */

int mult(unsigned int num1,unsigned int num2)
{
  if(num1==0 || num2==0) // multiplication of 0 is 0
    return 0;
  
  // just add num1 with num2, num2 times ( 5 *3 = 5+5+5)
  return add(num1, mult(num1, num2-1));
  
}

/**
 * Make a main function that takes two integer command line arguments and
 * uses the mult() function you used to multiply the two numbers together.
 * Example input/output:
 * ./h3 5 10
 * 5 * 10 = 50
 * ./h3 32767 65534
 * 32767 * 65534 = 2147352578
 */

int main(int argc, char * argv[])
{
  if(argc<3){
    printf("Usage <int int> %s\n", argv[0]);
    exit(1);
  }
  
  //printf("Add: %d\n", add( atoi(argv[1]), atoi(argv[2])) ); 
  printf("%d * %d = %d\n",atoi(argv[1]),atoi(argv[2]), mult( atoi(argv[1]), atoi(argv[2])) );
  
  return 0;
  
  
}



