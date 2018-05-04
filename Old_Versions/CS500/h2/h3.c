
/**
 * Make a program that counts all the upper and lower case x's and o's in the
 * input on stdin and then prints the counts of each.
 * 
 * Example input/output:
 * ./h3 < Makefile 
 * X's = 1, O's = 38
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  
  int letter, countX=0, countO=0; 
	
  letter=getchar();
  while(!feof(stdin)){
    letter = toupper(letter);
    
    if(letter == 'X')  
       countX++;
    
    if(letter == 'O')
       countO++;
    
    letter=getchar();
    
  }
  
  printf("X's = %d, O's = %d\n", countX, countO);
  

  return 0;
  
}