// Thiago Santos - CS 500
// 08/24/2017
#include <stdio.h>

/**
 * Modify example 1.2p9 to just print "Hello, world!" preceded by a number
 * that is right aligned to three spaces and ranges from 1 to 100 in steps of
 * 3.
 * Example output:
 *   1 Hello, world!
 *   4 Hello, world!
 *   7 Hello, world!
 *  10 Hello, world!
 *  13 Hello, world!
 * ...
 * 100 Hello, world!
 */


int main(void)
{
	
	for (int i = 0; i < 100; i+=3)
	{
		
			printf("%3d %s\n", i+1, "Hello, world!");
		
		

	}
	return 0;
}

