#include <stdio.h>
#include <ctype.h>

/**
 * Write a C program that reads from stdin one character at a time and prints
 * the characters in "excited mode" - all '.' characters are printed as '!',
 * letters are printed as upper case, and all other characters are printed as-is.
 * (3 points)
 */

int main(int argc, char *arv[])
{

  int ch;
  while( (ch = fgetc(stdin)) != EOF){
       
    if(ch=='.')
      printf("!");
    else if(isalpha(ch))
      printf("%c", toupper(ch));
    else
      putchar(ch);
   
    
  }
  
  return 0;
}
