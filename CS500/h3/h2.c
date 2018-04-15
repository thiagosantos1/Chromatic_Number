
/**
 * Get two integers from the command line, 'n' and 'm' and print all the numbers
 * from n to m inclusive  The starting number should be the smaller of the two
 * and the ending number the larger of n or m.  Print a usage statement and exit
 * if not enough command line parameters are given.
 *
 * Example input/output:
 * ./h2 5 1
 * 1
 * 2
 * 3
 * 4
 * 5
 */
/* Author: Thiago
 * Date: 09/08/17
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
  
  if(argc <2){
    printf("You must enter 2 integers to execute the program %s\n", argv[0]);
    exit(1);
  }
//   
  int num1, num2, aux;
  
  num1 = atoi(argv[1]);
  num2 = atoi(argv[2]);
  
  
  if(num1 > num2){ // let's say num1 has to be always smaller than num2
    aux = num1;
    num1 = num2;
    num2 = aux;
  }
  
  for(int i=num1; i <= num2; i++)
    printf("%d\n", i);
  
  
  return 0;
  
  
  
  
}