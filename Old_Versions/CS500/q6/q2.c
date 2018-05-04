#include <stdio.h>
#include <ctype.h>

/**
 * Write a C program that reads from stdin one character at a time and prints
 * the characters.  If the previous character was not a letter and the current
 * character is a letter, make sure it is printed uppercase, otherwise print the
 * character unmodified. (3 points)
 */

int main(void)
{
  int ch, prev=0;
  while((ch=getchar()) != EOF){
    
    if(prev ==0)
      putchar(ch);
    
    else if( (! isalpha(prev)) )
      putchar(toupper(ch));
    else
      putchar(ch);
    
    prev = ch;    
    
  }
  
  
}