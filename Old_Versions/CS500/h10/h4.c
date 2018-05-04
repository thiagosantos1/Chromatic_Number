/* 1 point */
#include <stdio.h>
#include <stdlib.h>

/**
 | Get the first command line parameter as an integer (n).  Print a field of
 | alternating asterisks (*) and spaces that is a n x n rows and columns high.
 | Note that each row must be n columns wide, including spaces.
 | Example input/output:
 | ./h4 5
 | * * *
 |  * * 
 | * * *
 |  * * 
 | * * *
 */

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: %s <size>\n", argv[0]);
    return 0;
  }
  int num = atoi(argv[1]);
  int line;
  for(int row = 1; row <=num; row++){
	  if((row %2) ==0)
		  line = 2;
	  else
		  line =1;

	  for(int pt=line; pt<num+line; pt++){
	  	if( (pt%2 ==0))
			putchar(' ');
		else
			putchar('*');
	  }
	  putchar('\n');	
  }

  return 0;
}
