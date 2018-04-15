
/**
 * Make a program that reads characters from stdin and does the following:
 * 1) Maintains a counter that increments by one when the character is a open
 *    parenthesis '(' and decrements it by one if it is a close parenthesis ')'.
 * 2) If the counter above ever goes below zero set a flag indicating that it
 *    has done so.
 * 3) After you have read all the characters, print:
 *    "Too many )'s" if the counter is below zero or ever under-flowed.
 *    "Too many ('s" if the counter is above zero, or:
 *    "OK" if the counter is zero.
 *
 * Example input/output:
 *./h4 < Makefile
 * OK
 * ./h4
 * (()
 * Too many ('s
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  
  int letter, countParen=0; // countParen - Count parenthesis 
	
  letter=getchar();
  while(!feof(stdin)){
    
    if(letter == '(')  
       countParen++;
    
    if(letter == ')')
       countParen--;
    
    letter=getchar();
    
  }
  
  if(countParen > 0)
    printf("Too many ('s\n");
  else if(countParen <0)
    printf("Too many )'s\n");
  else
    printf("OK\n");
  

  return 0;
  
}