
/**
 * Create a global character array containing the string:
 *   "nopqrstuvwxyzabcdefghijklm"
 * And read characters from the standard input and convert them all to lower-
 * case using the tolower() function.  Use the global character array to map
 * the characters a-z to the characters in the array, (i.e. 'a' should map to
 * 'n', 'b' to 'o', etc.) and print the character it maps to instead of the
 * original.
 * 
 * Example input/output:
 * ./h6
 * test
 * grfg
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  
  int letter, gloabalChar[] = {'n', 'o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m'};
  	
  letter=getchar();
  if(letter == '\n')
    putchar(letter);
  
  while(!feof(stdin)){
   
    letter = tolower(letter);
    if( (letter - 'a' > 25) || (letter - 'a' < 0) )
      putchar(letter);
    else
      printf("%c", gloabalChar[letter - 'a']);
    
    letter=getchar();
    
  }
  

  return 0;
  
}