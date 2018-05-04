#include <stdio.h>
#include <stdlib.h>

/**
 * (3pts)
 * Given n, where 1 <= n <= 9, print a pyramid in the form:
 * 1
 * 12
 * 123
 * ...
 * 123...n
 * i.e. n rows high and up to n items in width.
 */
int main(int argc, char *argv[])
{
  int n;
  if (argc > 1) n = atoi(argv[1]);
  else return 0;
  /* Write your code here: */
  
  for(int i=1; i<=n;i++){
    for(int j =1; j<=i; j++)
      printf("%d", j);
    printf("\n");
    
  }

  return 0;
}
