#include <stdio.h>
#include <stdlib.h>

/**
 * (4pts)
 * Create a function called shuffle that takes an unsigned integer and returns
 * the same, which exchanges (swaps) the high byte of the number with the low
 * byte and does the same with the two middle bytes of the number.  Thus the
 * hex number 12345678 should be returned as 78563412
 */


/**
 * Do not modify main below:  This reads takes a hex number from the command
 * line and uses it in with your shuffle function.  Output is in hex.
 */
int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: %s n\n", argv[0]);
    return 0;
  }
  unsigned int n = strtol(argv[1],NULL,16);
  printf("%08x -> %08x\n", n, shuffle(n));
  return 0;
}
