
/**
 * Combine h8 and h9 together to read in a list of numbers and print their 8-bit
 * binary values.  Use the "img" test file as input on the standard input:
 */

/* Author: Thiago
 * Date: 09/08/17
 */

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
  
  int num;
  
  while( scanf("%d", &num) != EOF){
  
   printf("%3d:", num);
    
    for(int binary =8; binary >= 0; binary--){
      
      // if for that byte position the binary is set, printf *
      if(num & (1<<binary))
	       printf("*");
      else
	       printf(" ");
      
    }
    
    printf("\n");
    
  }
  
  return 0;
  
  
}