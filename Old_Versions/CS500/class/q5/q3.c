#include <stdio.h>
#include <stdlib.h>

/**
 * Write a C function named roundPower2 that has one long int as a parameter.
 * The function should return the next power of 2 that is <= the parameter.
 * For example, if the parameter is 17 the function should return 16. If the
 * parameter is 100 the function should return 64.  If the parameter is 8
 * the function should return 8. (4 points)
 */








/* Do not modify main below */
int main(int argc, char *argv[])
{
  long int n;
  
  if (argc < 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 0;
  }
  n = atol(argv[1]);
  printf("%ld -> %ld\n", n, roundPower2(n));

  return 0;
}
