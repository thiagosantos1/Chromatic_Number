// Thiago Santos - CS 500
// 08/24/2017
#include <stdio.h>

/**
 * Modify the code example 1.2p9.c in the following way:
 * 1) Print three columns of numbers followed by the ASCII character for that
 *    number.  The first column is in the range 32 to 63 in steps of 1. The
 *    second columns 32 more than that and the third is 64 more than that.
 * 2) Print each columns number right aligned to three characters followed by
 *    a space then the ASCII character for that number.  Use tabs between
 *    columns and a newline at the end of the third column.
 * Hints: In printf, %#d will format a decimal number to be right aligned #
 *    spaces and %c prints the character of the number given. Look at Example
 *    1.1p8 for how to join multiple printfs together to output one line of
 *    text.
 * 
 * Example output:
 *  32      64 @    96 `
 *  33 !    65 A    97 a
 *  34 "    66 B    98 b
 *  35 #    67 C    99 c
 * ...
 *  62 >    94 ^   126 ~
 *  63 ?    95 _   127 
 */


int main(void)
{
	
	for (int count = 32; count < 64; count++)
	{
		printf("%3d %c\t%3d %c\t%3d %c\n", count, count, count+32, count+32, count+64, count+64);

	}


	return 0;
}

