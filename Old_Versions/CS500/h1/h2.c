// Thiago Santos - CS 500
// 08/24/2017
#include <stdio.h>

/**
 * Create a main function that:
 * 1) Uses the "printf" function to print: 'Hello, world!' followed by a 
 *    newline (\n) character to the screen.
 * 2) Do the above three times.
 * 3) Use the return keyword to exit the main function with a return value
 *    of zero.
 */

int main(void)
{

	for (int count = 0; count < 3; count++)
	{
		printf("%s\n", "Hello, world!" );
	}

	return 0;

}
