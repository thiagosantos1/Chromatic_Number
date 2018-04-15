
/**
 * Make a program that takes a single integer command line argument (n) and
 * makes a n x n multiplication table resembling the 4x4 example below. It
 * should accept numbers between 1 and 12, but no smaller or larger.  If there
 * are not enough arguments it should print a usage:
 *   Usage: h7 <n>\n
 * and exit, and if n is out of range it should print:
 *   n out of range (1-12)\n
 * and exit.  All numbers are right-aligned to 4 characters.
 *
 * Example input/output:
 * ./h7 4
 *    *    1   2   3   4
 *     +----------------
 *    1|   1   2   3   4
 *    2|   2   4   6   8
 *    3|   3   6   9  12
 *    4|   4   8  12  16
 */

/* Author: Thiago
 * Date: 09/08/17
 */

#include<stdio.h>
#include<stdlib.h>


void nXnMultiplication(int side)
{
  
  printf("%4s ", "*");
  
  for(int i=1; i<=side; i++){
    printf("%4d", i);
  }
  printf("\n %4s", "+");
  
  for(int i=0; i< (side*4); i++)
    printf("-");
  
  printf("\n");
  
  for(int i=1; i<=side; i++){
    
    for(int mult =0; mult<=side; mult++){
      if(mult==0)
	       printf("%4d|", i);
      else
	       printf("%4d", i * mult);
    }
    
    printf("\n");
    
  }
  
  
}

int main(int argc, char * argv[])
{
  
  if(argc<2){
    printf("usage: h4 <number>\n");
    exit(1);
  }
  
  if( (atoi(argv[1]) <1) || (atoi(argv[1]) >12) ){
    printf("n out of range (1-12)\n");
    exit(1);
  }
  
  nXnMultiplication(atoi(argv[1]));
  
  return 0;
  
  
}