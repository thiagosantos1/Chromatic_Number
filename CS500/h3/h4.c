
/**
 * Do not modify main below. Write the function pyramid that takes an integer
 * argument and outputs a pyramid constructed of asterisks(*) that is that
 * number of rows high.
 * 
 * Example input/output:
 * ./h4 4
 *    *
 *   ***
 *  *****
 * *******
 */
  /* Author: Thiago
 * Date: 09/08/17
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void pyramid(int base);

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("usage: h4 <number>\n");
    return 1;
  }
  pyramid(atoi(argv[1]));

  return 0;
}


void pyramid(int base){
 
  int numOfStars = 1;
  
  for(int i=base; i>0 ; i--){
    
    for(int j=0; j< i -1; j++){
     
      printf(" ");
      
    }
    
    if(i == base){ // for the first one
      printf("*");
      
    }else{
      for(int stars=0; stars < numOfStars; stars++)
	       printf("*");
      
    }
    
    printf("\n");
    numOfStars+=2;
    
  }
  
  
}