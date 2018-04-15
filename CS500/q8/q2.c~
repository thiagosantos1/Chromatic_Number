#include <stdio.h>
#include <ctype.h>

/**
 * (3pts)
 * Reads one character at a time from stdin and count the number of times a
 * letter is immediately preceded by a letter of lesser value.  Uppercase and
 * lowercase letters should be considered the same (i.e. A == a, b > A or a).
 * Print the count after reading all the characters.
 */

int main(int argc, char *arv[])
{
  int ch=0, prev=0, count=0;
  
  while((ch=getchar())!= EOF){
      ch= toupper(ch);
      
      if(isalpha(ch) && isalpha(prev)){
	if(prev<ch) count++;
      }   
      prev=ch;     
  }
  
  printf("%d\n", count);

  return 0;
}
