
/**
 * Prints the binary representations of all the numbers from 0 to 255
 * (represents 8 binary bits).
 * Hint:  To test bit i in n use: (n & (1<<i))
 *  If the result is not zero, the bit is set (i.e. on or a 1.)
 * 
 * Example input/output:
 * ./h9:
 *   0:         
 *   1:        *
 *   2:       * 
 *   3:       **
 * ...
 * 253: ****** *
 * 254: ******* 
 * 255: ********
 */

/* Author: Thiago
 * Date: 09/08/17
 */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
 
  
  for(int i=0; i<= 255; i++){
   
    printf("%3d:", i);
    
    for(int binary =8; binary >= 0; binary--){
      
      // if for that byte position the binary is set, printf *
      if(i & (1<<binary))
	       printf("*");
      else
	       printf(" ");
      
    }
    
    printf("\n");
    
  }
  
  return 0;
  
}



