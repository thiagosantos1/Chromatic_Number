#include <stdio.h>
#include <stdlib.h>

/**
 * Write a C function named bin2s that takes a long integer parameter and
 * returns a _static_ character string with the binary representation of the
 * parameter.  The string it returns should start with the upper most 1 bit
 * in the number. Therefore bin2s(8) should return "1000" and not a string
 * with all 64 bits. bin2s(0) should at least return "0" however. (4 points)
 */

char * bin2s(long int num)
{
  char * re = malloc(sizeof(num)*8);
  int i;
  int seq=0; // position on the string to add 1 or 0
  for(i = sizeof(num)*8 -1; i>=0; i--){
   
    if(num & (1UL<< i))
      break;
  }
  
  for( i=i; i>=0; i--){
   
    if(num & (1UL<< i))
      re[seq++] = '1';
    else
      re[seq++] = '0';
  }
  
  if(num==0) // be sure to get from 0
    re[0] = '0';
  
  return re;
  
}

/* Do not modify main below */
int main(int argc, char *argv[])
{
  long int n;
  
  if (argc < 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 0;
  }
  n = atol(argv[1]);
  printf("%ld -> %s\n", n, bin2s(n));

  return 0;
}
