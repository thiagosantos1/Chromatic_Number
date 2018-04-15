#include <stdio.h>
#include <stdlib.h>

/**
 | (3pts)
 | Given an input n, print a triangle out of spaces and asterisks that is n rows
 | high and is upside down that also has as many spaces before it as asterisks.
 | e.g. for an input of 5 it should print:
 |     *****
 |    ****
 |   ***
 |  **
 | *
 */
int main(int argc, char *argv[])
{
  int n;
  if (argc > 1) n = atoi(argv[1]);
  else return 0;
  /* Write your code here: */
  int rows = n;
  
  for(rows=rows; rows>0;rows--){
    
    for(int sp = rows; sp>0;sp--)
      putchar(' ');
    for(int star = rows; star>0;star--)
      putchar('*');
    putchar('\n');
    
  }

  return 0;
}
