/* 1 point */
#include <stdio.h>
#include <stdlib.h>

/**
 * Get the first command line parameter as an integer and create a hollow 
 * pyramid composed of asterisks (*) and spaces that is the integer rows high:
 * Example input/output:
 * ./h3 5
 *     *
 *    * *
 *   *   *
 *  *     *
 * *********
 */

void printSpace(int times)
{
  for(int space =0; space <times; space++)
     putchar(' ');
  
}
void printStar(int times)
{
  for(int st=0; st<times;st++)
    putchar('*');
  
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: %s <height>\n", argv[0]);
    return 0;
  
  }
  int num = atoi(argv[1]);
  int lSpace = num-1, rSpace = 0;

  for(int n=0; n<num; n++){
	  printSpace(lSpace);
	  if(n<num-1){
	  	putchar('*');
		printSpace(rSpace+n-1);
		if(n>0)
			putchar('*');
	  }
	  else{
		  printStar(num+rSpace);
	  }
		
	  lSpace--;
	  rSpace++;
	  putchar('\n');
  }

  return 0;
}
