/* 1 point */
#include <stdio.h>
#include <stdlib.h>

/**
 * Get the first command line parameter as an integer and print an upside-down
 * pyramid composed of asterisks (*) that is that number of rows high:
 * Example input/output:
 * ./h1 5
 * *********
 *  *******
 *   *****
 *    ***
 *     *
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
  
  int rows = atoi(argv[1]);
  // looking to the base case, botton of pyramind, we can see that it always increese by 2 (1 - 1+2 - 3+2 ....)
  // Thus we have a formula to find how many stars at each level - (depth *2 -1), first layer been depth 5 (max depth of the pyramind)
  int depth = rows;
  int spaces = 0; // used before print first star
  for(int i=0; i<rows; i++){
    
    printSpace(spaces);
    
    printStar((depth*2)-1);
    
    putchar('\n');
    depth--;
    spaces++;
    
  }

  return 0;
}
