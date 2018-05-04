/* 1 point */
#include <stdio.h>
#include <stdlib.h>

/**
 * Get the first command line parameter as an integer and print a hollow box
 * composed of asterisks (*) that is that width and height:
 * Example input/output:
 * ./h2 5
 * *****
 * *   *
 * *   *
 * *   *
 * *****
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
    printf("Usage: %s <size>\n", argv[0]);
    return 0;
  }

  int num = atoi(argv[1]);
  int stars = 0;

  for(int line =0; line<num; line++){
	if(line == 0 || line == num-1)
		stars = num;
	else
		stars = 2;
	
	if(stars == num){
		printStar(stars);
	}	
	else{
		putchar('*');
		printSpace(num-stars);
		putchar('*');

	}
	putchar('\n');
  }

  return 0;
}
