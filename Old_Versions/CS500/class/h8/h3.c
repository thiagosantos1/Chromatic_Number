/* 2 points  */
#include <stdio.h>
#include <stdlib.h>

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



/**
 * Make a main function that takes two integer command line arguments and
 * uses the mult() function you used to multiply the two numbers together.
 * Example input/output:
 * ./h3 5 10
 * 5 * 10 = 50
 * ./h3 32767 65534
 * 32767 * 65534 = 2147352578
 */

