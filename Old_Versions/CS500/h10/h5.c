/* 2 point */
#include <stdio.h>
#include <stdlib.h>

/**
 * Get the first command line parameter as an integer (h). Print a diamond
 * composed of asterisks (*) that is h rows high:
 * Example input/output:
 * ./h5 5     | ./h5 6
 *   *        |   *
 *  ***       |  ***
 * *****      | *****
 *  ***       | *****
 *   *        |  ***
 *            |   *
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
  int mid = num/2;
  int lSpaces = (num%2)==0 ? mid-1:mid;
  int star = 1, jump = 2;
  int midle = (num%2)==0 ? mid:mid+1; // to do half of hte diamond

  // half of the diamond
  int row;
  for(row=0 ; row<midle; row++){
	  printSpace(lSpaces);
	  printStar(star);

	  lSpaces--;
	  star +=jump;
	  putchar('\n');

  }
  
  // other half of the diamond
  lSpaces = (num%2)==0 ? 0:1;
  star = (num%2)==0 ? star-(jump): star - (jump*2);
  for(row=row; row<num; row++){
	  printSpace(lSpaces);
	  printStar(star);

	  lSpaces++;
	  star -=jump;
	  putchar('\n');
  }

  return 0;
}
