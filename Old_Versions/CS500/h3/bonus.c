/* 2 points */

/**
 * Using h10 as a basis, print the "characters" side by side.  Each character
 * is 8 numbers high so if there are n numbers, there are n/8 "characters".
 */

/* Author: Thiago
 * Date: 09/11/17
 */

#include <stdlib.h>
#include <stdio.h>


int main(void)
{
  
  int num, arrayNums[100], arrayCount =0;
  int jump = 8, printPosition =0; // each character is 8 numbers high
  
  while( scanf("%d", &num) != EOF){
  
    arrayNums[arrayCount++] = num; 
  }
  
  for(int i=0; i<jump; i++){ // each character is 8 numbers high
    
    printPosition +=i;
    for(int character =0; character < arrayCount/jump; character++){
    
      
      for(int binary =8; binary >= 0; binary--){
      
	       // if for that byte position the binary is set, printf 
      	if(arrayNums[printPosition] & (1<<binary))
          printf("*");
        else
	       printf(" ");
      
      }	
      
      printPosition+= jump;
      
      printf(" "); // space beetween chars
      
    }
    
    printPosition =0;
    
    //
    printf("\n");
    
  }
  
  return 0;
  
  
}