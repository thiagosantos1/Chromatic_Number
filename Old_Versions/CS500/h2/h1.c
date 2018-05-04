
/**
 * Create a main function that:
 * - Reads a character from stdin and outputs that character. If the character
 *   is a lowercase letter however it should output the uppercase version of
 *   that letter.
 * Example input/output:
 * ./h1
 * test
 * TEST
 */


/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

/* Useded Help of cReference.com to remeber about reading from stind
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
	
	int letter; 
	
	letter=getchar();
	while(!feof(stdin)){
	  letter = toupper(letter);
	  putchar(letter);
	  letter=getchar();
	}
	
	return 0;
}

