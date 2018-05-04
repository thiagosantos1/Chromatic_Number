
/**
 * Create a program that reads characters from the standard input and prints all
 * the characters between ()'s (including the ()'s), each on its own line.  It
 * should allow nested parenthesis as well.
 * 
 * Example input/output:
 * ./h7 < Makefile
 * (PROGS)
 * (CC)
 * (LDFLAGS)
 * ...
 * (CC)
 * (CFLAGS)
 * (PROGS)
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
	
	int letter;
	int openParenFlag=0; // counts how many opens parenthesis there are
	
	letter=getchar();
	while(!feof(stdin)){
	  
	  if(letter == '(')
	    openParenFlag++;
	  
	  if(openParenFlag>0)
	    putchar(letter);
	  
	  if(letter == ')'){
	    openParenFlag--;
	    if(openParenFlag == 0)
	      printf("\n");
	    else if(openParenFlag <0)
		openParenFlag =0;
	  }
	  
	  letter=getchar();
	}
	
	return 0;
}

