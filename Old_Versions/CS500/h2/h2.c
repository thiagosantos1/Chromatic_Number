
/**
 * Create a main function that:
 * 1) Reads a character from stdin and outputs that character, however:
 * 2) Each line should be prefixed with its line number, starting at 1.  Each
 *    line number should be 3 characters wide with a space following it.
 * Hint: Print the line number for 1 before entering the loop.  Whenever you
 *   encounter a newline (\n), print the newline then the next line number
 *   and continue on with the loop.
 * - Print an extra newline after the main loop to make sure the cursor is on
 *   a new line before the program exits.
 * Example input/output:
 * ./h2 < Makefile
 *   1 CC=gcc
 *   2 
 *   3 PROGS=h1 h2 h3 h4 h5 h6 h7 h8 h9 h10
 * ...
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  
  int letter, countLine=1; 
	
  letter=getchar();
  if(!feof(stdin))
    printf("%3d ", countLine++);
  
  while(!feof(stdin)){
    putchar(letter);
    if(letter == '\n')
       printf("%3d ", countLine++);
    letter=getchar();
    
  }

  return 0;
  
}