#include <stdio.h>
#include <stdlib.h>

unsigned int shuffle(unsigned int n)
{
 
  
  //num = (num) << (32-4) | (num) >> 4;
  //num = num << (32-4) | num >>4;
 // num = (num) << (32-8) | (num) >> 8;
  //num = num << (32-8) | num >>8;

 // return num;
  
  int a = n>>24;
  int b = n>>16 & 0xFF; // masc it off - put zero in all other positions
  int c = n>>8 & 0xFF;
  int d = n & 0xFF;
  
  return (d<<24) | (c<<16) | (b<<8) | a;
  
  // or
  
}
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
