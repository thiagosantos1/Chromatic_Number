
/**
 * Reads a list of numbers (one per line) in from the standard input using
 * scanf() and prints a sideways graph.
 * 
 * Example input/output:
 * ./h8 < testdata
 *  5: #####
 * 40: ########################################
 * 51: ###################################################
 * ...
 * 26: ##########################
 * 46: ##############################################
 * 14: ##############
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
  
    printf("%2d: ", num);
    for(int i=0; i<num; i++){
      printf("#");
    }
    printf("\n");
  }
  
  return 0;
  
  
}
