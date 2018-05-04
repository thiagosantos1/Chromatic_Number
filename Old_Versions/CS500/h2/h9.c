
/**
 * Make a program that reads characters from the standard input and counts all
 * occurrences of == (just two equal signs), but not = or ===, etc.
 * 
 * Example input/output:
 * ./h9
 * = == ===
 * <ctrl-D>
 * 1
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
	
	int letter, equalOccur=0; // counts how many times == apears
	int equalCountFlag=0; // counts how many opens '=' there are
	
	letter=getchar();
	while(!feof(stdin)){
	  
	  if(letter == '='){
	    equalCountFlag++;
	    
	  }
	  else{
	    
	    if(equalCountFlag == 2)
	      equalOccur++;
	    
	    if(equalCountFlag >0)
	      equalCountFlag = 0;
	    
	  }
	  	  
	  letter=getchar();
	}
	
	
	printf("%d\n", equalOccur);
	return 0;
}
