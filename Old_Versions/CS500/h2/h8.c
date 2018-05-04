
/**
 * Write a program that reads characters from the standard input and places
 * them into a character buffer if they are a number or if it's a minus sign
 * and is the first character to go in the buffer, and as long as you read
 * numbers, keep adding them to the buffer.  For any other character encountered
 * use the atoi() function and add the integer number to a sum and start over.
 * 
 * When all the characters have been read, print the sum of all the numbers.
 * 
 * Example input/output:
 * ./h8 < Makefile
 * 169
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	
	char bufferValues[30];
	int letter, sumTotal, numbCount=0; // if >0 there is a sequence of number in the input
	
	letter = getchar();
	while(!feof(stdin)){
	  
	  if(isdigit(letter) || letter=='-'){
	   
	   bufferValues[numbCount] = letter;
	    numbCount++;
	 
	  }
	  
	  else if(numbCount >0){
	  
	    sumTotal += atoi(bufferValues);
	    
	    for(int i=0; i<numbCount;i++)
	      bufferValues[i] = 'e'; // reset vector
	      
	    numbCount =0; // reset for the next iteration
	   
	  }
	
	  letter = getchar();
	}
	
	printf("%d\n", sumTotal);

	return 0;
}

